#include <iostream>

using namespace std;


class Node {

private:
    // Data
    int key;
    string value;
    int color; // 0 is black, 1 is red

  
public:

    //Pointers
    Node* parent;
    Node* lchild;
    Node* rchild;

    Node(int key, string value) {
        this->key = key;
        this->value = value;
        this->color = 0; //no child to begin with

        this->parent = NULL;
        this->lchild = NULL;
        this->rchild = NULL;
    }
    //Getters decleration and inline implementation
    int getKey() { return key;}
    string getValue() {return value;}

    //Setter declaration
    void setKey(int k);
    void setValue(string v);
    

    
};

//Node Setter Implementations

void Node::setKey(int k) {
    key = k;
}

void Node::setValue(string v) {
    value = v;
}

class RBTree {
//Private member root
private:
    Node* root;
    void rebalance(Node* r);
    void rotateLeft(Node* r);
    void rotateRight(Node* r);
    void deleteAllChildren(Node* current);

public:
    //Constructor Decl.
    RBTree(int key, string value);
    RBTree(int[] keys, string[] values);
    ~RBTree();

    //Declaration of the Methods
    void insert(int key, string value); // Add a key/value pair to tree
    string search(int key);
    void printTree();
    
};

//Constructor Implementation
RBTree::RBTree(int key, string value) {
    insert(key,value);
}

RBTree::RBTree (int[] keys, string[] values) {
    int n = sizeof(keys)/sizeof(int);
    for (int i =0; i < n; i++) {
        insert(keys[i],values[i]);
    }
}

//Destructor for RBTree
RBTree::~RBTree() {

}

//Implement private methods

void RBTree::deleteAllChildren(Node* current) {
    if (current != NULL) {
        deleteAllChildren(current->lchild);
        deleteAllChildren(current->rchild);
    }
}
