#ifndef PARSER_H
#define PARSER_H

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
void attach_string(std::string key, Node* parent, std::list<Token>* tokens);
void attach_boolean(std::string key, Node* parent, std::list<Token>* tokens);
void parse_object(std::list<Token>* tokens, Node* parent);
void log_abs(Node* root_node);
void parser(std::list<Token>* tokens);

#endif
