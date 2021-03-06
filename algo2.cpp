//
// Created by Radu on 11/30/2020.
//
#include "algo2.h"

Node::Node(int val) : val(val) {
    parent = left = right = NULL;

    // Node is created during insertion
    // Node is red at insertion
    color = RED;
}

bool Node::hasRedChild() {
    return (left != NULL and left->color == RED) or
           (right != NULL and right->color == RED);
}

void Node::moveDown(Node *nParent) {
    if (parent != NULL) {
        if (isOnLeft()) {
            parent->left = nParent;
        } else {
            parent->right = nParent;
        }
    }
    nParent->parent = parent;
    parent = nParent;
}

Node *Node::sibling() {
    // sibling null if no parent
    if (parent == NULL)
        return NULL;

    if (isOnLeft())
        return parent->right;

    return parent->left;
}

bool Node::isOnLeft() { return this == parent->left; }

Node *Node::uncle() const {
    // If no parent or grandparent, then no uncle
    if (parent == NULL or parent->parent == NULL)
        return NULL;

    if (parent->isOnLeft())
        // uncle on right
        return parent->parent->right;
    else
        // uncle on left
        return parent->parent->left;
}


void RBTree::fixDoubleBlack(Node *x) {
    if (x == root)
        // Reached root
        return;

    Node *sibling = x->sibling(), *parent = x->parent;
    if (sibling == NULL) {
        // No sibiling, double black pushed up
        fixDoubleBlack(parent);
    } else {
        if (sibling->color == RED) {
            // Sibling red
            parent->color = RED;
            sibling->color = BLACK;
            if (sibling->isOnLeft()) {
                // left case
                rightRotate(parent);
            } else {
                // right case
                leftRotate(parent);
            }
            fixDoubleBlack(x);
        } else {
            // Sibling black
            if (sibling->hasRedChild()) {
                // at least 1 red children
                if (sibling->left != NULL and sibling->left->color == RED) {
                    if (sibling->isOnLeft()) {
                        // left left
                        sibling->left->color = sibling->color;
                        sibling->color = parent->color;
                        rightRotate(parent);
                    } else {
                        // right left
                        sibling->left->color = parent->color;
                        rightRotate(sibling);
                        leftRotate(parent);
                    }
                } else {
                    if (sibling->isOnLeft()) {
                        // left right
                        sibling->right->color = parent->color;
                        leftRotate(sibling);
                        rightRotate(parent);
                    } else {
                        // right right
                        sibling->right->color = sibling->color;
                        sibling->color = parent->color;
                        leftRotate(parent);
                    }
                }
                parent->color = BLACK;
            } else {
                // 2 black children
                sibling->color = RED;
                if (parent->color == BLACK)
                    fixDoubleBlack(parent);
                else
                    parent->color = BLACK;
            }
        }
    }
}

void RBTree::deleteMin() {
    deleteNode(minimum);
}

void RBTree::deleteMax() {
    deleteNode(maximum);
}

int RBTree::getMin() const {
    return minimum->val;
}

Node *RBTree::getRoot() { return root; }

int RBTree::getMax() const {
    return maximum->val;
}

void RBTree::insert(int n) {
    Node *newNode = new Node(n);
    if (root == NULL) {
        // when root is null
        // simply insert value at root
        newNode->color = BLACK;
        root = newNode;
        minimum = newNode;
        maximum = newNode;
    } else {
        Node *temp = search(n);

        // connect new node to correct node
        newNode->parent = temp;

        if (n <= temp->val)
            temp->left = newNode;
        else
            temp->right = newNode;

        // fix red red voilaton if exists
        fixRedRed(newNode);
        if(n <= minimum->val) {
            minimum = newNode;
        }
        if(n > maximum->val) {
            maximum = newNode;
        }
    }
}

Node *RBTree::search(int n) {
    Node *temp = root;
    while (temp != NULL) {
        if (n <= temp->val) {
            if (temp->left == NULL)
                break;
            else
                temp = temp->left;
        } else if (n == temp->val) {
            break;
        } else {
            if (temp->right == NULL)
                break;
            else
                temp = temp->right;
        }
    }

    return temp;
}

RBTree::RBTree() { root = NULL; }

void RBTree::deleteNode(Node *v) {

    Node *u = BSTreplace(v);
    // True when u and v are both black
    bool uvBlack = ((u == NULL or u->color == BLACK) and (v->color == BLACK));
    Node *parent = v->parent;

    if (u == NULL) {
        // u is NULL therefore v is leaf
        if (v == root) {
            // v is root, making root null
            root = NULL;
        } else {
            
            if (uvBlack) {
                // u and v both black
                // v is leaf, fix double black at v
                fixDoubleBlack(v);
            } else {
                // u or v is red
                if (v->sibling() != NULL)
                    // sibling is not null, make it red"
                    v->sibling()->color = RED;
            }

            // delete v from the tree
            if (v->isOnLeft()) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
        }
        if(v == minimum) {
            minimum = parent;
        }
        if(v == maximum) {
            maximum = parent;
        }
        delete v;
        return;
    }

    if (v->left == NULL or v->right == NULL) {
        // v has 1 child
        if (v == root) {
            // v is root, assign the value of u to v, and delete u
            v->val = u->val;
            v->left = v->right = NULL;
            delete u;
        } else {
            // Detach v from tree and move u up
            if (v->isOnLeft()) {
                parent->left = u;
            } else {
                parent->right = u;
            }
            if(v == minimum) {
                minimum = u;
            }
            if(v == maximum) {
                maximum = u;
            }
            delete v;
            u->parent = parent;
            if (uvBlack) {
                // u and v both black, fix double black at u
                fixDoubleBlack(u);
            } else {
                // u or v red, color u black
                u->color = BLACK;
            }
        }
        return;
    }

    // v has 2 children, swap values with successor and recurse
    swapValues(u, v);
    deleteNode(u);
}

void RBTree::leftRotate(Node *x) {
    // new parent will be node's right child
    Node *nParent = x->right;

    // update root if current node is root
    if (x == root)
        root = nParent;

    x->moveDown(nParent);

    // connect x with new parent's left element
    x->right = nParent->left;
    // connect new parent's left element with node
    // if it is not null
    if (nParent->left != NULL)
        nParent->left->parent = x;

    // connect new parent with x
    nParent->left = x;
}

void RBTree::rightRotate(Node *x) {
    // new parent will be node's left child
    Node *nParent = x->left;

    // update root if current node is root
    if (x == root)
        root = nParent;

    x->moveDown(nParent);

    // connect x with new parent's right element
    x->left = nParent->right;
    // connect new parent's right element with node
    // if it is not null
    if (nParent->right != NULL)
        nParent->right->parent = x;

    // connect new parent with x
    nParent->right = x;
}

void RBTree::swapColors(Node *x1, Node *x2) {
    COLOR temp;
    temp = x1->color;
    x1->color = x2->color;
    x2->color = temp;
}

void RBTree::swapValues(Node *u, Node *v) {
    int temp;
    temp = u->val;
    u->val = v->val;
    v->val = temp;
}

Node *RBTree::BSTreplace(Node *x) {
    // when node have 2 children
    if (x->left != NULL and x->right != NULL)
        return successor(x->right);

    // when leaf
    if (x->left == NULL and x->right == NULL)
        return NULL;

    // when single child
    if (x->left != NULL)
        return x->left;
    else
        return x->right;
}

Node *RBTree::successor(Node *x) {
    Node *temp = x;

    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}

void RBTree::fixRedRed(Node *x) {
    // if x is root color it black and return
    if (x == root) {
        x->color = BLACK;
        return;
    }

    // initialize parent, grandparent, uncle
    Node *parent = x->parent, *grandparent = parent->parent,
            *uncle = x->uncle();

    if (parent->color != BLACK) {
        if (uncle != NULL && uncle->color == RED) {
            // uncle red, perform recoloring and recurse
            parent->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;
            fixRedRed(grandparent);
        } else {
            // Else perform LR, LL, RL, RR
            if (parent->isOnLeft()) {
                if (x->isOnLeft()) {
                    // for left right
                    swapColors(parent, grandparent);
                } else {
                    leftRotate(parent);
                    swapColors(x, grandparent);
                }
                // for left left and left right
                rightRotate(grandparent);
            } else {
                if (x->isOnLeft()) {
                    // for right left
                    rightRotate(parent);
                    swapColors(x, grandparent);
                } else {
                    swapColors(parent, grandparent);
                }

                // for right right and right left
                leftRotate(grandparent);
            }
        }
    }
}

