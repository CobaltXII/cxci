#pragma once
#include <iostream>

// A block of random-access-memory.
struct memory_t {
	value_t* cells;
	long size;
	long data_offset;
	
	// Default constructor.
	memory_t(long size = 1024 * 1024) {
		this->size = size;
		cells = new value_t[size];
		if (!cells) {
			std::cerr << "could not allocate memory" << std::endl;
			exit(4);
		}
	}
};