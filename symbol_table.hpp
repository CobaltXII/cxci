#pragma once
#include <vector>

// A symbol.
struct symbol_t {
	type_t						type;
	identifier_t				identifier;
	std::vector<parameter_t> 	parameters;
	bool						is_function = false;

	symbol_t(type_t type, identifier_t identifier) {
		this->type = type;
		this->identifier = identifier;
	}

	symbol_t(type_t type, identifier_t identifier, std::vector<parameter_t> parameters) {
		this->type = type;
		this->identifier = identifier;
		this->parameters = parameters;
		is_function = true;
	}
};

// A symbol table.
struct symbol_table_t {
	symbol_table_t* parent;
	std::vector<symbol_t> symbols;

	// Default constructor.
	symbol_table_t(symbol_table_t* parent = nullptr) {
		this->parent = parent;
	}

	// Add a symbol.
	void add_symbol(symbol_t symbol) {
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
	symbol_t& fetch(identifier_t identifier) {
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