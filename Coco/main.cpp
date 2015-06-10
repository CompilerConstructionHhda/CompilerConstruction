

#include <stdio.h>
#include <iostream>
#include "Parser.h"
using namespace std;

const string filepath = "test_ok";
//const string filepath = "test_missing_operator";
//const string filepath = "test_missing_operand";
//const string filepath = "test_missing_var";

int main(int argc, char** argv) {
    Parser myParser;
    myParser.Lexer(filepath);
    myParser.parse();
    myParser.printSymbolTable();
    return 0;
}

