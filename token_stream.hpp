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
};

#undef TOKEN_DEBUG