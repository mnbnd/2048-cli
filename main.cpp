// Jacob Yuill, John Sievertsen
// 2048 Game 11/21/24
// This file runs the main game loop for the 2048 program.
// It will continue to run until the user decides to quit or the game is finished (Win or Loss condition). 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "board.h"

using namespace std;

void playGame() {
  Board board;
  char input;

  while (true) {
    board.printBoard();
    if (board.hasWon()) {
      cout << "Congratulations! You reached 2048!\n";
      break;
    }
    if (board.isGameOver()) {
      cout << "Game Over! No more moves possible.\n";
      break;
    }
    cout << "Enter move (W,A,S,D): ";
    cin >> input;
    bool moved = board.move(input); // Move the tiles
    if (moved) {
      board.addRandomTile();
    } else {
      cout << "Invalid move. Try again.\n";
    }
  }
}

int main() {
  srand(static_cast<unsigned int>(time(0))); // Seed the random number generator for the board
  char choice;
  do {
    playGame();
    cout << "Do you want to restart the game? (Y/N): ";
    cin >> choice;
  } while (choice == 'Y' || choice == 'y');

  cout << "Thanks for playing!\n";
  return 0;
}


