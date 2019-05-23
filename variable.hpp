#pragma once

// A raw value.
typedef long value_t;

// A variable.
struct variable_t {
	type_t			type;
	identifier_t	identifier;
	value_t			raw;
	long			pointer;
};