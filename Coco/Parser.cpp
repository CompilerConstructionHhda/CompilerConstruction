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
        
        while (isspace(ch) && !fin.eof()) {
            if (ch == '\n') {
                // count lines
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
    
    while (!this->tokens.empty()){
        this->currentLineValid = false;
        this->it = this->tokens.begin();
        this->root = new ZNode();
        string var;
        float rechnung;
        var = this->G2();
        rechnung = E();
        if (this->currentLineValid && var != ""){
            this->symbol_table[var] = rechnung;
        }
        
        else {
            cout << rechnung << endl;
        }
        
        Token t = this->tokens.front();
        while (t.getType() != tok_semi){
            this->tokens.pop_front();
            t = this->tokens.front();
        }
        this->tokens.pop_front();
    //löschen der zeile bis semikolon
    }
}

string Parser::G2(){
    if ((*it).getType() == tok_identifier){
        string var = (*it).getIdentifier();
        bool ret = this->D2();        
        if (ret){
            //es is ne zuweisung
            ++it;
            return var;
        }
        else {
            it = this->tokens.begin(); //we know it's not an assignment, start from scratch
            return "";
        }
    }
    else {
        //we know it's not an assignment, start from scratch
        return "";
    }
}

bool Parser::D2(){
    ++it;
    if ((*it).getType() == tok_assign){
        return true;
    }
    else return false;
}

float Parser::E(){
    
    float t = this->T();
    t += this->E2();
    return t;
    /**
     * 
     * TODO Rechnen
     * @return 
     */
}

float Parser::T(){
    float f = this->F();
    float t2 = this->T2();
    f *= t2;
    return f;
}

float Parser::E2(){
    ++it;
    string op = (*it).getIdentifier();
    float t;
    if (op == "+"){
        ++it;
        t = this->T();
        return t + this->E2();
    }
    else if (op == "-"){
        ++it;
        t = this->T();
        return -t + this->E2();
    }
    else if (';'){
        this->currentLineValid = true;
        return 0;
    }
    
    else {
        return 0;
    }
}

float Parser::T2(){
    ++it;
    string op = (*it).getIdentifier();
    Tok tok = (*it).getType();
    float f;
    if (op == "*"){
        ++it;
        f = this->F();
        return f * this->T2();
    }
    else if (op == "/"){
        ++it;
        f = this->F();
        return (1/f) * this->T2();
    }
    
    else if (tok == tok_identifier || tok == tok_number){
        cerr << "\033[1;31mERROR: Operator expected\033[0m" << endl;
        exit(1);
    }
    
    else {
       std::advance(it, -1); 
       return 1;
    }
}

float Parser::F(){
    if ((*it).getType() == tok_number){
        return (*it).getValue();
    }
    else if ((*it).getType() == tok_identifier) {
        if (this->symbol_table.find( (*it).getIdentifier() ) == this->symbol_table.end()){
            cerr << "\033[1;31mError: Variable does not exist\033[0m" << endl;
            exit(1);
        }
        else {
            return this->symbol_table.at( (*it).getIdentifier() );
        }
    }
    
    else {
        cerr << "\033[1;31mERROR: Number or variable expected\033[0m" << endl;
        exit(1);
    }
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