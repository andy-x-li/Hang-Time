# Hang-Time

A game I programmed called Hang Time for a CS class at UChicago.

The goal was the recreate a game our professor tasked us individually with. 

Hang Time is a game involving black and white pieces. The game is similar to Connect 4 except for the fact that pieces can hang in place for a period of time before eventually falling. Our game is fully customizable from the hang time, to the number of pieces in a row needed to win, to even the size of the board itself (boards size is limited at 62x62). 

To run the code: 
  1) Save proj2
  2) Open in a code editor 
  3) Execute the makefile by typing "make" in the command line
  4) Start the game by typing something such as "./play -w 10 -h 10 -t 2 -r 3 -b" in the command line 

"./play -w 10 -h 10 -t 2 -r 3 -b" has multiple flags in it. 
  - The number after the -w flag is the width of the board. 
  - The number after the -h flag is the height of the board. 
  - The number after the -t flag is the hang time of the game. 
  - The number after the -r flag is the number of pieces in a row needed to win. 
  - Flag -b represents the "bits board" (it can be replaced with flag -m to represent a "matrix board")
  
Note: "bits board" and "matrix board" have no visual differences but are instead used to demonstrate our understanding of matrices and bit manipulation. In other words, board data is stored in different ways depending on which flag is specified. 

Below is an example of the game with parameters "./play -w 15 -h 15 -t 1 -r 3 -b" (15x15 board, hang time of 1, win condition of 3): 

https://user-images.githubusercontent.com/125074849/218190793-6f1b167c-e09d-490c-b472-a39de63b9472.mov

Note: proj1 is an early version of the code used as a checkpoint for development during class. 


