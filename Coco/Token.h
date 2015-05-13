/* 
 * File:   Token.h
 * Author: orkanone
 *
 * Created on 9. Mai 2015, 09:18
 */

#ifndef TOKEN_H
#define	TOKEN_H

#include <string>
#include "tok.h"
using namespace std;

class Token {
public:
    Token(string identifier, Tok type);
    Token(float value, Tok type);
    string getIdentifier();
    Tok getType();
    float getValue();
private:
    string identifier;
    float value;
    Tok type;
    
};

#endif	/* TOKEN_H */

