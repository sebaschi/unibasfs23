#include <iostream>

using namespace std;


class Node {

private:
    // Data
    int key;
    string value;

  
public:

    int color; // 0 is black, 1 is red
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
    void inOrderTraversal(Node* current);

public:
    //Constructor Decl.
    RBTree();
    RBTree(int key, string value);
    RBTree(int* keys, string* values);
    ~RBTree();

    //Declaration of the Methods
    void insert(int key, string value); // Add a key/value pair to tree
    string search(int key);
    void printTree();
    
};

//Constructor Implementation
RBTree::RBTree() {
    this->root = NULL;
}

RBTree::RBTree(int key, string value) {
    this->root = NULL;
    insert(key,value);
}

RBTree::RBTree (int* keys, string* values) {
    this->root = NULL;
    int n = sizeof(keys)/sizeof(int);
    for (int i =0; i < n; i++) {
        insert(keys[i],values[i]);
    }
}

//Destructor for RBTree
RBTree::~RBTree() {

}

//Implement public methods
//Ref: Algorithmen - Eine Einfürung, Cormen, Leierson, Rivest, Stein, 2013 Oldenbourg Wissenschaftsverlag GmbH
void RBTree::insert(int key, string value) {

    //Create new node;
    Node* z = new Node(key,value);

    Node* y = NULL;
    Node* x = this->root;
    
    while ( x != NULL) {
        y = x;
        cout << z->getKey() << endl;
        cout << x->getKey() << endl;
        if (z->getKey() < x->getKey()) {
            x = x->lchild;
        } else {
            x = x->rchild;
        }
    }

    z->parent = y;

    if (y == NULL) {
        this->root = z;
    } else if (z->getKey() < y->getKey()) {
        y->lchild = z;
    } else {
        y->rchild = z;
    }

    z->lchild = NULL;
    z->rchild = NULL;
    z->color = 1;
    //rebalance(z);

}

void RBTree::rebalance(Node* z) {
    while (z->parent != NULL && z->parent->color==1) {
        if (z->parent == z->parent->parent->lchild) {
        }
    }
}

void RBTree::printTree() {
    Node* current = this->root;
    inOrderTraversal(current);
    cout << endl;
}



//Implement private methods
//

void RBTree::inOrderTraversal(Node* current) {
    if (current != NULL) {
        cout << "(";
        inOrderTraversal(current->lchild);
        cout << "Key: " << current->getKey() << " Value: " << current->getValue();
        inOrderTraversal(current->rchild);
        cout << ")";
    }
}

void RBTree::deleteAllChildren(Node* current) {
    if (current != NULL) {
        deleteAllChildren(current->lchild);
        deleteAllChildren(current->rchild);
        delete current;
    }
}

int main() {
    int zips[14] = {1005, 9000, 1204, 6060, 5034, 8057, 8805, 2740, 3005, 4052, 3920, 4132, 6005, 3604};
    string names[14] = {"Lausanne", "St. Gallen", "Geneve", "Sarnen", "Suhr", "Zurich", "Richterswil", "Moutier",
"Bern", "Basel", "Zermatt", "Muttenz", "Luzern", "Thun"};
    RBTree tree(zips, names); 
    tree.printTree();
    return 0;
}
