#include <iostream>
#include <fstream>
#include <string>

#include "parser.hpp"
#include "prettyprint.hpp"

// Entry point.
int main(int argc, char** argv) {
	if (argc != 2) {
		std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
		exit(1);
	}

	std::ifstream file_stream(argv[1]);
	if (!file_stream.is_open()) {
		std::cerr << "Could not open file \"" << argv[1] << "\"." << std::endl;
	}

	std::string file_content(
		(std::istreambuf_iterator<char>(file_stream)),
		(std::istreambuf_iterator<char>())
	);

	program_t program = parser_t(argv[1], file_content).parse();

	for (int i = 0; i < program.size(); i++) {
		prettyprint_function(program[i]);
	}

	return 0;
}