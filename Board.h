#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Node.h"

using namespace std;

class Board {
private:
  Node* grid[4][4]; // 4x4 grid of Node pointers

  // Delete copy constructor and copy assignment operator
  Board(const Board&) = delete;
  Board& operator=(const Board&) = delete;

public:
  Board();
  ~Board();
  void initialize();
  void printBoard();
  void addRandomTile();
  bool move(char direction);
  bool canMove();
  bool isGameOver();
  bool hasWon();
};

// Implementation of Board class methods

Board::Board() {
  // Initialize the grid with Nodes
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      grid[i][j] = new Node();
    }
  }
  // Set up the pointers
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (i > 0)
        grid[i][j]->up = grid[i - 1][j];
      else
        grid[i][j]->up = NULL;
      if (i < 3)
        grid[i][j]->down = grid[i + 1][j];
      else
        grid[i][j]->down = NULL;
      if (j > 0)
        grid[i][j]->left = grid[i][j - 1];
      else
        grid[i][j]->left = NULL;
      if (j < 3)
        grid[i][j]->right = grid[i][j + 1];
      else
        grid[i][j]->right = NULL;
    }
  }
  initialize();
}

Board::~Board() {
  // Delete all Nodes
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      delete grid[i][j];
    }
  }
}


