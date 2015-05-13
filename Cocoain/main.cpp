

#include <stdio.h>
#include <iostream>
#icnlude <string.h>
#include "Parser.h"
using namespace std;

const string filepath = "/home/orkanone/wat";

int main(int argc, char** argv) {
    Parser myParser;
    myParser.Lexer(filepath);
    myParser.parse();
    /*Kommentare Kommentiere Klub*/
    return 0;
}

