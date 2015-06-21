/* 
 * File:   Function.h
 * Author: orkanone
 *
 * Created on 21. Juni 2015, 14:17
 */

#ifndef FUNCTION_H
#define	FUNCTION_H

#include <list>
#include <map>
#include "Token.h"
using namespace std;
class Function {
public:
    Function();
private:
    list<Token>::iterator it; //Zeiger auf lines of code
    string name;
    int params_count;
    map <string, float> symbol_table;
    //TODO rücksprung
    
};

#endif	/* FUNCTION_H */

