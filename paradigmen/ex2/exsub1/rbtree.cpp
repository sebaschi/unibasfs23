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

        this->parent = nullptr;
        this->lchild = nullptr;
        this->rchild = nullptr;
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

private:
    Node* root;
    void rebalance(Node* r);
    void rotateLeft(Node* r);
    void rotateRight(Node* r);
    void deleteAllNodes(Node* current);
    void traversal(Node* current, int indent);

public:
    //Constructor Decl.
    RBTree();
    RBTree(int key, string value);
    RBTree(int* keys, string* values, int size);
    ~RBTree();

    //Declaration of the Methods
    void insert(int key, string value); // Add a key/value pair to tree
    string search(int key);
    void printTree();
    
};

//Constructor Implementation
RBTree::RBTree() {
    this->root = nullptr;
}

RBTree::RBTree(int key, string value) {
    this->root = nullptr;
    insert(key,value);
}

RBTree::RBTree (int* keys, string* values, int size) {
    this->root = nullptr;
    for (int i =0; i < size; i++) {
        insert(keys[i],values[i]);
    }
}

//Destructor for RBTree
RBTree::~RBTree() {
    deleteAllNodes(this->root);
}

//Implement public methods
//Ref: Algorithmen - Eine Einfürung, Cormen, Leierson, Rivest, Stein, 2013 Oldenbourg Wissenschaftsverlag GmbH
void RBTree::insert(int key, string value) {

    //Create new node;
    Node* z = new Node(key,value);

    Node* y = nullptr;
    Node* x = this->root;
    while ( x != nullptr) {
        y = x;
        if (z->getKey() < x->getKey()) {
            x = x->lchild;
        } else {
            x = x->rchild;
        }
    }

    z->parent = y;

    if (y == nullptr) {
        this->root = z;
    } else if (z->getKey() < y->getKey()) {
        y->lchild = z;
    } else {
        y->rchild = z;
    }

    z->lchild = nullptr;
    z->rchild = nullptr;
    z->color = 1;
    rebalance(z);
}

//From the same book as insert(int,string)
void RBTree::rebalance(Node* z) {
    while (z->parent != nullptr && z->parent->color==1) {
        //Parent is a left child    
        if (z->parent == z->parent->parent->lchild) {
            Node* y = z->parent->parent->rchild;
            if (y != nullptr && y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->rchild) {
                    z = z->parent;
                    rotateLeft(z); 
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rotateRight(z->parent->parent);
            }
        } else if (z->parent == z->parent->parent->rchild) { //Parent is a right child. Analog but left/right switched -> book
            Node* y = z->parent->parent->lchild;
            if (y != nullptr && y->color == 1) {
                z->parent->color = 0;
                y->color = 0;
                z->parent->parent->color = 1;
                z = z->parent->parent;
            } else {
                if (z == z->parent->lchild) {
                    z = z->parent;
                    rotateRight(z);
                }
                z->parent->color = 0;
                z->parent->parent->color = 1;
                rotateLeft(z->parent->parent);
            }
        }
    }
    this->root->color = 0; //keep root black
}

// Again same book
void RBTree::rotateLeft(Node* z) {
    if (z->rchild == nullptr) {return;}
    Node* y = z->rchild;
    z->rchild = y->lchild;
    
    if (y->lchild != nullptr) {
        y->lchild->parent = z;
    }

    y->parent = z->parent;

    if (z->parent == nullptr) {
        this->root = y;
        this->root->parent = nullptr;
    } else if (z == z->parent->lchild) {
        z->parent->lchild = y;
    } else {
        z->parent->rchild = y;
    }

    y->lchild = z;
    z->parent = y;

}

//Like rotateLeft(Node*) but left/right flipped
void RBTree::rotateRight(Node* z) {
    if (z->lchild == nullptr) { cout << "lchild null"<<endl; return;}
    Node* y = z->lchild;
    z->lchild = y->rchild;

    if (y->rchild != nullptr) {
        y->rchild->parent = z;
    }

    y->parent = z->parent;

    if (z->parent == nullptr) {
        this->root = y;
        this->root->parent = nullptr;
    } else if (z == z->parent->rchild) {
        z->parent->rchild = y;
    } else {
        z->parent->lchild = y;
    }

    y->rchild =z;
    z->parent =y;
}

void RBTree::printTree() {
    if (this-> root == nullptr) { return; };
    Node* current = this->root;
    traversal(current, 0);
    cout << endl;
}



//Implement private methods
//

void RBTree::traversal(Node* current, int indent) {
    if (current == nullptr) { return;}
    for (int i = 0; i < indent; i++) {
        cout << " ---- ";
    }
    cout << current->color << ":" << current->getKey() << ":" << current->getValue() ;
    traversal(current->lchild, indent+1);
    cout << endl;
    traversal(current->rchild, indent+1);
}

//heler method for destructor
void RBTree::deleteAllNodes(Node* current) {
    //Base case
    if (current != nullptr) {
        //Recursively delete left subtree
        deleteAllNodes(current->lchild);
        //Recursively delete right suntree
        deleteAllNodes(current->rchild);
        //delete self;
        delete current;
    }
}

int main() {
    int zips[14] = {1005, 9000, 1204, 6060, 5034, 8057, 8805, 2740, 3005, 4052, 3920, 4132, 6005, 3604};
    string names[14] = {"Lausanne", "St. Gallen", "Geneve", "Sarnen", "Suhr", "Zurich", "Richterswil", "Moutier",
"Bern", "Basel", "Zermatt", "Muttenz", "Luzern", "Thun"};
    RBTree tree(zips, names, 14); 
    tree.printTree();

    //To test destructor use heap memory
    RBTree* test= new RBTree();
    test->insert(111, "One");
    test->insert(222, "two");
    test->insert(333, "three");
    test->printTree();
    test->insert(444,"four");
    test->printTree();
    test->insert(555, "five");
    test->insert(666, "six");
    test->printTree();
    //To check if destructor works
    delete test;
    return 0;
}
