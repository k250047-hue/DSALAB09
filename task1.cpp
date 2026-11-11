
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


/*

EXPLANATION OF THE CODE:

1. NODE CLASS:
   The Node class represents each node of the tree.
   Each node contains three things:
   - data stores the value of the node.
   - left stores the address of its left child.
   - right stores the address of its right child.
   The constructor initializes the data and sets both child
   pointers to NULL.

2. getHeight() FUNCTION:
   This function calculates the height of a tree.
   If the root is NULL, it returns 0.
   Otherwise, it calculates the height of the left and right
   subtrees and returns the greater height plus 1.

3. getBalance() FUNCTION:
   This function calculates the balance factor of a node.
   It subtracts the right subtree height from the left subtree
   height.
   Balance Factor = Left Height - Right Height.
   If the result is greater than 1 or less than -1,
   the node is unbalanced.

4. rotateRight() FUNCTION:
   This function performs a right rotation.
   Suppose the original tree is:

           10
          /
         6
        / \
       4   8

   oldRoot points to node 10.
   newRoot points to node 6.
   middleTree points to node 8.

   First, newRoot stores the address of oldRoot's left child.
   Then, middleTree stores the right child of newRoot.
   After that, newRoot->right = oldRoot connects node 6
   with node 10 as its right child.
   Finally, oldRoot->left = middleTree connects node 8
   as the left child of node 10.

   The resulting tree is:

           6
          / \
         4   10
            /
           8

   The function returns newRoot because node 6 becomes
   the new root of this subtree.

5. rotateLeft() FUNCTION:
   This function performs a left rotation.
   Suppose the original tree is:

       10
         \
          16
         /  \
        12   18

   oldRoot points to node 10.
   newRoot points to node 16.
   middleTree points to node 12.

   First, newRoot stores the address of oldRoot's right child.
   Then, middleTree stores the left child of newRoot.
   After that, newRoot->left = oldRoot connects node 10
   as the left child of node 16.
   Finally, oldRoot->right = middleTree connects node 12
   as the right child of node 10.

   The resulting tree is:

          16
         /  \
        10   18
          \
           12

   The function returns newRoot because node 16 becomes
   the new root of this subtree.

6. convertToAVL() FUNCTION:
   This is the main conversion function.
   It takes the root of the existing BST as input.
   First, it checks whether the root is NULL.
   Then, it recursively converts the left and right subtrees.
   After that, it calculates the balance factor of the current
   node to check whether it is balanced or not.

   FOUR ROTATION CASES:

   A. LEFT LEFT (LL) CASE:
      If the balance factor is greater than 1 and the left
      child has a balance factor greater than or equal to 0,
      a right rotation is performed.

   B. RIGHT RIGHT (RR) CASE:
      If the balance factor is less than -1 and the right
      child has a balance factor less than or equal to 0,
      a left rotation is performed.

   C. LEFT RIGHT (LR) CASE:
      If the balance factor is greater than 1 and the left
      child has a negative balance factor,
      first a left rotation is performed on the left child.
      Then, a right rotation is performed on the current node.

   D. RIGHT LEFT (RL) CASE:
      If the balance factor is less than -1 and the right
      child has a positive balance factor,
      first a right rotation is performed on the right child.
      Then, a left rotation is performed on the current node.

   If the node is already balanced, no rotation is performed.
   The function returns the root of the balanced subtree.

7. display() FUNCTION:
   This function prints the tree using preorder traversal.
   First, it prints the current node.
   Then, it prints the left subtree.
   Finally, it prints the right subtree.

8. MAIN() FUNCTION:
   In main(), two BSTs are created according to the question.

   TREE A:
       10
      /
     6
    / \
   4   8

   TREE B:
      10
        \
         16
        /  \
       12   18

   Each node is created dynamically using the new keyword.
   The left and right pointers connect the nodes to form
   the original BSTs.

   Both trees are passed to convertToAVL().
   The returned roots are stored back in treeA and treeB
   because rotations may change the original root.

   Finally, display() prints both converted AVL trees.

9. ROTATIONS PERFORMED:

   TREE A:
   Original root = 10
   Unbalanced node = 10
   Rotation = RIGHT ROTATION (LL CASE)
   New root = 6

   TREE B:
   Original root = 10
   Unbalanced node = 10
   Rotation = LEFT ROTATION (RR CASE)
   New root = 16

10. WHY DO WE RETURN THE NEW ROOT?

    During rotation, the original root may move down and
    another node becomes the new root.
    Therefore, we return the new root so that the parent
    or main function can correctly connect the rotated tree.

*/
