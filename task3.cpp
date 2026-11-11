
#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int data;
    int height;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

class AVLTree {
public:

    int getHeight(Node* root) {
        if (root == NULL)
            return 0;

        return root->height;
    }

    int getBalance(Node* root) {
        if (root == NULL)
            return 0;

        return getHeight(root->left) - getHeight(root->right);
    }

    Node* leftRotate(Node* root) {
        Node* newRoot = root->right;
        Node* temp = newRoot->left;

        newRoot->left = root;
        root->right = temp;

        root->height = 1 + max(getHeight(root->left),
                               getHeight(root->right));

        newRoot->height = 1 + max(getHeight(newRoot->left),
                                  getHeight(newRoot->right));

        return newRoot;
    }

    Node* rightRotate(Node* root) {
        Node* newRoot = root->left;
        Node* temp = newRoot->right;

        newRoot->right = root;
        root->left = temp;

        root->height = 1 + max(getHeight(root->left),
                               getHeight(root->right));

        newRoot->height = 1 + max(getHeight(newRoot->left),
                                  getHeight(newRoot->right));

        return newRoot;
    }

    Node* insert(Node* root, int value) {
        if (root == NULL)
            return new Node(value);

        if (value < root->data)
            root->left = insert(root->left, value);

        else if (value > root->data)
            root->right = insert(root->right, value);

        else
            return root;

        root->height = 1 + max(getHeight(root->left),
                               getHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1 && value < root->left->data)
            return rightRotate(root);

        if (balance < -1 && value > root->right->data)
            return leftRotate(root);

        if (balance > 1 && value > root->left->data) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && value < root->right->data) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void display(Node* root) {
        if (root != NULL) {
            cout << root->data << " ";
            display(root->left);
            display(root->right);
        }
    }

    Node* getRoot() {
        return NULL;
    }
};

int main() {
    AVLTree tree;
    Node* root = NULL;

    int values[] = {50, 30, 70, 20, 40, 60, 80};

    for (int i = 0; i < 7; i++) {
        root = tree.insert(root, values[i]);
    }

    cout << "Original AVL Tree: ";
    tree.display(root);

    root = tree.insert(root, 55);

    cout << "\n\nAfter inserting 55: ";
    tree.display(root);

    root = tree.leftRotate(root);

    cout << "\n\nAfter left rotation on root: ";
    tree.display(root);

    return 0;
}
