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

	// Checks if a character can be used anywhere in an identifier besides the
	// first character. Any value x where chr_id_start(x) == true must also
	// satisfy chr_id(x) == true.
	static bool chr_id(int ch) {
		return (ch >= 'a' && ch <= 'z') ||
			   (ch >= 'A' && ch <= 'Z') ||
			   (ch >= '0' && ch <= '9') ||
			   ch == '_';
	}

	// Checks is a character is whitespace.
	static bool chr_whitespace(int ch) {
		return ch == ' ' || ch == '\t' || ch == '\n';
	}

	// Reads from the character stream until the predicate returns false or
	// the end-of-file has been reached.
	std::string read_while(bool (*predicate)(int)) {
		std::string str = "";
		while (!input.eof() && predicate(input.peek())) {
			str += input.next();
		}
		return str;
	}

	// Reads an identifier.
	token_t read_identifier() {
		std::string str = read_while(chr_id);
		if (str == "if") {
			return {tk_if, str, TOKEN_DEBUG};
		} else if (str == "int") {
			return {tk_int, str, TOKEN_DEBUG};
		} else if (str == "else") {
			return {tk_else, str, TOKEN_DEBUG};
		} else if (str == "while") {
			return {tk_while, str, TOKEN_DEBUG};
		} else if (str == "return") {
			return {tk_return, str, TOKEN_DEBUG};
		} else {
			return {tk_identifier, str, TOKEN_DEBUG};
		}
	}

	// Reads an integer literal.
	token_t read_lit_integer() {
		return {
			tk_lit_integer,
			read_while(chr_digit),
			TOKEN_DEBUG
		};
	}

	// Reads an escaped string/character literal. The start and end quotes are
	// not included in the token text.
	std::string read_escaped(int quote) {
		bool escaped = false;
		std::string str = "";
		input.next();
		while (!input.eof()) {
			int ch = input.next();
			if (escaped) {
				str += ch;
				escaped = false;
			} else if (ch == '\\') {
				escaped = true;
			} else if (ch == quote) {
				break;
			} else {
				str += ch;
			}
		}
		return str;
	}

	// Reads a string literal.
	token_t read_lit_string() {
		return {
			tk_lit_string,
			read_escaped('"'),
			TOKEN_DEBUG
		};
	}

	// Reads a character literal.
	token_t read_lit_character() {
		return {
			tk_lit_character,
			read_escaped('\''),
			TOKEN_DEBUG
		};
	}

	// Skips whitespace.
	void skip_whitespace() {
		read_while(chr_whitespace);
	}
};

#undef TOKEN_DEBUG