

#include <stdio.h>
#include <iostream>
#include "Parser.h"
using namespace std;

const string filepath = "/home/orkanone/wat";

int main(int argc, char** argv) {
    Parser myParser;
    myParser.Lexer(filepath);
    myParser.parse();
    return 0;
}

