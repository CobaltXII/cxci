#pragma once
#include <string>
#include <iostream>

// All available colors.
enum ansi_color_t {
	black,
	red,
	green,
	yellow,
	blue,
	magenta,
	cyan,
	white,
	bold_black,
	bold_red,
	bold_green,
	bold_yellow,
	bold_blue,
	bold_magenta,
	bold_cyan,
	bold_white,
	reset
};

// All available color escape codes.
std::string ansi_color_code[] = {
	"\x1b[30m",
	"\x1b[31m",
	"\x1b[32m",
	"\x1b[33m",
	"\x1b[34m",
	"\x1b[35m",
	"\x1b[36m",
	"\x1b[37m",
	"\x1b[30;1m",
	"\x1b[31;1m",
	"\x1b[32;1m",
	"\x1b[33;1m",
	"\x1b[34;1m",
	"\x1b[35;1m",
	"\x1b[36;1m",
	"\x1b[37;1m",
	"\x1b[0m"
};
