#pragma once
#include <string>
#include <vector>

#include "variable.hpp"
#include "variable_table.hpp"
#include "standard.hpp"

// This is done for brevity.
#define symbol_table_t variable_table_t

// An interpreter.
struct interpreter_t {
	program_t program;

	// Default constructor. Assumes that program has already been verified to
	// be a semantically correct program.
	interpreter_t(program_t program) {
		this->program = program;
	}
	// Interpret a statement.
	bool interpret_statement(statement_t* statement, symbol_table_t& symbols) {
		if (statement->type == st_compound) {
			compound_statement_t stmt = statement->compound_stmt;
			// Create a new symbol table and interpret each of the contained
			// statements.
			symbol_table_t new_symbols(&symbols);
			for (int i = 0; i < stmt.statements.size(); i++) {
				if (interpret_statement(stmt.statements[i], new_symbols)) {
					symbols.add_symbol(new_symbols.fetch("__return__"));
					return true;
				}
			}
		} else if (statement->type == st_conditional) {
			conditional_statement_t stmt = statement->conditional_stmt;
			// Interpret and compare the condition. If the condition is true,
			// interpret the body statement.
			if (compare(interpret_expression(stmt.condition, symbols))) {
				symbol_table_t new_symbols(&symbols);
				if (interpret_statement(stmt.body, new_symbols)) {
					symbols.add_symbol(new_symbols.fetch("__return__"));
					return true;
				}
			}
		} else if (statement->type == st_while) {
			while_statement_t stmt = statement->while_stmt;
			// Interpret and compare the condition. If the condition is true,
			// interpret the body statement.
			while (compare(interpret_expression(stmt.condition, symbols))) {
				symbol_table_t new_symbols(&symbols);
				if (interpret_statement(stmt.body, new_symbols)) {
					symbols.add_symbol(new_symbols.fetch("__return__"));
					return true;
				}
			}
		} else if (statement->type == st_return) {
			return_statement_t stmt = statement->return_stmt;
			// Interpret the value of the return statement and assign it to a
			// new symbol under the identifier __return__.
			symbols.add_symbol(latch_identifier("__return__", interpret_expression(stmt.value, symbols)));
			return true;
		} else if (statement->type == st_variable_declaration) {
			variable_declaration_statement_t stmt = statement->variable_declaration_stmt;
			if (stmt.initializer) {
				// Add a new symbol to the symbol table under the statement's
				// identifier with the value returned by interpreting the
				// statement's initializer.
				symbols.add_symbol(latch_identifier(stmt.identifier, interpret_expression(stmt.initializer, symbols)));
			} else {
				// Add a new symbol to the symbol table under the statement's
				// identifier and type with a raw value of 0.
				symbols.add_symbol({stmt.type, stmt.identifier, 0});
			}
		} else if (statement->type == st_expression) {
			expression_statement_t stmt = statement->expression_stmt;
			// Interpret the expression.
			interpret_expression(stmt.expression, symbols);
		}
		return false;
	}

	// Interpret a function.
	variable_t interpret_function(identifier_t identifier, std::vector<variable_t> parameters, symbol_table_t parent_symbols) {
		// Check if standard function int putchar(int) is being called.
		if (identifier == "putchar") {
			return CXCI_STDLIB_putchar(parameters);
		}
		// Find the function.
		function_t function;
		for (int i = 0; i < program.size(); i++) {
			if (program[i].identifier == identifier) {
				function = program[i];
				break;
			}
		}
		// Load the parameters into a new symbol table.
		symbol_table_t symbols(&parent_symbols);
		for (int i = 0; i < parameters.size(); i++) {
			symbols.add_symbol(parameters[i]);
		}
		// Interpret all of the body statements.
		for (int i = 0; i < function.body.size(); i++) {
			statement_t* statement = function.body[i];
			bool returned = interpret_statement(statement, symbols);
			if (returned) {
				// The function returned a value which is stored under the
				// identifier __return__.
				return symbols.fetch("__return__");
			}
		}
		// This statement will never be reached if the program is valid. It is
		// just used to keep the compiler quiet.
		return {};
	}

	// Interpret the program, starting at function main.
	value_t interpret() {
		return interpret_function("main", {}, nullptr).raw;
	}
};