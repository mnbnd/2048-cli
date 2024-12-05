// Jacob Yuill, John Sievertsen
// 2048 Game 11/21/24
// This file runs the main game loop for the 2048 program.
// It will continue to run until the user decides to quit or the game is finished (Win or Loss condition). 
#include <iostream>
#include <cstdlib>
#include <ctime> //for seeding rng
#include "Board.h"

using namespace std;

void playGame() {
  Board board; //new obj
  char input;

  while (1) {
    board.printBoard();
    if (board.hasWon()) {
      cout << "You won! You reached 2048!\n";
      break;
    }
    if (board.isGameOver()) {
      cout << "Game over! No more moves possible.\n";
      break;
    }
    cout << "Enter move [W A S D]: ";
    cin >> input;
    bool moved = board.move(input); // Move the tiles
    if (moved) {
      board.addRandomTile();
    } else {
      cout << "Invalid move. Try again." << endl;
    }
  }
}

int main() {
  srand(static_cast<unsigned int>(time(0))); //seed board RNG
  char choice;
  do { //run game at least once = use do while loop 
    playGame();
    cout << "Do you want to start a new game? (Y/N): ";
    cin >> choice;
  } while (choice == 'Y' || choice == 'y');
}


