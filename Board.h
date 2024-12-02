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

void Board::initialize() {
    // Add two initial tiles
    addRandomTile();
    addRandomTile();
}

void Board::printBoard() {
    // Print the board to the console
    cout << "-----------------------------\n";
    for (int i = 0; i < 4; i++) {
        cout << "|";
        for (int j = 0; j < 4; j++) {
            if (grid[i][j]->value != 0)
                printf("%4d |", grid[i][j]->value);
            else
                printf("     |");
        }
        cout << "\n-----------------------------\n";
    }
}

void Board::addRandomTile() {
    // Add a random tile (2 or 4) to an empty spot
    int emptyCells = 0;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j]->value == 0)
                emptyCells++;

    if (emptyCells == 0)
        return;

    int r = rand() % emptyCells;
    int count = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (grid[i][j]->value == 0) {
                if (count == r) {
                    int randValue = rand() % 10;
                    if (randValue == 0)
                        grid[i][j]->value = 4;
                    else
                        grid[i][j]->value = 2;
                    return;
                }
                count++;
            }
        }
    }
}

bool Board::move(char direction) {
    bool moved = false;
    bool merged[4][4] = { false };

    switch (direction) {
    case 'w':
    case 'W':
        // Move up
        for (int j = 0; j < 4; j++) {
            for (int i = 1; i < 4; i++) {
                if (grid[i][j]->value != 0) {
                    int k = i;
                    while (k > 0 && grid[k - 1][j]->value == 0) {
                        grid[k - 1][j]->value = grid[k][j]->value;
                        grid[k][j]->value = 0;
                        k--;
                        moved = true;
                    }
                    if (k > 0 && grid[k - 1][j]->value == grid[k][j]->value && !merged[k - 1][j]) {
                        grid[k - 1][j]->value *= 2;
                        grid[k][j]->value = 0;
                        merged[k - 1][j] = true;
                        moved = true;
                    }
                }
            }
        }
        break;
    case 's':
    case 'S':
        // Move down
        for (int j = 0; j < 4; j++) {
            for (int i = 2; i >= 0; i--) {
                if (grid[i][j]->value != 0) {
                    int k = i;
                    while (k < 3 && grid[k + 1][j]->value == 0) {
                        grid[k + 1][j]->value = grid[k][j]->value;
                        grid[k][j]->value = 0;
                        k++;
                        moved = true;
                    }
                    if (k < 3 && grid[k + 1][j]->value == grid[k][j]->value && !merged[k + 1][j]) {
                        grid[k + 1][j]->value *= 2;
                        grid[k][j]->value = 0;
                        merged[k + 1][j] = true;
                        moved = true;
                    }
                }
            }
        }
        break;
    case 'a':
    case 'A':
        // Move left
        for (int i = 0; i < 4; i++) {
            for (int j = 1; j < 4; j++) {
                if (grid[i][j]->value != 0) {
                    int k = j;
                    while (k > 0 && grid[i][k - 1]->value == 0) {
                        grid[i][k - 1]->value = grid[i][k]->value;
                        grid[i][k]->value = 0;
                        k--;
                        moved = true;
                    }
                    if (k > 0 && grid[i][k - 1]->value == grid[i][k]->value && !merged[i][k - 1]) {
                        grid[i][k - 1]->value *= 2;
                        grid[i][k]->value = 0;
                        merged[i][k - 1] = true;
                        moved = true;
                    }
                }
            }
        }
        break;
    case 'd':
    case 'D':
        // Move right
        for (int i = 0; i < 4; i++) {
            for (int j = 2; j >= 0; j--) {
                if (grid[i][j]->value != 0) {
                    int k = j;
                    while (k < 3 && grid[i][k + 1]->value == 0) {
                        grid[i][k + 1]->value = grid[i][k]->value;
                        grid[i][k]->value = 0;
                        k++;
                        moved = true;
                    }
                    if (k < 3 && grid[i][k + 1]->value == grid[i][k]->value && !merged[i][k + 1]) {
                        grid[i][k + 1]->value *= 2;
                        grid[i][k]->value = 0;
                        merged[i][k + 1] = true;
                        moved = true;
                    }
                }
            }
        }
        break;
    default:
        // Invalid input
        cout << "Invalid input. Please enter W, A, S, or D.\n";
        break;
    }

    return moved;
}

bool Board::canMove() {
    // Check if any moves are possible
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (grid[i][j]->value == 0)
                return true;
            if (i > 0 && grid[i][j]->value == grid[i - 1][j]->value)
                return true;
            if (i < 3 && grid[i][j]->value == grid[i + 1][j]->value)
                return true;
            if (j > 0 && grid[i][j]->value == grid[i][j - 1]->value)
                return true;
            if (j < 3 && grid[i][j]->value == grid[i][j + 1]->value)
                return true;
        }
    }
    return false;
}

bool Board::isGameOver() {
    return !canMove();
}

bool Board::hasWon() {
    // Check if any tile is 2048
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (grid[i][j]->value == 2048)
                return true;
    return false;
}

#endif // BOARD_H
