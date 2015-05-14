

#include <stdio.h>
#include <iostream>
#include "Parser.h"
using namespace std;

const string filepath = "wat";
//whassuuuuuuuuuuuup
int main(int argc, char** argv) {
    Parser myParser;
    myParser.Lexer(filepath);
    //myParser.printAndEmptyList();
    myParser.parse();
    return 0;
}

