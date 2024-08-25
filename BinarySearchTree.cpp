//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Daniel Schween 
// Version     : 1.0
// Copyright   : Copyright � 2023 SNHU COCE
// Description : Lab 5-2 Binary Search Tree
//============================================================================

#include <iostream>
#include <time.h>

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
    Node *left;
    Node *right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Bid aBid) :
            Node() {
        bid = aBid;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void addNode(Node* node, Bid bid);
    void inOrder(Node* node);
    void postOrder(Node* node);
    void preOrder(Node* node);
    Node* removeNode(Node* node, string bidId);

public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void InOrder();
    void PostOrder();
    void PreOrder();
    void PreOrder(Node* root);
    void Insert(Bid bid);
    void Remove(string bidId);
    Bid Search(string bidId);
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // Initialize housekeeping variables
    // root is equal to nullptr

    this->root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {

}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
    if (root == NULL) 
        return;

    Inorder(root->left);       //Visit left subtree
    printf("%c ", root->data);  //Print data
    Inorder(root->right);      // Visit right subtree
   
    
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
    if (root == NULL)
        return;

    PostOrder(root->left); // Visit left subtree
    PostOrder(root->right); // Visit right subtree
    printf("%c", root->data); // Print data
    
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
    if (root == NULL) return;

    Preorder(root->left);     // Visit left subtree
    Preorder(root->right);    // Visit right subtree
    printf("%c ", root->data); // Print data
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {

    // Implement inserting a bid into the tree
    if (root == nullptr) {

        root = new Node(bid);
    }
    else {

        this->addNode(root, bid);
    }
}

/**
 * Remove a bid
 */
void BinarySearchTree::Remove(string bidId) {

    // Implement removing a bod into the tree
    this->removeNode(root, bidId);
}

/**
 * Search for a bid
 */
Bid BinarySearchTree::Search(string bidId) {

    // Implement searching the tree for a bid
    Node* current = root;

    // keep looping until bottom reached or bid is found
    while (current != nullptr) {

        // If match found, return
        if (current->bid.bidId.compare(bidId == 0)) {
            return current->bid;
        }

        // If bid is less then current bid, add to the left subtree
        if (bidId.compare(current->bid.bidId) < 0) {

            current = current->left;
        }

        else {
            current = current->right;
        }
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
void BinarySearchTree::addNode(Node* node, Bid bid) {
    // Implement inserting a bid into the tree

    // if node is larger then add to left
    if (node->bid.bidId.compare(bid.bidId) > 0) {

        // If no left node
        if (node->left == nullptr) {

            // New left node
            node->left = new Node(bid);
        }

        // Recurse down the left node
        else {

            this->addNode(node->left, bid);
        }
    }

    // Add to the right subtree
    else {

        if (node->right == nulptr) {

            // New right node
            node->right = new Node(bid);
        }

        // Recurse down to the right node
        else {

            this->addNode(node->right, bid);

        }
    }
}

void BinarySearchTree::inOrder(Node* node) {

    //if node is not equal to null ptr
    if (node != nullptr) {

        inOrder(node->left);
    

    //output bidID, title, amount, fund
    cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
        << node->bid.fund << endl;

    //InOder right
    inOrder(node->right);
    }
}

void BinarySearchTree::postOrder(Node* node) {
      // FixMe (4b): Post order root
      
      //if node is not equal to null ptr
    if (node != nullptr) {

        // postOrder left
        postOrder(node->left);

        // postOrder right
        postOrder(node->right);

        //output bidID, title, amount, fund
        cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
            << node->bid.fund << endl;

}

void BinarySearchTree::preOrder(Node* node) {
      // Pre order root
      // if node is not equal to null ptr
    if (node != nullptr) {

        //output bidID, title, amount, fund
        cout << node->bid.bidId << ": " << node->bid.title << " | " << node->bid.amount << " | "
            << node->bid.fund << endl;

        //preOrder left
        PreOrder(node->left);

        //preOrder right 
        preOrder(node->right);
    }
}

/**
 * Remove a bid from some node (recursive)
 */
Node* BinarySearchTree::removeNode(Node* node, string bidId) {
    // Implement removing a bid from the tree
    
    // if node = nullptr, return node
    if (node == nullptr) {
        return node;
    }

    // recurse down the left subtree
    if (bidId.compare(node->bid.bidId) < 0) {

        node->left = removeNode(node->left, bidId);
    }

    else if (bidId.compare(node->bid.bidId) > 0) {

        node->right = removeNode(node->bid, bidId);
    }

    else {

        // no children, leaf node
        if (node->left == nullptr && node->right == nullptr) {
            
            delete node;
            node = nullptr;
        }

        // one child to the left
        else if (node->left != nullptr && node->right == nullptr) {
            
            Node* temp = node;
            node = node->left;
            delete temp;
        }

        // one child to the right
        else if (node->right != nullptr && node->left == nullptr) {
            
            Node* temp = node;
            node = node->right;
            delete temp;
        }

        //two children
        else {
            Node* temp = node->right;

            while (temp->left != nullptr) {

                temp = temp->left;
            }

            node->bid = temp->bid;
            node->right = removeNode(node->right, temp->bid.bidId);
        }
    }

    return node;
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
void loadBids(string csvPath, BinarySearchTree* bst) {
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

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

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
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a binary search tree to hold all bids
    BinarySearchTree* bst;
    bst = new BinarySearchTree();
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
