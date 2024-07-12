#include "../token.h"

std::string parse_string(std::list<Token>* tokens)
{
    read_token(tokens);  // first quote
    std::string str = "";
    Token token = read_token(tokens);

    while (token.type != TokenType::T_QUOTE)
    {
        str += token.value;
        token = read_token(tokens);
    }

    return str;
}
