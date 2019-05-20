/*

cxci - CobaltXII's C-like Interpreter

SYNOPSIS
	C-like interpreter written in C++11.

LICENSE
	This repository and it's contents are licensed under the MIT License.

AUTHOR
	Adam Sidat (CobaltXII)

*/

#include <iostream>
#include <fstream>
#include <string>

#include "parser.hpp"
#include "semantic_analyzer.hpp"
#include "interpreter.hpp"

// Entry point.
int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
		exit(1);
	}

	// Open the file.
	std::ifstream file_stream(argv[1]);
	if (!file_stream.is_open()) {
		std::cerr << "Could not open file \"" << argv[1] << "\"." << std::endl;
	}

	// Load the file.
	std::string file_content(
		(std::istreambuf_iterator<char>(file_stream)),
		(std::istreambuf_iterator<char>())
	);

	// Parse the file (implicity lexes the file).
	program_t program = parser_t(argv[1], file_content).parse();

	// Validate the program.
	semantic_analyzer_t semantic_analyzer(argv[1], file_content);
	semantic_analyzer.validate(program);

	// Create an interpreter.
	interpreter_t interpreter(program);

	// Pack all the arrays in the program into memory.
	interpreter.pack_arrays();

	// Interpret the program.
	return interpreter.interpret();
}