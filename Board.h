// Jacob Yuill, John Sievertsen
// 2048 Game 11/23/24
// This file is responsible for declaring and defining the member functions of the Board class.
// The functions include most of the game logic, such as moving tiles, checking for a win or loss, and adding random tiles.
#include <iostream>
#include <cstdlib> //for srand
#include <ctime> //for seeding RNG
#include "Node.h"

using namespace std;

class Board {
private:
  Node* grid[4][4]; // 4x4 grid of Node pointers

 //copy constructor and copy assignment operator for rule of three compliance
  Board(const Board&) = delete;
  Board& operator=(const Board&) = delete;

public:
  Board(); //constructor
  ~Board(); //destructor
  void initialize(); //adds two tiles to board
  void printBoard(); //prints out board
  void addRandomTile(); 
  bool move(char direction);
  bool canMove(); 
  bool isGameOver();
  bool hasWon();
};

Board::Board() {
  // fill the grid with nodes
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      grid[i][j] = new Node();
    }
  }
  //initialize pointers if they exist, otherwise keep it null
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
  // Delete all nodes. Destructor
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      delete grid[i][j];
    }
  }
}

void Board::initialize() {
  //always 2 new tiles
  addRandomTile(); 
  addRandomTile();
}

void Board::printBoard() {
  cout << "-------------------------\n";
  for (int i = 0; i < 4; i++) {
    cout << "|";
    for (int j = 0; j < 4; j++) {
      if (grid[i][j]->value != 0) {
        printf("%4d |", grid[i][j]->value);
      } else {
        printf("     |");
      }
    }
    cout << "\n-------------------------\n";
  }
}

void Board::addRandomTile() {
  // Add a random tile (2 or 4) to an empty spot
  int emptyCells = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (grid[i][j]->value == 0) {
        emptyCells++;
      }
    }
  }

  if (emptyCells == 0) { //dont add anything if board is full
    return;
  }

  int r = rand() % emptyCells;
  int count = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) { // for each cell
      if (grid[i][j]->value == 0) { // if cell is empty
        if (count == r) { // and we've reached the randomly selected empty cell
          int randValue = rand() % 10; // theres a 10% chance of 4, and a 90% chance of 2 being generated
          if (randValue == 0) {
            grid[i][j]->value = 4;
          } else {
            grid[i][j]->value = 2;
          }
          return;
        }
        count++;
      }
    }
  }
}

bool Board::move(char direction) {
  //bools that see if tile has moved/merged
  bool moved = false;
  bool merged[4][4] = { false };


  // the code of each of these is the same, but with directions flipped for each cardinal direction.
  switch (direction) {
    //up
    case 'w':
    case 'W':
      for (int j = 0; j < 4; j++) { //check each column
        for (int i = 1; i < 4; i++) { //check row below
          if (grid[i][j]->value != 0) { //non empty tile
            int k = i;
            while (k > 0 && grid[k-1][j]->value == 0) { //handles movement of tiles before merging
              grid[k - 1][j]->value = grid[k][j]->value; //move current val up 
              grid[k][j]->value = 0;			 //remove initial position	
              k--;					               //move up position	
              moved = true;
            }
            if (k > 0 && grid[k-1][j]->value == grid[k][j]->value && !merged[k-1][j]) { //check if both tiles are euqal to eachother, and hasn't already merged
              grid[k - 1][j]->value *= 2; //double destination tile
              grid[k][j]->value = 0;      //make original tile empty
              merged[k - 1][j] = true;
              moved = true;
            }
          }
        }
      }
      break;
    //down
    case 's':
    case 'S':
      for (int j = 0; j < 4; j++) {
        for (int i = 2; i >= 0; i--) { //check row above
          if (grid[i][j]->value != 0) {
            int k = i;
            while (k < 3 && grid[k + 1][j]->value == 0) {
              grid[k+1][j]->value = grid[k][j]->value;
              grid[k][j]->value = 0;
              k++;
              moved = true;
            }
            if (k < 3 && grid[k + 1][j]->value == grid[k][j]->value && !merged[k + 1][j]) {
              grid[k+1][j]->value *= 2;
              grid[k][j]->value = 0;
              merged[k + 1][j] = true;
              moved = true;
            }
          }
        }
      }
      break;
   //left
   case 'a':
   case 'A':
      for (int i = 0; i < 4; i++) { //check each column
        for (int j = 1; j < 4; j++) { //check row left
          if (grid[i][j]->value != 0) { //non empty tile
            int k = j;
            while (k > 0 && grid[i][k-1]->value == 0) { //handles movement of tiles before merging
              grid[i][k-1]->value = grid[i][k]->value; //move current val up 
              grid[i][k]->value = 0; //remove initial position
              k--;                   //move up position
              moved = true; 
            }
            if (k > 0 && grid[i][k-1]->value == grid[i][k]->value && !merged[i][k - 1]) { //check if both tiles are equal to each other and hasn't merged this turn
              grid[i][k-1]->value *= 2; //double destination tile
              grid[i][k]->value = 0; //make original tile empty
              merged[i][k-1] = true;
              moved = true;
            }
          }
        }
      }
      break;
    //right
    case 'd':
    case 'D':
      for (int i = 0; i < 4; i++) {
        for (int j = 2; j >= 0; j--) {
          if (grid[i][j]->value != 0) {
            int k = j;
            while (k < 3 && grid[i][k+1]->value == 0) {
              grid[i][k+1]->value = grid[i][k]->value;
              grid[i][k]->value = 0;
              k++;
              moved = true;
            }
            if (k < 3 && grid[i][k+1]->value == grid[i][k]->value && !merged[i][k+1]) {
              grid[i][k+1]->value *= 2;
              grid[i][k]->value = 0;
              merged[i][k+1] = true;
              moved = true;
            }
          }
        }
      }
      break;
    default: //if no good input found
      cout << "Invalid input. Use [W A S D]" << endl;
      break;
  }

  return moved;
}

bool Board::canMove() {
  //loop whole board and check if the values equal one another at each section AND that is it is not on a corner
  //do this for each direction, and if at least one move is found, then return true
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (grid[i][j]->value == 0) {
        return true;
      }
      if (i > 0 && grid[i][j]->value == grid[i - 1][j]->value) {
        return true;
      }
      if (i < 3 && grid[i][j]->value == grid[i + 1][j]->value) {
        return true;
      }
      if (j > 0 && grid[i][j]->value == grid[i][j - 1]->value) { 
        return true;
      }
      if (j < 3 && grid[i][j]->value == grid[i][j + 1]->value) {
        return true;
      }
    }
  }
  return false;
}

bool Board::isGameOver() {
  return !canMove();
}

bool Board::hasWon() {
  // Check if any tile is 2048
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (grid[i][j]->value == 2048) {
        return true;
      }
    }
  }
  return false;
}
