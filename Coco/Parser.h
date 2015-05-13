/* 
 * File:   Parser.h
 * Author: orkanone
 *
 * Created on 9. Mai 2015, 09:21
 */

#ifndef PARSER_H
#define	PARSER_H

#include "Token.h"
#include "tok.h"
#include <list>
#include <map>
#include <fstream>
#include <iostream>
using namespace std;

class Parser {
public:
    Parser();
    Token getNextToken();
    void Lexer(string filepath);
    void parse();
private:
    list <Token> tokens;
    map <string, float> symbol_table;
    
};

#endif	/* PARSER_H */

