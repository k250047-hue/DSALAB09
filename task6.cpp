
#include <iostream>
#include <vector>
#include <iomanip>
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

class BST {
public:

    void inorder(Node* root, vector<int>& arr) {
        if (root == NULL)
            return;

        inorder(root->left, arr);
        arr.push_back(root->data);
        inorder(root->right, arr);
    }

    Node* buildTree(vector<int>& arr, int start, int end) {
        if (start > end)
            return NULL;

        int mid = (start + end) / 2;

        Node* root = new Node(arr[mid]);

        root->left = buildTree(arr, start, mid - 1);
        root->right = buildTree(arr, mid + 1, end);

        return root;
    }

    void deleteTree(Node* root) {
        if (root == NULL)
            return;

        deleteTree(root->left);
        deleteTree(root->right);

        delete root;
    }

    Node* balanceBST(Node* root) {
        vector<int> arr;

        inorder(root, arr);

        deleteTree(root);

        return buildTree(arr, 0, arr.size() - 1);
    }

    int height(Node* root) {
        if (root == NULL)
            return 0;

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        if (leftHeight > rightHeight)
            return leftHeight + 1;

        return rightHeight + 1;
    }

    bool isBalanced(Node* root) {
        if (root == NULL)
            return true;

        int leftHeight = height(root->left);
        int rightHeight = height(root->right);

        if (leftHeight - rightHeight > 1 ||
            rightHeight - leftHeight > 1)
            return false;

        return isBalanced(root->left) &&
               isBalanced(root->right);
    }

    void display(Node* root, int space = 0) {
        if (root == NULL)
            return;

        space += 5;

        display(root->right, space);

        cout << endl;

        for (int i = 5; i < space; i++)
            cout << " ";

        cout << setw(4) << setfill('0') << root->data;
        cout << setfill(' ') << endl;

        display(root->left, space);
    }
};

int main() {
    BST tree;

    // Creating Tree A
    Node* A = new Node(10);
    A->left = new Node(6);
    A->left->left = new Node(4);
    A->left->right = new Node(8);

    // Creating Tree B
    Node* B = new Node(10);
    B->right = new Node(16);
    B->right->left = new Node(12);
    B->right->right = new Node(18);

    cout << "TREE A BEFORE BALANCING:" << endl;
    tree.display(A);

    cout << "\nIs Tree A Balanced? ";
    cout << (tree.isBalanced(A) ? "Yes" : "No");

    A = tree.balanceBST(A);

    cout << "\n\nTREE A AFTER BALANCING:" << endl;
    tree.display(A);

    cout << "\nHeight of Tree A: " << tree.height(A);

    cout << "\n\nTREE B BEFORE BALANCING:" << endl;
    tree.display(B);

    cout << "\nIs Tree B Balanced? ";
    cout << (tree.isBalanced(B) ? "Yes" : "No");

    B = tree.balanceBST(B);

    cout << "\n\nTREE B AFTER BALANCING:" << endl;
    tree.display(B);

    cout << "\nHeight of Tree B: " << tree.height(B);

    cout << "\n\nAre both trees balanced? ";
    cout << (tree.isBalanced(A) && tree.isBalanced(B)
             ? "Yes" : "No");

    tree.deleteTree(A);
    tree.deleteTree(B);

    return 0;
}
