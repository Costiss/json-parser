#ifndef PARSER_BOOLEAN_H
#define PARSER_BOOLEAN_H

#include <string>

#include "../errors.c++"
#include "../token.h"

int is_boolean(Token* token);
void _assert_boolean_char(char c, char expected);
void _assert_true_indent(std::string chars);
void _assert_false_indent(std::string chars);
bool parse_boolean(std::list<Token>* tokens);

#endif
