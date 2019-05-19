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

	// Latch an identifier onto a variable.
	variable_t latch_identifier(identifier_t identifier, variable_t variable) {
		return {variable.type, identifier, variable.raw};
	}

	// Assign a value to an expression.
	void assign_to(expression_t* expression, variable_t value, symbol_table_t& symbols) {
		symbols.fetch(expression->identifier).raw = value.raw;
	}

	// Returns true if the values of both variables are equal.
	bool variables_equal(variable_t a, variable_t b) {
		return a.raw == b.raw;
	}

	// Returns true if a variable is true.
	bool compare(variable_t variable) {
		return variable.raw;
	}

	// Interpret an expression.
	variable_t interpret_expression(expression_t* expression, symbol_table_t& symbols) {
		if (expression->type == et_integer_literal) {
			return {{0}, "", std::stol(expression->integer_literal)};
		} else if (expression->type == et_string_literal) {
			// TODO
		} else if (expression->type == et_character_literal) {
			return {{0}, "", expression->character_literal[0]};
		} else if (expression->type == et_identifier) {
			return symbols.fetch(expression->identifier);
		} else if (expression->type == et_indexing) {
			// TODO
		} else if (expression->type == et_function_call) {
			function_call_expression_t function_call = expression->function_call;
			// Interpret all the function arguments.
			std::vector<variable_t> arguments;
			for (int i = 0; i < function_call.parameters.size(); i++) {
				arguments.push_back(interpret_expression(function_call.parameters[i], symbols));
			}
			return interpret_function(function_call.function, arguments, symbols);
		} else if (expression->type == et_binary) {
			binary_expression_t binary = expression->binary;
			// Interpret the operands.
			if (binary.binary_operator == bi_assignment) {
				assign_to(binary.left_operand, interpret_expression(binary.right_operand, symbols), symbols);
				return interpret_expression(binary.left_operand, symbols);
			}
			variable_t left_operand = interpret_expression(binary.left_operand, symbols);
			variable_t right_operand = interpret_expression(binary.right_operand, symbols);
			if (binary.binary_operator == bi_addition) {
				return {left_operand.type, "", left_operand.raw + right_operand.raw};
			} else if (binary.binary_operator == bi_subtraction) {
				return {left_operand.type, "", left_operand.raw - right_operand.raw};
			} else if (binary.binary_operator == bi_multiplication) {
				return {left_operand.type, "", left_operand.raw * right_operand.raw};
			} else if (binary.binary_operator == bi_division) {
				return {left_operand.type, "", left_operand.raw / right_operand.raw};
			} else if (binary.binary_operator == bi_modulo) {
				return {left_operand.type, "", left_operand.raw % right_operand.raw};
			}
			bool compare_left = compare(left_operand);
			bool compare_right = compare(right_operand);
			if (binary.binary_operator == bi_logical_and) {
				return {{0}, "", long(compare_left && compare_right)};
			} else if (binary.binary_operator == bi_logical_or) {
				return {{0}, "", long(compare_left || compare_right)};
			} else if (binary.binary_operator == bi_relational_equal) {
				return {{0}, "", long(variables_equal(left_operand, right_operand))};
			} else if (binary.binary_operator == bi_relational_non_equal) {
				return {{0}, "", long(!variables_equal(left_operand, right_operand))};
			} else if (binary.binary_operator == bi_relational_greater_than) {
				return {{0}, "", long(left_operand.raw > right_operand.raw)};
			} else if (binary.binary_operator == bi_relational_lesser_than) {
				return {{0}, "", long(left_operand.raw < right_operand.raw)};
			}
		} else {
			unary_expression_t unary = expression->unary;
			if (unary.unary_operator == un_value_of) {
				// TODO
			} else if (unary.unary_operator == un_arithmetic_positive) {
				variable_t operand = interpret_expression(unary.operand, symbols);
				return {operand.type, "", long(+operand.raw)};
			} else if (unary.unary_operator == un_arithmetic_negative) {
				variable_t operand = interpret_expression(unary.operand, symbols);
				return {operand.type, "", long(-operand.raw)};
			} else if (unary.unary_operator == un_address_of) {
				// TODO
			} else {
				return {{0}, "", long(!compare(interpret_expression(unary.operand, symbols)))};
			}
		}
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