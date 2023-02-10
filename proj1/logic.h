/* CMSC 15200, proj 1, Andy Li, andyxli */

#ifndef LOGIC_H
#define LOGIC_H

#include <stdbool.h>
#include "board.h"

/* turn : An enum that stores two different states: one for when it's black's
turn and one for white's. */
enum turn {
    BLACKS_TURN,
    WHITES_TURN
};
typedef enum turn turn;

/* outcome : An enum that stores four different game states for the game's 
outcome. */
enum outcome {
    IN_PROGRESS,
    BLACK_WIN,
    WHITE_WIN,
    DRAW
};
typedef enum outcome outcome;

/* game : A struct that contains the game's parameters: which player's turn, a
posqueue of which elements are hanging, the board, the number of pieces in a
row needed to win (run), and the  hangtime of each element. */
struct game {
    unsigned int run, hangtime;
    board* b;
    posqueue* hanging;
    turn player;
};
typedef struct game game;

/* new_game : A function that creates a new game with the specified size and
and parameters and using the desired data representation. Raises an error if
the board cannot have a certain run size. */
game* new_game(unsigned int run, unsigned int hangtime, unsigned int width,
               unsigned int height, enum type type);

/* game_free : A function that frees a game and the board and posqueue 
it stored. */
void game_free(game* g);

/* place_piece : A function that places a piece belonging to the player whose
turn it is at the specified coordinates. if the spot is taken, it does nothing
and returns false. Otherwise it returns true. After placing the current piece,
the function should also stimulate the effects of gravity on any unsupported
pieces that have lost their ability to hover. The function also changes the 
turn to the next player. If an illegal move was requested, the same player 
should call the function again. */
bool place_piece(game* g, pos p);

/* game_outcome : A function that reports the outcome of a completed game or
that the game is still in progress. */
outcome game_outcome(game* g);

#endif /* LOGIC_H */
