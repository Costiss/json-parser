#include <cctype>
#include <cstdio>
#include <iostream>
#include <list>

enum TokenType
{
    T_IDENTIFIER,
    T_LEFT_CURLY_BRACE,
    T_RIGHT_CURLY_BRACE,
    T_LEFT_SQUARE_BRACKET,
    T_RIGHT_SQUARE_BRACKET,
    T_COMMA,
    T_QUOTE,
    T_COLON,
};

struct Token
{
    TokenType type;
    char value;
    int line;
    int column;
};

std::list<Token> tokenize(FILE *fptr);
std::string token_type_string(TokenType type);
