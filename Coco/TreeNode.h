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
    TreeNode(){}
    
    TreeNode* getLeft() const {
        return Left;
    }

    void setLeft(TreeNode* Left) {
        this->Left = Left;
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
    }
    
    void deleteLeft(){
        delete Left;
        Left = NULL;
    }
    
    void deleteRight(){
        delete Right;
        Right = NULL;
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
        cout << "ZNode" << endl;
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
            cout << "\t";
        }
        cout << "G2Node: " << this->var << endl;
        count++;
        if (this->Left != NULL){
            this->Left->print(count);
        }
        if (this->Right != NULL){
            this->Right->print(count);
        }
    }
    
private:
    string var;
};

class D2Node : public TreeNode {
public:
    D2Node(){}
    
    virtual void print(int count){
        for (int i = 0; i < count; i++){
            cout << "\t";
        }
        cout << "D2Node" << this->Semicolon << endl;
        count++;
        if (this->Left != NULL){
            this->Left->print(count);
        }
        if (this->Right != NULL){
            this->Right->print(count);
        }
    }
private:
    string Semicolon = ":=";
};

class ENode : public TreeNode {
public:
    ENode(){}   
    virtual void print(int count){
        for (int i = 0; i < count; i++){
            cout << "\t";
        }
        cout << "ENode" << endl;
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
    virtual void print(int count){
        for (int i = 0; i < count; i++){
            cout << "\t";
        }
        cout << "E2Node" << endl;
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

class TNode : public TreeNode {
public:
    TNode(){}    
    virtual void print(int count){
        for (int i = 0; i < count; i++){
            cout << "\t";
        }
        cout << "TNode" << endl;
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
    virtual void print(int count){
        for (int i = 0; i < count; i++){
            cout << "\t";
        }
        cout << "T2Node" << endl;
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
            cout << "\t";
        }
        cout << "FNode" << endl;
        count++;
        cout <<  endl;
        if (this->Left != NULL){
            this->Left->print(count);
        }
        if (this->Right != NULL){
            this->Right->print(count);
        }
    }
private:
    string var;
    int id;
};
#endif	/* TREENODE_H */


