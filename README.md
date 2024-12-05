# 2048
2048 project for COSC202

There are no flags you need to run the program with, just type "make" to run the makefile and then run the game binary 2048. It instantly puts you into a game. 

The only other thing the makefile can do is "make clean"  which just removes the binary it compiled. I (Jacob) copied the makefile from one of the other labs and just retooled it for our project.

Our program is a CLI clone of 2048. You can move using WASD, with each direction corresponding to how it does like other video games. When a game is won/failed, it will prompt you if you want to start a new one. You can only do one move at a time however, by typing in the direction character then pressing enter to submit.

The only way to exit the program prematurely is by doing a C-c SIGINT, but it otherwise prompts you if you want to quit.

Other than that, it should be pretty straightforward.
