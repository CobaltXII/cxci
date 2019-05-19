#pragma once
#include <cstdio>

// Standard function int putchar(int).
variable_t CXCI_STDLIB_putchar(std::vector<variable_t> parameters) {
	putchar(parameters[0].raw);
	return parameters[0];
}