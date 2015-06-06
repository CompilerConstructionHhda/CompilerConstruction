/* 
 * File:   Parser.h
 * Author: orkanone
 *
 * Created on 9. Mai 2015, 09:21
 */

#ifndef PARSER_H
#define	PARSER_H

#include "TreeNode.h"
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
    Token getCurrentToken();
    Token getNextToken();
    void Lexer(string filepath);
    void printAndEmptyList();
    void parse(); //primary node Z()
    
    string G2(); //is it an assignment or not
    bool D2(); // := or nothing
    float E(); // 
    float E2(); // +TE2 or -TE2 or nothing or ;
    float T();
    float T2();  // *FT2 or /FT2 or nothing or ;
    float F();  // E or id or var
private:
    list <Token> tokens;
    map <string, float> symbol_table;
    list<Token>::iterator it;
    bool currentLineValid;
    TreeNode* currentTreeNode;
    TreeNode* firstTreeNode;
};

#endif	/* PARSER_H */

