#ifndef TOKEN_CPP
#define TOKEN_CPP

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

std::list<Token> tokenize(FILE* fptr)
{
    std::list<Token> tokens = std::list<Token>();
    int line = 1;
    int column = 1;
    for (int c = std::fgetc(fptr); c != EOF; c = std::fgetc(fptr))
    {
        Token token = Token{};
        token.line = line;
        token.value = c;
        token.column = column;

        int is_space = std::isspace(c);

        switch (c)
        {
            case '{':
                token.type = TokenType::T_LEFT_CURLY_BRACE;
                tokens.push_back(token);
                break;
            case '}':
                token.type = TokenType::T_RIGHT_CURLY_BRACE;
                tokens.push_back(token);
                break;
            case '[':
                token.type = TokenType::T_LEFT_SQUARE_BRACKET;
                tokens.push_back(token);
                break;
            case ']':
                token.type = TokenType::T_RIGHT_SQUARE_BRACKET;
                tokens.push_back(token);
                break;
            case ',':
                token.type = TokenType::T_COMMA;
                tokens.push_back(token);
                break;
            case '"':
                token.type = TokenType::T_QUOTE;
                tokens.push_back(token);
                break;
            case ':':
                token.type = TokenType::T_COLON;
                tokens.push_back(token);
                break;
            default:
                if (is_space)
                    break;
                token.type = TokenType::T_IDENTIFIER;
                tokens.push_back(token);
                break;
        }
        line++;
        column++;
    }

    return tokens;
}

std::string token_type_string(TokenType type)
{
    switch (type)
    {
        case TokenType::T_COLON:
            return "COLON";
        case TokenType::T_COMMA:
            return "COMMA";
        case TokenType::T_QUOTE:
            return "QUOTE";
        case TokenType::T_LEFT_CURLY_BRACE:
            return "LEFT_CURLY_BRACE";
        case TokenType::T_RIGHT_CURLY_BRACE:
            return "RIGHT_CURLY_BRACE";
        case TokenType::T_LEFT_SQUARE_BRACKET:
            return "LEFT_SQUARE_BRACKET";
        case TokenType::T_RIGHT_SQUARE_BRACKET:
            return "RIGHT_SQUARE_BRACKET";
        case TokenType::T_IDENTIFIER:
            return "IDENTIFIER";
    }
    return "UNKNOWN";
}

void assert_token(Token token, TokenType expected)
{
    std::string expected_str = token_type_string(expected);
    if (token.type != expected)
    {
        throw std::runtime_error("Expected token type");
    }
}
void assert_terminator_token(Token token)
{
    if (token.type != TokenType::T_COMMA && token.type != TokenType::T_RIGHT_CURLY_BRACE)
    {
        std::printf("expected comma or right curly brace got: %c (%s)\n", token.value,
                    token_type_string(token.type).c_str());
        exit(1);
    }
}

Token read_token(std::list<Token>* tokens)
{
    Token token = tokens->front();
    tokens->pop_front();

    return token;
}
Token peek_token(std::list<Token>* tokens) { return tokens->front(); }

#endif
