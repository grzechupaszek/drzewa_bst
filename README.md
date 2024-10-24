# AVL Tree Implementation

This project implements an AVL tree in C++. An AVL tree is a self-balancing binary search tree where the difference between heights of left and right subtrees cannot be more than one for all nodes.

## Features

- Insert nodes into the AVL tree
- Delete nodes from the AVL tree
- Search for nodes in the AVL tree
- Display the AVL tree in a 2D format
- Perform an inorder traversal of the AVL tree
- Get the height of the AVL tree

## Getting Started

### Prerequisites

- C++ compiler (e.g., g++)
#### Menu
1. Wstaw wezel
2. szukaj wezla
3. usun wezel
4. wyswietl drzewo
5. wysokosc drzewa
6. inorder traversal
0. wyjdz
 
##### Functions
insert(TreeNode* r, TreeNode* new_node)
Inserts a new node into the AVL tree.

deleteNode(TreeNode* root, int key)
Deletes a node with the specified key from the AVL tree.

recursiveSearch(TreeNode* r, int val)
Searches for a node with the specified value in the AVL tree.

print2D(TreeNode* root)
Displays the AVL tree in a 2D format.

height(TreeNode* r)
Returns the height of the AVL tree.

inorderTraversal(TreeNode* root)
Performs an inorder traversal of the AVL tree and prints the values of the nodes.
