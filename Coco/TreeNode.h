/* 
 * File:   TreeNode.h
 * Author: coolpharaoh
 *
 * Created on June 6, 2015, 10:16 AM
 */

#ifndef TREENODE_H
#define	TREENODE_H
#include <iostream>

using namespace std;
class TreeNode {
public:
    TreeNode(){
        this->Parent = NULL;
        this->Left = NULL;
        this->Right = NULL;
    }
    
    TreeNode* getLeft() const {
        return Left;
    }

    void setLeft(TreeNode* Left) {
        this->Left = Left;
        Left->setParent(this);
        
    }

    TreeNode* getParent() const {
        return Parent;
    }

    void setParent(TreeNode* Parent) {
        this->Parent = Parent;
    }

    TreeNode* getRight() const {
        return Right;
    }

    void setRight(TreeNode* Right) {
        this->Right = Right;
        Right->setParent(this);
    }
    
    virtual void print(int count) = 0;

protected:
    TreeNode* Left;
    TreeNode* Right;
    TreeNode* Parent;
};

class ZNode : public TreeNode {
public:
    ZNode(){
        
    }
    void print(int count){
        for (int i = 0; i < count; i++){
            cout << "\t";
        }
        cout << "Z" << endl;
        count++;
        if (this->Left != NULL){
            this->Left->print(count);
        }
        if (this->Right != NULL){
            this->Right->print(count);
        }
    }
private:
};

class G2Node : public TreeNode {
public:
    G2Node(){
    
    }
    void setVar(string var){
        this->var = var;
    }

    virtual void print(int count){
        for (int i = 0; i < count; i++){
            if (i == count-1){
                cout <<"|----";
            }
            else cout << "\t";
        }
        
        cout << "G2";
        if (this->var != ""){
        cout << "____identifier: " << this->var;
        }
        cout << endl;
        count++;
        if (this->Left != NULL){
            this->Left->print(count);
        }
        if (this->Right != NULL){
            this->Right->print(count);
        }
    }
    
private:
    string var = "";
};

class D2Node : public TreeNode {
public:
    D2Node(){}
    
    void setOperator(string Operator){
        this->Operator = Operator;
    }
    
    virtual void print(int count){
        for (int i = 0; i < count; i++){
            if (i == count-1){
                cout <<"|----";
            }
            else cout << "\t";
        
        }
        cout << "D ";
        if (this->Operator != ""){
            cout << "____ " << this->Operator;
        }
        cout << endl;
        count++;
        if (this->Left != NULL){
            this->Left->print(count);
        }
        if (this->Right != NULL){
            this->Right->print(count);
        }
    }
private:
    string Operator = "";
};

class ENode : public TreeNode {
public:
    ENode(){}   
    virtual void print(int count){
        for (int i = 0; i < count; i++){
            if (i == count-1){
                cout <<"|----";
            }
            else cout << "\t";
        }
        cout << "E" << endl;
        count++;
        if (this->Left != NULL){
            this->Left->print(count);
        }
        if (this->Right != NULL){
            this->Right->print(count);
        }
    }
private:
};

class E2Node : public TreeNode {
public:
    E2Node(){}
    
    void setOperator(string Operator){
        this->Operator = Operator;
    }
    
    virtual void print(int count){
        for (int i = 0; i < count; i++){
            if (i == count-1){
                cout <<"|----";
            }
            else cout << "\t";
        }
        cout << "E'";
        if (this->Operator != ""){
            cout << " ____ " << this->Operator;
        }
        cout << endl;
        count++;
        if (this->Left != NULL){
            this->Left->print(count);
        }
        if (this->Right != NULL){
            this->Right->print(count);
        }
    }
private:
    string Operator = "";
};

class TNode : public TreeNode {
public:
    TNode(){}    
    virtual void print(int count){
        for (int i = 0; i < count; i++){
                if (i == count-1){
                cout <<"|----";
            }
            else cout << "\t";
        }
        cout << "T" << endl;
        count++;
        if (this->Left != NULL){
            this->Left->print(count);
        }
        if (this->Right != NULL){
            this->Right->print(count);
        }
    }
private:
};

class T2Node : public TreeNode {
public:
    T2Node(){}
    
    void setOperator(string Operator){
        this->Operator = Operator;
    }
    
    virtual void print(int count){
        for (int i = 0; i < count; i++){
             if (i == count-1){
                cout <<"|----";
            }
            else cout << "\t";
        }
        cout << "T' ";
        if (this->Operator != ""){
            cout << "____" << this->Operator;
        }
        cout << endl;
        count++;
        if (this->Left != NULL){
            this->Left->print(count);
        }
        if (this->Right != NULL){
            this->Right->print(count);
        }
    }
private:
    string Operator = "";
};

class FNode : public TreeNode {
public:
    FNode(){}
    
    void setVar(string var){
        this->var = var;
    }

    void setID(int id){
        this->id = id;
    }

    virtual void print(int count){
        for (int i = 0; i < count; i++){
                if (i == count-1){
                cout <<"|----";
            }
            else cout << "\t";
        }
        if(var != "")
            cout << "F ____ var: " << this->var << endl;
        else
            cout << "F ____ number: " << this->id << endl;
        count++;
        if (this->Left != NULL){
            this->Left->print(count);
        }
        if (this->Right != NULL){
            this->Right->print(count);
        }
    }
private:
    string var = "";
    int id;
};
#endif	/* TREENODE_H */


