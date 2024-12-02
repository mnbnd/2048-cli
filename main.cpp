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
    bool moved = board.move(input);
    if (moved) {
      board.addRandomTile();
    } else {
      cout << "Invalid move. Try again.\n";
    }
  }
}

int main() {
  srand(static_cast<unsigned int>(time(0)));
  char choice;
  do {
    playGame();
    cout << "Do you want to restart the game? (Y/N): ";
    cin >> choice;
  } while (choice == 'Y' || choice == 'y');

  cout << "Thanks for playing!\n";
  return 0;
}


