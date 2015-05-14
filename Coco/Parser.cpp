/* 
 * File:   Parser.cpp
 * Author: orkanone
 * 
 * Created on 9. Mai 2015, 09:21
 */

#include "Parser.h"

Parser::Parser() {
}

Token Parser::getNextToken() {
    Token rtrn = this->tokens.front();
    this->tokens.pop_front();
    return rtrn;
}

void Parser::Lexer(string filepath) {
    fstream fin(filepath, fstream::in);
    char ch;
    string identifier;
    while (fin >> noskipws >> ch) {
        while (isspace(ch)) {
            if (ch == '\n') {
                //count lines
            }
            fin >> noskipws >> ch; // get next char
        }
        if (ch == ':'){
            identifier = ch;
            fin >> noskipws >> ch; //get next char
            if (ch == '='){
                identifier += ch;
                this->tokens.push_back(Token(identifier, tok_assign));
            }
        }

        //TODO klammern
        
        if (isalpha(ch)) {
            identifier = ch;
            fin >> noskipws >> ch; //get next char
            while (isalnum(ch) && !fin.eof()) {
                identifier += ch;
                fin >> noskipws >> ch;
            }
            this->tokens.push_back(Token(identifier, tok_identifier));
        }
        
        //int only
        if(isdigit(ch)){
            identifier = ch;
            fin >> noskipws >> ch;
            while (isdigit(ch) && !fin.eof()){
                identifier += ch;
                fin >> noskipws >> ch;
            }
            float val = atof(identifier.c_str());
            this->tokens.push_back(Token(val, tok_number));
                    
        }
        
        if (ch == '+' || ch == '-'){
            identifier = ch;
            this->tokens.push_back(Token(identifier, tok_plus));
        }
        
        if (ch == '*' || ch == '/'){
            identifier = ch;
            this->tokens.push_back(Token(identifier, tok_mult));
        }
        
        if (ch == ';'){
            identifier = ch;
            this->tokens.push_back(Token(identifier, tok_semi));
        }
        

    }
    fin.close();

    //manually eof

}

void Parser::parse(){
    list<Token>::iterator it;
    it = this->tokens.begin();
    it++;
    cout << (*it).getIdentifier() << endl;
    it++;
    cout << (*it).getIdentifier() << endl;
    
}

void Parser::printAndEmptyList() {
    while (!this->tokens.empty()) {
        Token currentToken = getNextToken();
        if (currentToken.getType() == tok_identifier
            || currentToken.getType() == tok_assign 
            || currentToken.getType() == tok_plus
            || currentToken.getType() == tok_mult
            || currentToken.getType() == tok_semi) {
            cout << currentToken.getIdentifier() << endl;
        }
        if (currentToken.getType() == tok_number) {
            cout << currentToken.getValue() << endl;
        }
    }
}


