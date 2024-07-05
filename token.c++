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

std::list<Token> tokenize(FILE *fptr)
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
