#pragma once
#include <string>

#include "char_stream.hpp"
#include "token.hpp"

// Debugging information for tokens. This includes the line number and the
// column number.
#define TOKEN_DEBUG input.lineno, input.colno

// A token stream.
struct token_stream_t {
	char_stream_t input;

	// Default constructor.
	token_stream_t(std::string buffer = "") {
		input = char_stream_t(buffer);
	}

	// Checks if a character is a digit.
	static bool chr_digit(int ch) {
		return ch >= '0' && ch <= '9';
	}

	// Checks if a character can be the first character in an identifier.
	static bool chr_id_start(int ch) {
		return (ch >= 'a' && ch <= 'z') ||
			   (ch >= 'A' && ch <= 'Z') ||
			   ch == '_';
	}
};

#undef TOKEN_DEBUG