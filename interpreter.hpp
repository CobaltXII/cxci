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
};