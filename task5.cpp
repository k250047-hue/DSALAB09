
#include <iostream>
#include <algorithm>
using namespace std;

class Node {
public:
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int value) {
        key = value;
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

    Node* rightRotate(Node* root) {
        Node* temp = root->left;
        Node* child = temp->right;

        temp->right = root;
        root->left = child;

        root->height = 1 + max(getHeight(root->left),
                               getHeight(root->right));

        temp->height = 1 + max(getHeight(temp->left),
                               getHeight(temp->right));

        return temp;
    }

    Node* leftRotate(Node* root) {
        Node* temp = root->right;
        Node* child = temp->left;

        temp->left = root;
        root->right = child;

        root->height = 1 + max(getHeight(root->left),
                               getHeight(root->right));

        temp->height = 1 + max(getHeight(temp->left),
                               getHeight(temp->right));

        return temp;
    }

    Node* insert(Node* root, int value) {
        if (root == NULL)
            return new Node(value);

        if (value < root->key)
            root->left = insert(root->left, value);

        else if (value > root->key)
            root->right = insert(root->right, value);

        else
            return root;

        root->height = 1 + max(getHeight(root->left),
                               getHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1 && value < root->left->key)
            return rightRotate(root);

        if (balance < -1 && value > root->right->key)
            return leftRotate(root);

        if (balance > 1 && value > root->left->key) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && value < root->right->key) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void display(Node* root) {
        if (root != NULL) {
            cout << root->key << " ";
            display(root->left);
            display(root->right);
        }
    }

    int countNodes(Node* root) {
        if (root == NULL)
            return 0;

        return 1 + countNodes(root->left)
                 + countNodes(root->right);
    }

    void kthSmallest(Node* root, int k, int& count, int& answer) {
        if (root == NULL)
            return;

        kthSmallest(root->left, k, count, answer);

        count++;

        if (count == k) {
            answer = root->key;
            return;
        }

        if (count < k)
            kthSmallest(root->right, k, count, answer);
    }

    void kthLargest(Node* root, int k, int& count, int& answer) {
        if (root == NULL)
            return;

        kthLargest(root->right, k, count, answer);

        count++;

        if (count == k) {
            answer = root->key;
            return;
        }

        if (count < k)
            kthLargest(root->left, k, count, answer);
    }

    void findValues(Node* root, int k) {
        int total = countNodes(root);

        if (k < 1 || k > total) {
            cout << "Invalid value of K!" << endl;
            return;
        }

        int count = 0;
        int small = -1;

        kthSmallest(root, k, count, small);

        count = 0;
        int large = -1;

        kthLargest(root, k, count, large);

        cout << "\n" << k << "th Smallest Key: " << small;
        cout << "\n" << k << "th Largest Key: " << large;
    }

    void showSideHeights(Node* root) {
        if (root == NULL) {
            cout << "Tree is empty!";
            return;
        }

        cout << "\nLeft Side Height: "
             << getHeight(root->left);

        cout << "\nRight Side Height: "
             << getHeight(root->right);

        cout << "\nRoot Key: " << root->key;
    }
};

int main() {
    AVLTree tree;
    Node* root = NULL;

    int values[] = {10, 5, 15, 3, 7, 12};

    for (int i = 0; i < 6; i++) {
        root = tree.insert(root, values[i]);
    }

    cout << "AVL Tree: ";
    tree.display(root);

    int k;

    cout << "\n\nEnter K value: ";
    cin >> k;

    tree.findValues(root, k);

    cout << "\n\nTree Heights:";
    tree.showSideHeights(root);

    return 0;
}
