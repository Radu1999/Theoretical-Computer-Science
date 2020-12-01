//
// Created by Radu on 11/30/2020.
//

#ifndef ALGO2_H
#define ALGO2_H
#include <bits/stdc++.h>
using namespace std;

enum COLOR { RED, BLACK };

class Node {
public:
    int val;
    COLOR color;
    Node *left, *right, *parent;

    Node(int val);

    // returns pointer to uncle
    Node *uncle() const;

    // check if node is left child of parent
    bool isOnLeft();

    // returns pointer to sibling
    Node *sibling();

    // moves node down and moves given node in its place
    void moveDown(Node *nParent);

    bool hasRedChild();
};


class RBTree {
    Node *root;
    Node *minimum;
    Node *maximum;

    // left rotates the given node
    void leftRotate(Node *x);

    void rightRotate(Node *x);

    void swapColors(Node *x1, Node *x2);

    void swapValues(Node *u, Node *v);

    // fix red red at given node
    void fixRedRed(Node *x);

    // find node that do not have a left child
    // in the subtree of the given node
    Node *successor(Node *x);

    Node *predecessor(Node *x);

    // find node that replaces a deleted node in BST
    Node *BSTreplace(Node *x);

    void fixDoubleBlack(Node *x);


    // deletes the given node
    void deleteNode(Node *v);

public:
    // constructor
    // initialize root
    RBTree();

    Node *getRoot();

    // searches for given value
    // if found returns the node (used for delete)
    // else returns the last node while traversing (used in insert)
    Node *search(int n);
    // inserts the given value to tree
    void insert(int n);

    int getMax() const;

    int getMin() const;


    void deleteMax();

    void deleteMin();

};


#endif //RBT_SOLUTION_ALGO2_H
