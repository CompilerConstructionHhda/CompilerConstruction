/* 
 * File:   Parser.cpp
 * Author: orkanone
 * 
 * Created on 9. Mai 2015, 09:21
 */

#include "Parser.h"

Parser::Parser() {
    /*this->root = new ZNode();
    G2Node* leftchild = new G2Node();
    leftchild->setVar("lala");
    D2Node* leftleftgrandchild = new D2Node();
    
    ENode* rightchild = new ENode();
    FNode* rightleftgrandchild = new FNode();
    E2Node* rightrightgrandchild = new E2Node();
    
    leftchild->setLeft(leftleftgrandchild);
    
    rightchild->setLeft(rightleftgrandchild);
    rightchild->setRight(rightrightgrandchild);
    
    this->root->setLeft(leftchild);
    this->root->setRight(rightchild);
     */    
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
        this->currentNode = this->root;
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
    this->currentNode->setLeft(new G2Node());
    this->currentNode = this->currentNode->getLeft();
    if ((*it).getType() == tok_identifier){
        string var = (*it).getIdentifier();
        bool ret = this->D2();        
        if (ret){
            //es is ne zuweisung
            ++it;
            G2Node* tmp = static_cast<G2Node*> (this->currentNode);
            tmp->setVar(var);
            this->currentNode = this->currentNode->getParent();
            return var;
            
        }
        else {
            it = this->tokens.begin(); //we know it's not an assignment, start from scratch
            this->currentNode = this->currentNode->getParent();
            this->currentNode->setLeft(NULL);
            return "";
        }
    }
    else {
        //we know it's not an assignment, start from scratch
        this->currentNode = this->currentNode->getParent();
        this->currentNode->setLeft(NULL);
        return "";
    }
}

bool Parser::D2(){
    ++it;
    if ((*it).getType() == tok_assign){      
        this->currentNode->setLeft(new D2Node());
        return true;
    }
    else return false;
}

float Parser::E(){
    this->currentNode->setRight(new ENode());
    this->currentNode = this->currentNode->getRight();
    float t = this->T();
    t += this->E2();
    this->currentNode->getParent();
    return t;
    /**
     * 
     * TODO Rechnen
     * @return 
     */
}

float Parser::T(){
    this->currentNode->setLeft(new TNode());
    this->currentNode = this->currentNode->getLeft();
    float f = this->F();
    float t2 = this->T2();
    f *= t2;
    this->currentNode = this->currentNode->getParent();
    return f;
}

float Parser::E2(){
    this->currentNode->setRight(new E2Node());
    this->currentNode = this->currentNode->getRight();
    E2Node* tmp = static_cast<E2Node*>(this->currentNode);
    ++it;
    string op = (*it).getIdentifier();
    float t, e2;
    if (op == "+"){
        ++it;
        tmp->setOperator("+");
        t = this->T();
        e2 = this->E2();
        this->currentNode = this->currentNode->getParent();
        return t + e2;
    }
    else if (op == "-"){
        ++it;
        tmp->setOperator("-");
        t = this->T();
        e2 = this->E2();
        this->currentNode = this->currentNode->getParent();
        return -t + e2;
    }
    else if (';'){
        tmp->setOperator(";");
        this->currentLineValid = true;
        this->currentNode = this->currentNode->getParent();
        return 0;
    }
    
    else {
        return 0;
    }
}

float Parser::T2(){
    this->currentNode->setRight(new T2Node());
    this->currentNode = this->currentNode->getRight();
    T2Node* tmp = static_cast<T2Node*>(this->currentNode);
    ++it;
    string op = (*it).getIdentifier();
    Tok tok = (*it).getType();
    float f, t2;
    if (op == "*"){
        ++it;
        tmp->setOperator("*");
        f = this->F();
        t2 = this->T2();
        this->currentNode = this->currentNode->getParent();
        return f * t2;
    }
    else if (op == "/"){
        ++it;
        tmp->setOperator("/");
        f = this->F();
        t2 = this->T2();
        this->currentNode = this->currentNode->getParent();
        return (1/f) * t2;
    }
    
    else if (tok == tok_identifier || tok == tok_number){
        cerr << "\033[1;31mERROR: Operator expected\033[0m" << endl;
        exit(1);
    }
    
    else {
       std::advance(it, -1);
       this->currentNode = this->currentNode->getParent();
       return 1;
    }
}

float Parser::F(){
    this->currentNode->setLeft(new FNode());
    FNode* tmp = static_cast<FNode*>(this->currentNode->getLeft());
    if ((*it).getType() == tok_number){
        tmp->setID((*it).getValue());
        return (*it).getValue();
    }
    else if ((*it).getType() == tok_identifier) {
        if (this->symbol_table.find( (*it).getIdentifier() ) == this->symbol_table.end()){
            cerr << "\033[1;31mError: Variable does not exist\033[0m" << endl;
            exit(1);
        }
        else {
            tmp->setVar((*it).getIdentifier());
            return this->symbol_table.at( (*it).getIdentifier() );
        }
    }
    
    else {
        cerr << "\033[1;31mERROR: Number or variable expected\033[0m" << endl;
        exit(1);
    }
}

void Parser::printSyntaxTree(){
    this->root->print(0);
}

void Parser::printSymbolTable(){
    map<string, float>::iterator it;
    for(it = symbol_table.begin(); it != symbol_table.end(); it++) {
        cout << it->first << " : " << it->second << endl;
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