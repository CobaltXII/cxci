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