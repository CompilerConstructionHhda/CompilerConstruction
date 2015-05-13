/* 
 * File:   Token.cpp
 * Author: orkanone
 * 
 * Created on 9. Mai 2015, 09:18
 */

#include "Token.h"

Token::Token(string identifier, Tok type) {
    this->identifier = identifier;
    this->value = 0;
    this->type = type;
}

Token::Token(float value, Tok type){
    this->identifier = "";
    this->value = value;
    /*Kommentare Kommentiere Klub*/
    this->type = type;
}

string Token::getIdentifier(){
    return this->identifier;
}

Tok Token::getType(){
    return this->type;
}

float Token::getValue() {
    return this->value;
}

