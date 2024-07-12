#include <cctype>
#include <cstdio>
#include <list>

#include "parser.h"

int is_utf8_char(char c) { return (c & 0xC0) != 0x80; }

int main()
{
    std::printf("running\n");
    FILE *fptr = std::fopen("./file.json", "r");

    std::list<Token> tokens = tokenize(fptr);

    parser(&tokens);

    std::printf("done\n");
    /* for (auto v : tokens) std::printf("%c", v.value); */
}
