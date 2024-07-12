#ifndef PARSER_CPP
#define PARSER_CPP

#include <stdlib.h>

#include <boost/outcome.hpp>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <list>

#include "parser/boolean.h"
#include "parser/string.h"

enum NodeValue
{
    N_ROOT,
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
};

void attach_string(std::string key, Node* parent, std::list<Token>* tokens)
{
    std::string value = parse_string(tokens);

    Node node = Node{};
    node.key = key;
    node.type = N_STRING;

    char* str = new char[value.size() + 1];
    node.value_ptr = static_cast<void*>(str);
    std::strcpy(str, value.c_str());

    parent->children.push_back(node);
};

void attach_boolean(std::string key, Node* parent, std::list<Token>* tokens)
{
    bool value = parse_boolean(tokens);

    Node node = Node{};
    node.type = NodeValue::N_BOOLEAN;
    node.key = key;
    node.value_ptr = static_cast<void*>(&value);
    node.value_size = sizeof(bool);

    parent->children.push_back(node);
}

void parse_object(std::list<Token>* tokens, Node* parent)
{
    /* Token token = tokens.front(); */
    /* tokens.pop_front(); */
    /* if (token.type != TokenType::T_LEFT_CURLY_BRACE) */
    /* { */
    /*     return -1; */
    /* } */

    Token token = peek_token(tokens);
    assert_token(token, TokenType::T_QUOTE);

    std::string key = parse_string(tokens);

    token = read_token(tokens);
    assert_token(token, TokenType::T_COLON);
    token = peek_token(tokens);

    if (token.type == TokenType::T_QUOTE)
    {
        attach_string(key, parent, tokens);
    }
    else if (token.type == TokenType::T_IDENTIFIER && is_boolean(&token))
    {
        attach_boolean(key, parent, tokens);
    }

    token = read_token(tokens);
    assert_terminator_token(token);

    if (token.type == TokenType::T_COMMA)
    {
        parse_object(tokens, parent);
    }
    else if (token.type == TokenType::T_RIGHT_CURLY_BRACE)
    {
        return;
    }
}

void log_abs(Node* root_node)
{
    switch (root_node->type)
    {
        case N_ROOT:
            break;
        case N_OBJECT:
            break;
        case N_STRING:
            std::printf("%s\n", static_cast<char*>(root_node->value_ptr));
        case N_NUMBER:
            break;
        case N_BOOLEAN:
            std::printf("%s\n", static_cast<bool>(root_node->value_ptr) ? "true" : "false");
            break;
        case N_NULL:
            break;
        case N_ARRAY:
            break;
    }
    for (auto& child : root_node->children)
    {
        log_abs(&child);
    }
}

void parser(std::list<Token>* tokens)
{
    Node root = Node{};
    root.type = NodeValue::N_ROOT;
    root.children = std::list<Node>();

    read_token(tokens);

    parse_object(tokens, &root);
    std::printf("root: %ld\n", root.children.size());
    log_abs(&root);
}

#endif
