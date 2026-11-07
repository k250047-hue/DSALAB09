
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int value) {
        data = value;
        left = NULL;
        right = NULL;
    }
};

int getHeight(Node* root) {
    if (root == NULL) {
        return 0;
    }

    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);

    if (leftHeight > rightHeight) {
        return leftHeight + 1;
    }

    return rightHeight + 1;
}

int getBalance(Node* root) {
    if (root == NULL) {
        return 0;
    }

    return getHeight(root->left) - getHeight(root->right);
}

Node* rotateRight(Node* oldRoot) {
    Node* newRoot = oldRoot->left;
    Node* middleTree = newRoot->right;

    newRoot->right = oldRoot;
    oldRoot->left = middleTree;

    return newRoot;
}

Node* rotateLeft(Node* oldRoot) {
    Node* newRoot = oldRoot->right;
    Node* middleTree = newRoot->left;

    newRoot->left = oldRoot;
    oldRoot->right = middleTree;

    return newRoot;
}

Node* convertToAVL(Node* root) {
    if (root == NULL) {
        return NULL;
    }

    root->left = convertToAVL(root->left);
    root->right = convertToAVL(root->right);

    int balance = getBalance(root);

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0) {
        return rotateRight(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0) {
        return rotateLeft(root);
    }

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void display(Node* root) {
    if (root == NULL) {
        return;
    }

    cout << root->data << " ";
    display(root->left);
    display(root->right);
}

int main() {

    // BST A
    Node* treeA = new Node(10);
    treeA->left = new Node(6);
    treeA->left->left = new Node(4);
    treeA->left->right = new Node(8);

    // BST B
    Node* treeB = new Node(10);
    treeB->right = new Node(16);
    treeB->right->left = new Node(12);
    treeB->right->right = new Node(18);

    treeA = convertToAVL(treeA);
    treeB = convertToAVL(treeB);

    cout << "AVL Tree A: ";
    display(treeA);

    cout << "\nAVL Tree B: ";
    display(treeB);

    return 0;
}
