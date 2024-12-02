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

Node::Node(int val) {
  value = val;
  up = NULL;
  down = NULL;
  left = NULL;
  right = NULL;
}
