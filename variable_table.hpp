#pragma once
#include <vector>

// A symbol table.
struct variable_table_t {
	variable_table_t* parent;
	std::vector<variable_t> symbols;

	// Default constructor.
	variable_table_t(variable_table_t* parent = nullptr) {
		this->parent = parent;
	}

	// Add a symbol.
	void add_symbol(variable_t symbol) {
		symbols.push_back(symbol);
	}

	// Check if a symbol under the specified identifier exists in any scope.
	bool exists(identifier_t identifier) {
		// Search the current scope for the specified identifier.
		for (int i = 0; i < symbols.size(); i++) {
			if (symbols[i].identifier == identifier) {
				return true;
			}
		}
		if (parent) {
			// Search the parent scope for the specified identifier.
			return parent->exists(identifier);
		} else {
			return false;
		}
	}

	// Check if a symbol under the specified identifier exists in this scope.
	bool exists_locally(identifier_t identifier) {
		// Search the current scope for the specified identifier.
		for (int i = 0; i < symbols.size(); i++) {
			if (symbols[i].identifier == identifier) {
				return true;
			}
		}
		return false;
	}

	// Fetch the symbol under the specified identifier.
	variable_t& fetch(identifier_t identifier) {
		// Search the current scope for the specified identifier.
		for (int i = 0; i < symbols.size(); i++) {
			if (symbols[i].identifier == identifier) {
				return symbols[i];
			}
		}
		// Search the parent scope for the specified identifier.
		return parent->fetch(identifier);
	}
};