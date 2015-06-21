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
    list<Token>::iterator GetIt() const {
        return it;
    }

    void SetIt(list<Token>::iterator it) {
        this->it = it;
    }

    string GetName() const {
        return name;
    }

    void SetName(string name) {
        this->name = name;
    }
    
    void SetInput(string param){
        inputParams.push_back(param);
    }
    
    list<string> getInputParams(){
        return this->inputParams;
    }
    
    void setIsVoid(bool param){
        this->isVoid = param;
    }
    
    bool getIsVoid(){
        return isVoid;
    }
    
    map <string, float> symbol_table;
private:
    list<Token>::iterator it; //Zeiger auf lines of code
    string name;
    list<string> inputParams;
    bool isVoid;
    //TODO rücksprung
    
};

#endif	/* FUNCTION_H */

