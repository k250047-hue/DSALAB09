
#include <iostream>
using namespace std;

class Node {
public:
    int roll;
    int height;
    Node* left;
    Node* right;

    Node(int r) {
        roll = r;
        height = 1;
        left = NULL;
        right = NULL;
    }
};

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

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* temp = x->right;

    x->right = y;
    y->left = temp;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* temp = y->left;

    y->left = x;
    x->right = temp;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}

Node* insert(Node* root, int roll) {
    if (root == NULL)
        return new Node(roll);

    if (roll < root->roll)
        root->left = insert(root->left, roll);
    else if (roll > root->roll)
        root->right = insert(root->right, roll);
    else
        return root;

    root->height = 1 + max(getHeight(root->left),
                           getHeight(root->right));

    int balance = getBalance(root);

    if (balance > 1 && roll < root->left->roll)
        return rightRotate(root);

    if (balance < -1 && roll > root->right->roll)
        return leftRotate(root);

    if (balance > 1 && roll > root->left->roll) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
   
    if (balance < -1 && roll < root->right->roll) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

void display(Node* root) {
    if (root != NULL) {
        cout << root->roll << " ";
        display(root->left);
        display(root->right);
    }
}

int main() {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);

    cout << "AVL Tree before inserting 15: ";
    display(root);

    root = insert(root, 15);

    cout << "\nAVL Tree after inserting 15: ";
    display(root);

    cout << "\nHeight of AVL Tree: " << getHeight(root);

    cout << "\nBalance Factor of Root: " << getBalance(root);

    return 0;
}


/*

    dry run 

Given Values: 10, 20, 30, 40, 50
New Value: 15

STEP 1: INSERT 10, 20, 30

Balance Factors:
BF(10) = -2
BF(20) = -1

RR CASE AT NODE 10
Perform LEFT ROTATION at 10.

Before Rotation:

10
  \
   20
     \
      30

After Left Rotation:

       20
      /  \
     10   30
-
STEP 2: INSERT 40 AND 50

Tree becomes:

       20
      /  \
     10   30
            \
             40
               \
                50

Node 30 becomes unbalanced.

Balance Factors:
BF(30) = -2
BF(40) = -1

RR CASE AT NODE 30
Perform LEFT ROTATION at 30.

After Left Rotation:

        20
       /  \
      10   40
          /  \
         30   50


STEP 3: INSERT NEW VALUE 15

Tree becomes:

        20
       /  \
      10   40
        \  / \
        15 30 50

STEP 4: CHECK BALANCE FACTORS

BF = Height(Left) - Height(Right)

Node 15: BF = 0
Node 10: BF = -1
Node 30: BF = 0
Node 50: BF = 0
Node 40: BF = 0
Node 20: BF = 0

All balance factors are between -1 and +1.

Therefore, the tree is balanced.

No rotation is required after inserting 15.

STEP 5: FINAL AVL TREE

             20
            /  \
           10   40
             \  / \
             15 30 50

STEP 6: HEIGHT OF TREE

Longest path:

20 -> 10 -> 15

Height in nodes = 3
Height in edges = 2

Final Height = 3 levels.


*/
