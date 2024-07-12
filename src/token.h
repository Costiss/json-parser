#ifndef TOKEN_H
#define TOKEN_H
#include <cctype>
#include <cstdio>
#include <list>
#include <stdexcept>
#include <string>

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
std::list<Token> tokenize(FILE* fptr);
std::string token_type_string(TokenType type);
void assert_token(Token token, TokenType expected);
void assert_terminator_token(Token token);

Token read_token(std::list<Token>* tokens);
Token peek_token(std::list<Token>* tokens);

#endif
