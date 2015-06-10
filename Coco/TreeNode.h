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

private:
    TreeNode* Left;
    TreeNode* Right;
    TreeNode* Parent;
};

class ZNode : public TreeNode {
public:
    ZNode();
    ZNode(G2Node left, ENode right){
        this->setLeft(left);
        this->setRight(right);
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

private:
    string var;
};

class D2Node : public TreeNode {
public:
    D2Node(){}
    
private:
    string Semicolon = ":=";
};

class ENode : public TreeNode {
public:
    ENode(){}   

private:
};

class E2Node : public TreeNode {
public:
    E2Node(){}   

private:
};

class TNode : public TreeNode {
public:
    TNode(){}    

private:
};

class T2Node : public TreeNode {
public:
    T2Node(){}  

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

private:
    string var;
    int id;
};
#endif	/* TREENODE_H */


