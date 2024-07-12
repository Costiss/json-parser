#include <cstdio>
#include <string>

#include "../errors.c++"
#include "../token.h"

int is_boolean(Token* token)
{
    char val = token->value;
    if (val == 't' || val == 'f')
        return 1;
    return 0;
}

bool parse_boolean(std::list<Token>* tokens)
{
    int counter = 0;
    std::string str = new char[4];

    Token curr = peek_token(tokens);

    while (curr.value != 'e')
    {
        if (str.size() > 5)
            break;

        curr = read_token(tokens);
        str.push_back(curr.value);
    }

    if (str == "true")
        return true;
    else if (str == "false")
        return false;
    else
        throw new ParsingError("Expected true or false");
}
