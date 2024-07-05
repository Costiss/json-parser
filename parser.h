#include <boost/outcome.hpp>
#include <cctype>
#include <cstdio>
#include <iostream>

#include "token.h"

enum NodeValue
{
    N_OBJECT,
    N_STRING,
    N_NUMBER,
    N_BOOLEAN,
    N_NULL,
    N_ARRAY
};

struct Node
{
    NodeValue type;
    std::string key;
    void* value_ptr;
    int value_size;

    Node** children;
    int child_count;
};

void assert_token(Token token, TokenType expected);
Token read_token(std::list<Token>* tokens);
std::string read_string(std::list<Token>* tokens);
void parse_object(std::list<Token>* tokens, Node* parent);
void parser(std::list<Token>* tokens);
