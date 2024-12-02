#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node {
public:
    int value;
    Node* up;
    Node* down;
    Node* left;
    Node* right;

    Node(int val = 0);
};

// Implementation of the Node constructor
Node::Node(int val) : value(val), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}

#endif // NODE_H

