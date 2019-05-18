#pragma once
#include <string>
#include <vector>

// All token types.
enum token_type_t {
	// Special tokens.
	tk_identifier,
	tk_lit_integer,
	tk_lit_string,
	tk_lit_character,
	tk_eof,
	// Reserved words.
	tk_if,
	tk_int,
	tk_else,
	tk_while,
	tk_return,
	// Punctuation.
	tk_left_parenthesis,		// (
	tk_right_parenthesis,		// )
	tk_left_bracket,			// [
	tk_right_bracket,			// ]
	tk_left_brace,				// {
	tk_right_brace,				// }
	tk_comma,					// ,
	tk_semicolon,				// ;
	// Binary operators.
	// tk_bi_addition,				// +
	// tk_bi_subtraction,			// -
	// tk_bi_multiplication,		// *
	tk_bi_division,				// /
	tk_bi_modulo,				// %
	tk_bi_assignment,			// =
	tk_bi_logical_and,			// &&
	tk_bi_logical_or,			// ||
	tk_bi_relational_equal,		// ==
	tk_bi_relational_non_equal,	// !=
	// Unary operators.
	// tk_un_value_of				// *
	// tk_un_arithmetic_positive	// +
	// tk_un_arithmetic_negative	// -
	tk_un_address_of,			// &
	tk_un_logical_not,			// !
	// Ambiguous operators.
	tk_plus,					// + | Unary arithmetic positive and binary
								//     addition
	tk_minus,					// - | Unary arithmetic negative and binary
								//     subtraction
	tk_asterisk					// * | Unary value-of and binary
								//     multiplication
};
