//============================================================================
// Name        : AVLSearchTree.cpp
// Author      : Antonio Arruda
// Version     : 2.0
// Copyright   : Copyright © 2022 SNHU COCE
// Description : AVL Search tree to search records of items sold by the eBids
//============================================================================

#include <iostream>
#include <time.h>
#include <bits/stdc++.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations

double strToDouble(string str, char ch);

// define a structure to hold bid information

struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

// Internal structure for tree node

struct Node {
    Bid bid;
    Node* parentPtr;
    Node* leftPtr;
    Node* rightPtr;
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */

class AVLBinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    AVLBinarySearchTree();
    virtual ~BinarySearchTree();
    void Insert();
    void InOrder();
    void Remove(string bidId);
    Bid Search(string bidId);

public:
    int key;
    Node *left;
    Node *right;
    int height;
};


// A utility function to get maximum
// of two integers
    int max(int a, int b);
 
// A utility function to get the
// height of the tree
    int height(Node *N)
    {
        if (N == NULL)
            return 0;
        return N->height;
    }
 
// A utility function to get maximum
// of two integers
    int max(int a, int b)
    {
        return (a > b)? a : b;
    }
 
/* Helper function that allocates a
   new node with the given key and
   NULL left and right pointers. */


/**
 * Default constructor
 */

AVLBinarySearchTree::AVLBinarySearchTree() {
    // initialize housekeeping variables
}

/**
 * Destructor
 */

AVLBinarySearchTree::~AVLBinarySearchTree() {
    // recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void AVLBinarySearchTree::InOrder() {
}

/**
 * Insert a bid
 */

void AVLBinarySearchTree::Insert(Bid bid) {
    // Implement inserting a bid into the tree
    
Node* newNode(int key)
{
    Node* node = new Node();
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // new node is initially
                      // added at leaf
    return(node);
}
 
// A utility function to right
// rotate subtree rooted with y
// See the diagram given above.
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left),
                    height(y->right)) + 1;
    x->height = max(height(x->left),
                    height(x->right)) + 1;
 
    // Return new root
    return x;
}
 
// A utility function to left
// rotate subtree rooted with x
// See the diagram given above.
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    // Update heights
    x->height = max(height(x->left),   
                    height(x->right)) + 1;
    y->height = max(height(y->left),
                    height(y->right)) + 1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert a key
// in the subtree rooted with node and
// returns the new root of the subtree.

Node* insert(Node* node, int key)
{

// Perform the normal BST insertion
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;

// Update height of this ancestor node
// Get the balance factor of this ancestor node to check whether this node became
// unbalanced
    node->height = 1 + max(height(node->left),
                        height(node->right));
 

    int balance = getBalance(node);
 
// If this node becomes unbalanced, then there are 4 cases
// Left Left Case, Right Right Case, Left Right Case, Right Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
 

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}
 
// A utility function to print preorder traversal of the tree.
// The function also prints the height of every node
void preOrder(Node *root)
{
    if(root != NULL)
    {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}
 

int main()
{
    Node *root = NULL;
     
    /* Constructing tree given in
    the above figure */
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "Preorder traversal of the "
            "constructed AVL tree is \n";
    preOrder(root);
     
    return 0;
}


/**
 * Remove a bid
 */

void AVLBinarySearchTree::Remove(string bidId) {
    // Implement removing a bid from the tree
    
    Node* nodePtr = SearchNode(root, bidId);
    if (nodePtr == nullptr) {
        return;
    }

    else {
        nodePtr->parentPtr->leftPtr = nodePtr->leftPtr;
        nodePtr->parentPtr->rightPtr = nodePtr->rightPtr;
        nodePtr->leftPtr->parentPtr = nodePtr->parentPtr;
        nodePtr->rightPtr->parentPtr = nodePtr->parentPtr;
        delete nodePtr;
    }
}

/**
 * Search for a bid
 */

Bid AVLBinarySearchTree::Search(string bidId) {
    // Implement searching the tree for a bid
    
    Node* nodePtr = SearchNode(root, bidId);
    if (nodePtr == nullptr) {
        Bid bid;
        return bid;
    }

    else {
        return nodePtr->bid;
    }

	Bid bid;
    return bid;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */

void AVLBinarySearchTree::addNode(Node* node, Bid bid) {
    // FIXME (2b) Implement inserting a bid into the tree

    int curKey = atoi(node->bid.bidId.c_str());
    int key = atoi(bid.bidId.c_str());

    cout << "Current key is: " << curKey << endl;
    cout << "Search key is: " << key << endl;

    if (key > curKey) {
        if (node->rightPtr == nullptr) {
            node->rightPtr = new Node;
            node->rightPtr->bid = bid;
            node->rightPtr->rightPtr = nullptr;
            node->rightPtr->leftPtr = nullptr;
            node->rightPtr->parentPtr = node;
        }
        else {
            addNode(node->rightPtr, bid);
        }
    }
    else {
        if (node->leftPtr == nullptr) {
            node->leftPtr = new Node;
            node->leftPtr->bid = bid;
            node->leftPtr->rightPtr = nullptr;
            node->leftPtr->leftPtr = nullptr;
            node->leftPtr->parentPtr = node;

            cout << "leftPtr is nullptr" << endl;
        }
        else {

            cout << "leftPtr is NOT nullptr" << endl;
            addNode(node->leftPtr, bid);
        }
    }
}

void AVLBinarySearchTree::inOrder(Node* node) {
}
//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */

void loadBids(string csvPath, AVLBinarySearchTree* bst) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
  
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file

        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids

            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            // push this bid to the end

            bst->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */

double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */

int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    AVLBinarySearchTree* bst;

    Bid bid;

    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            bst = new AVLBinarySearchTree();

            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bst);

            //cout << bst->Size() << " bids read" << endl;

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bst->InOrder();
            break;

        case 3:
            ticks = clock();

            bid = bst->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
            	cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;

            break;

        case 4:
            bst->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

	return 0;
}
