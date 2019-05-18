#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include "ansi_colors.hpp"
#include "token_stream.hpp"

// A completed token stream.
struct complete_token_stream_t {
	std::string filename;
	token_stream_t input;
	std::vector<token_t> tokens;
	long cursor = 0;

	// Default constructor.
	complete_token_stream_t(std::string filename = "", token_stream_t buffer = token_stream_t("")) {
		this->filename = filename;
		input = buffer;
		token_t token;
		while ((token = input.next()).type != tk_eof) {
			tokens.push_back(token);
		}
		tokens.push_back(token);
	}

	// Get the next token in the stream and increment the cursor.
	token_t next() {
		return tokens[cursor++];
	}

	// Peek the next token in the stream.
	token_t peek() {
		return tokens[cursor];
	}

	// Check if the end-of-file has been reached.
	bool eof() {
		return tokens[cursor].type == tk_eof;
	}

};