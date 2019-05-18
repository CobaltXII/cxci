#pragma once
#include <string>
#include <iostream>

// A character stream.
struct char_stream_t {
	std::string buffer;
	long cursor = 0;
	long lineno = 0;
	long colno = 0;

	// Default constructor.
	char_stream_t(std::string buffer = "") {
		this->buffer = buffer;
	}

	// Get the next character in the stream and increment the cursor, line
	// number and column number.
	int next() {
		int ch = buffer[cursor++];
		if (ch == '\n') {
			lineno++;
			colno = 0;
		} else {
			colno++;
		}
		return ch;
	}

	// Peek the next character in the stream.
	int peek() {
		return buffer[cursor];
	}

	// Peek the character after the next character in the stream.
	int peek_two() {
		return buffer[cursor + 1];
	}

	// Check if the end-of-file has been reached.
	bool eof() {
		return cursor >= buffer.size();
	}

	// Print an error message along with the current line number and character
	// number of the character stream, then exit.
	void die(std::string error) {
		std::cerr << error << " on line " << lineno << ", column " << colno << std::endl;
		exit(1);
	}
};