#include <iostream>
using namespace std;

// Class to model a node of a BST
class TNode {
public:
    int data; // Value of the node
    TNode* left; // Pointer to the left child
    TNode* right; // Pointer to the right child

    // Default constructor
    TNode() { 
        data = 0; 
        left = nullptr;
        right = nullptr; }
    // Parameterized constructor
    TNode(int value) { 
        data = value; 
        left = nullptr; 
        right = nullptr; }
};

// Class to create a BST
class BST {
public:
    TNode* root; // Root of the BST

    // Default constructor
    BST() { 
        root = nullptr;
         }

    // Check if the BST is empty
    bool isEmpty() {
        return root == nullptr;
    }

    // Insert a value into the BST
    void insert(TNode*& node, int value) {
        if (node == nullptr) {
            node = new TNode(value); // Create a new node if the position is empty
        } else if (value < node->data) {
            insert(node->left, value); // Recur on the left subtree
        } else {
            insert(node->right, value); // Recur on the right subtree
        }
    }

    // Search for a value in the BST
    bool search(TNode* node, int value) {
        if (node == nullptr) {
            return false; // Value not found
        }
        if (node->data == value) {
            return true; // Value found
        } else if (value < node->data) {
            return search(node->left, value); // Recur on the left subtree
        } else {
            return search(node->right, value); // Recur on the right subtree
        }
    }

    // Delete a node with a specific value from the BST
    void delete_node(TNode*& node, int value) {
        if (node == nullptr) {
            return; // Node not found
        }

        if (value < node->data) {
            delete_node(node->left, value); // Recur on the left subtree
        } else if (value > node->data) {
            delete_node(node->right, value); // Recur on the right subtree
        } else {
            // Node to be deleted found
            if (node->left == nullptr && node->right == nullptr) {
                delete node; // Delete leaf node
                node = nullptr;
            } else if (node->left == nullptr) {
                TNode* temp = node; // Node has only right child
                node = node->right;
                delete temp;
            } else if (node->right == nullptr) {
                TNode* temp = node; // Node has only left child
                node = node->left;
                delete temp;
            } else {
                TNode* minNode = findmin(node->right); // Node has two children
                node->data = minNode->data; // Replace with the minimum value in the right subtree
                delete_node(node->right, minNode->data); // Delete the duplicate node
            }
        }
    }

    // Perform in-order traversal of the BST
    void in_orderTraverse(TNode* node) {
        if (node != nullptr) {
            in_orderTraverse(node->left); // Traverse left subtree
            cout << node->data << " "; // Visit the node
            in_orderTraverse(node->right); // Traverse right subtree
        }
    }

    // Find the node with the minimum value in the BST or subtree
    TNode* findmin(TNode* node) {
        while (node && node->left != nullptr) {
            node = node->left; // Move to the leftmost node
        }
        return node;
    }

    // Get the parent of a node with a specific value
    TNode* getParent(TNode* node, int value) {
        if (node == nullptr || node->data == value) {
            return nullptr; // No parent if node is null or is the root
        }

        if ((node->left && node->left->data == value) || (node->right && node->right->data == value)) {
            return node; // Return the parent node
        }

        if (value < node->data) {
            return getParent(node->left, value); // Recur on the left subtree
        } else {
            return getParent(node->right, value); // Recur on the right subtree
        }
    }
};

int main() {
    BST tree; // Create an instance of BST

    // Insert values into the BST
    tree.insert(tree.root, 50);
    tree.insert(tree.root, 30);
    tree.insert(tree.root, 70);
    tree.insert(tree.root, 20);
    tree.insert(tree.root, 40);
    tree.insert(tree.root, 60);
    tree.insert(tree.root, 80);

    // Display the BST in in-order traversal
    cout << "In-order traversal: ";
    tree.in_orderTraverse(tree.root);
    cout << endl;

    // Search for a specific value in the BST
    int searchValue = 40;
    if (tree.search(tree.root, searchValue)) {
        cout << "Search for " << searchValue << ": Found" << endl;
    } else {
        cout << "Search for " << searchValue << ": Not Found" << endl;
    }

    // Delete a specific value from the BST
    int deleteValue = 30;
    cout << "Deleting " << deleteValue << endl;
    tree.delete_node(tree.root, deleteValue);

    // Display the BST in in-order traversal after deletion
    cout << "In-order traversal after deletion: ";
    tree.in_orderTraverse(tree.root);
    cout << endl;

    // Find the parent of a specific node
    int parentValue = 60;
    TNode* parent = tree.getParent(tree.root, parentValue);
    if (parent) {
        cout << "Parent of " << parentValue << " is " << parent->data << endl;
    } else {
        cout << "Parent of " << parentValue << " not found or it is the root." << endl;
    }

    return 0;
}
