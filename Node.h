// Jacob Yuill, John Sievertsen
// 2048 Game 11/23/24
// This file is responsible for declaring and defining the member functions of the Node class.
// The Node class is used to represent each tile on the game board.
#include <iostream>

using namespace std;

class Node {
public:
  int value;
  Node* up;
  Node* down;
  Node* left;
  Node* right;

  Node(int val = 0); //initializes value of constructor
};

Node::Node(int val) {
  value = val;
  up = NULL;
  down = NULL;
  left = NULL;
  right = NULL;
}
