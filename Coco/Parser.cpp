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
        
        //lex strings
        if (isalpha(ch)) {
            identifier = ch;
            fin >> noskipws >> ch; 
            while (isalnum(ch) && !fin.eof()) {
                identifier += ch;
                fin >> noskipws >> ch;
                //lex function declarations
                if (identifier == "func"){
                    if (ch == ' '){
                        this->tokens.push_back(Token(identifier, tok_func_decl));
                        fin >> noskipws >> ch;
                        identifier = "";
                    }
                }
                if (identifier == "return"){
                    if (ch == ' '){
                        this->tokens.push_back(Token(identifier, tok_return));
                        //fin >> noskipws >> ch;
                        identifier ="";
                        break;
                    }
                }
            }
            if (identifier != ""){
            this->tokens.push_back(Token(identifier, tok_identifier));
            }
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
     
        if (ispunct(ch)){
            Tok t;
            string ident = "";
            ident += ch;
            switch (ch){
                case '(': this->tokens.push_back(Token(ident, tok_left_par)); 
                    break;
                case ')': this->tokens.push_back(Token(ident, tok_right_par)); 
                    break;
                case '{': this->tokens.push_back(Token(ident, begin_code_block)); 
                    break;
                case '}': this->tokens.push_back(Token(ident, end_code_block));
                    break;
                case ',': this->tokens.push_back(Token(ident, tok_comma));
                    break;
            }
        }

    }
    this->tokens.push_back((Token("eof", tok_eof)));
    fin.close();

    //manually eof

}

void Parser::parseFunctions(){
    this->it = this->tokens.begin();
    while ((*it).getType() != tok_eof){
        this->func();
    }
}

void Parser::startMain(){
    if (function_table.find("main") == function_table.end()){
        cerr << "\033[1;31mERROR: No main function\033[0m" << endl;
        exit(1);
    }
    this->currentFunction = function_table["main"];
    this->parse(this->currentFunction->GetIt());
    
}

void Parser::func(){
    if((*it).getType() == tok_func_decl){
        this->currentFunction = new Function();
        it++;
        funcName();
        if((*it).getType() == begin_code_block){
            it++;
            this->currentFunction->SetIt(it);
            while ((*it).getType() != end_code_block){
                if ((*it).getType() == tok_eof){
                    cerr << "\033[1;31mERROR: End of file before function ends\033[0m" << endl;
                    exit(1); 
                }
                
                if ((*it).getType() == tok_identifier && (*it).getIdentifier() == "return"){
                    this->currentFunction->setIsVoid(false);
                }
                it++;
            }
            it++;
            //end code block found
            function_table[this->currentFunction->GetName()] = this->currentFunction;
            return;
        }else{
            cout << "Funktion ist nicht richtig!" << endl;
        }
    }else{
        cout << "Fail hier ist ein func" << endl;
    }
}

void Parser::funcName(){
    if((*it).getType() == tok_identifier){
        this->currentFunction->SetName((*it).getIdentifier());
        it++;
        if((*it).getType() == tok_left_par){
            it++;
            param(false);
        }else{
            cout << "Nach dem Namen kommt ein Klammer" << endl;
        }
    }else {
        cout << "Function hat keinen Namen" << endl;
    }
}

void Parser::param(bool lastIsComma){
    if((*it).getType() == tok_right_par && !lastIsComma){
        it++;
        return;
    }else if((*it).getType() == tok_identifier){
        this->currentFunction->SetInput((*it).getIdentifier());
        it++;
        if((*it).getType() == tok_comma){
            it++;
            param(true);
        }else if((*it).getType() == tok_right_par){
            it++;
            return;
        }else{
            cout << "Klammer oder Komma verlangt" << endl;
        }
    }
}

float Parser::parse(list<Token>::iterator itparam){ 
    this->it = itparam;
    while ((*it).getType() != tok_eof && (*it).getType() != end_code_block){
        this->currentLineValid = false;
        
        //it is func_declaration?
        //parse function
        
        this->root.push_back(new ZNode());
        this->currentNode = this->root.back();
        string var;
        float rechnung;
        
        if ((*it).getType() == tok_return){
            it++;
            return E();
        }
        
        else{

            var = this->G2();
            rechnung = E();

            if (this->currentLineValid && var != ""){
                this->currentFunction->symbol_table[var] = rechnung;
            }

            //if func !isvoid : return float

            else {
                cout << rechnung << endl;
            }
        }
        it++;
        /*
        Token t = this->tokens.front();
        while (t.getType() != tok_semi){
            this->tokens.pop_front();
            t = this->tokens.front();
        }
        this->tokens.pop_front();
    //löschen der zeile bis semikolon
         * */
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
            it--;
            //it = this->tokens.begin(); //we know it's not an assignment, start from scratch
            this->currentNode = this->currentNode->getParent();
            return "";
        }
    }
    else {
        //we know it's not an assignment, start from scratch
        this->currentNode = this->currentNode->getParent();
        return "";
    }
}

bool Parser::D2(){
    this->currentNode->setLeft(new D2Node());
    this->currentNode = this->currentNode->getLeft();
    D2Node* tmp = static_cast<D2Node*>(this->currentNode);
    ++it;
    if ((*it).getType() == tok_assign){  
        tmp->setOperator(":=");
        this->currentNode = this->currentNode->getParent();
        return true;
    }
    else{
        this->currentNode = this->currentNode->getParent();
        return false;
    }
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
        string identifier = (*it).getIdentifier();
        it++;
        if ((*it).getType() == tok_left_par){
            //MOFO function call!
            //Function* nextfunction = new Function();
            //nextfunction = this->function_table[ identifier ];
            it++;
            list<string>::iterator iter;
            list<string> inputParams = this->function_table[ identifier ]->getInputParams();
            for (iter = inputParams.begin(); iter != inputParams.end(); iter++){
                if ( (*it).getType() == tok_identifier || (*it).getType() == tok_number){
                    this->function_table[ identifier ]->symbol_table[(*iter)] = F();
                    it++;
                    if ((*it).getType() == tok_comma){
                        it++;
                        continue;
                    }
                    else if ((*it).getType() == tok_right_par){
                        it++;
                        break;
                    }
                }
                else {
                   cerr << "\033[1;31mError: Unexpected token in function call\033[0m" << endl;
                   exit(1);
                }
                
            }
            
            //save iterator (rücksprung)
            list<Token>::iterator saved_it = this->it;
            //save currentFunction
            Function* saved_function = this->currentFunction;
            //currentFunction = nextfunction
            this->currentFunction = this->function_table[ identifier ];
            //funktion ausführen
            float returnparam = parse(this->currentFunction->GetIt());
            
            //get old values
            this->it = saved_it;
            this->currentFunction = saved_function;
            
            it--;
            //return funktionsergebnis
            /*
             Missing:
             * 2 Funktionen in einer Zeile
             * Funktion ohne Parameter
             * Zahlen nicht returnbar
             
             */
            return returnparam;
            
        }
        
        else {
            it--;
        }
        
        if (this->currentFunction->symbol_table.find( (*it).getIdentifier() ) == this->currentFunction->symbol_table.end()){
            cerr << "\033[1;31mError: Variable does not exist\033[0m" << endl;
            exit(1);
        }
        else {
            tmp->setVar((*it).getIdentifier());
            return this->currentFunction->symbol_table.at( (*it).getIdentifier() );
        }
    }
    
    else {
        cerr << "\033[1;31mERROR: Number or variable expected\033[0m" << endl;
        exit(1);
    }
}

void Parser::printSyntaxTree(){
    for(int i=0; i<root.size(); i++){
        this->root.at(i)->print(0);
    }
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
        if (currentToken.getType() != tok_number) {
            cout << currentToken.getIdentifier();
        }
        if (currentToken.getType() == tok_number) {
            cout << currentToken.getValue();
        }
        cout << " is " << currentToken.getType() << endl;
    }
}

void Parser::printFunctions(){
    map<string, Function*>::iterator it;
    for (it = function_table.begin(); it != function_table.end(); it++){
        cout << "Func Name: " << it->first << "; Func: " << it->second->GetIt()->getType() << endl;
    }
}