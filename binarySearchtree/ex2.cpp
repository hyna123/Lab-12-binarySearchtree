#include <iostream>
using namespace std;

// Class to represent a node in the Binary Search Tree
class TNode {
public:
    int data;          // Data value of the node
    TNode* left;       // Pointer to the left child
    TNode* right;      // Pointer to the right child

    // Constructor to initialize a node with a given value
    TNode(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

// Class to represent the Binary Search Tree
class BST {
public:
    TNode* root;       // Pointer to the root node of the tree

    // Constructor to initialize an empty BST
    BST() {
        root = nullptr;
    }

    // Function to insert a value into the BST
    void insert(TNode*& node, int value) {
        if (node == nullptr) {
            // If the current node is null, create a new node with the given value
            node = new TNode(value);
        } else if (value < node->data) {
            // If the value is smaller, insert it into the left subtree
            insert(node->left, value);
        } else {
            // If the value is larger, insert it into the right subtree
            insert(node->right, value);
        }
    }

    // Function to perform in-order traversal of the BST (left, root, right)
    void inOrder(TNode* node) {
        if (node != nullptr) {
            inOrder(node->left);          // Traverse the left subtree
            cout << node->data << " ";    // Visit the current node
            inOrder(node->right);         // Traverse the right subtree
        }
    }
};

// Function to print the path from the root to a node with the given value
void printPath(TNode* node, int value) {
    while (node != nullptr) {
        cout << node->data << " ";        // Print the current node's data
        if (value == node->data) return;  // Stop if the value is found
        if (value < node->data) node = node->left;
        else node = node->right; // Move left or right
    }
    cout << "Value not found." << endl;   // Print a message if the value is not found
}

// Function to find the maximum value in the BST
int findMax(TNode* node) {
    if (node == nullptr) {
        cout << "BST is empty." << endl;
        return -1;  // Return a sentinel value if the tree is empty
    }
    while (node->right != nullptr) {
        node = node->right; // Move to the rightmost node
    }
    return node->data;      // Return the maximum value
}

// Function to find the sibling of a node with the given value
int findSibling(TNode* root, int value) {
    TNode* parent = nullptr; // Pointer to store the parent node
    while (root != nullptr && root->data != value) {
        parent = root;
        if (value < root->data) {
            root = root->left;
        } else {
            root = root->right;
        }
    }
    if (root == nullptr || parent == nullptr) {
        cout << "No sibling found." << endl;
        return -1;  // Return a sentinel value if no sibling is found
    }
    if (parent->left == root && parent->right != nullptr) 
        return parent->right->data;
    if (parent->right == root && parent->left != nullptr) 
        return parent->left->data;
    
    cout << "No sibling found." << endl;
    return -1;  // Return a sentinel value if no sibling is found
}

int main() {
    BST tree; // Create an instance of the BST class

    // Insert values into the BST
    for (int value : {50, 30, 70, 20, 40, 60, 80})
        tree.insert(tree.root, value);

    // Perform in-order traversal to display the tree
    cout << "In-order traversal: ";
    tree.inOrder(tree.root);
    cout << endl;

    // Print the path to a specific value
    int pathValue = 40;
    cout << "Path to " << pathValue << ": ";
    printPath(tree.root, pathValue);
    cout << endl;

    // Find and display the maximum value in the BST
    int maxValue = findMax(tree.root);
    if (maxValue != -1) {
        cout << "Maximum value: " << maxValue << endl;
    }

    // Find and display the sibling of a specific value
    int siblingValue = 30;
    int sibling = findSibling(tree.root, siblingValue);
    if (sibling != -1) {
        cout << "Sibling of " << siblingValue << ": " << sibling << endl;
    }

    return 0;
}
