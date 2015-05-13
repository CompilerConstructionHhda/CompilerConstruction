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
            fin >> noskipws >> ch;
        }
        if (isalpha(ch)) {
            identifier = ch;
            fin >> noskipws >> ch;
            while (isalnum(ch) && !fin.eof()) {
                identifier += ch;
                fin >> noskipws >> ch;
            }
            this->tokens.push_back(Token(identifier, tok_identifier));
        }

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

    }
    if (fin.eof()) {
        cout << "\neof\n";
    }
    fin.close();

    //manually eof

}

void Parser::parse() {
    while (!this->tokens.empty()) {
        Token currentToken = getNextToken();
        if (currentToken.getType() == tok_identifier) {
            cout << currentToken.getIdentifier() << endl;
        }
        if (currentToken.getType() == tok_number) {
            cout << currentToken.getValue() << endl;
        }
    }
}


