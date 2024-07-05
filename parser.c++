#include <boost/outcome.hpp>
#include <cctype>
#include <cstdio>
#include <iostream>
#include <list>

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

    std::list<Node> children;
    int child_count;
};

void assert_token(Token token, TokenType expected)
{
    std::string expected_str = token_type_string(expected);
    if (token.type != expected)
    {
        throw std::runtime_error("Expected token type");
    }
}

Token read_token(std::list<Token>* tokens)
{
    Token token = tokens->front();
    tokens->pop_front();

    return token;
}

std::string read_string(std::list<Token>* tokens)
{
    std::string key = "";
    Token token = read_token(tokens);

    while (token.type != TokenType::T_QUOTE)
    {
        key += token.value;
        token = read_token(tokens);
    }

    return key;
}

void parse_object(std::list<Token>* tokens, Node* parent)
{
    /* Token token = tokens.front(); */
    /* tokens.pop_front(); */
    /* if (token.type != TokenType::T_LEFT_CURLY_BRACE) */
    /* { */
    /*     return -1; */
    /* } */

    Node node = Node{};
    Token token = read_token(tokens);
    assert_token(token, TokenType::T_QUOTE);

    std::string key = read_string(tokens);
    node.key = key;

    token = read_token(tokens);
    assert_token(token, TokenType::T_COLON);
    token = read_token(tokens);
    switch (token.type)
    {
        case TokenType::T_QUOTE:
            std::string val = read_string(tokens);
            node.type = NodeValue::N_STRING;
            node.value_ptr = new std::string(val);
            node.value_size = val.size();
    }
    parent->children.push_back(node);
}

void parser(std::list<Token>* tokens)
{
    Node root = Node{};
    root.type = NodeValue::N_OBJECT;
    root.children = std::list<Node>();
    root.child_count = 0;

    read_token(tokens);

    parse_object(tokens, &root);

    std::string key = root.children.back().key;
    std::cout << key << std::endl;
}
