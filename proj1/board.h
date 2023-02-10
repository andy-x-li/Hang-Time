/* CMSC 15200, proj 1, Andy Li, andyxli */

#ifndef BOARD_H
#define BOARD_H

#include "pos.h"

/* cell : An enum that provides the names for identifing which type of
content a given location stores. */
enum cell {
    EMPTY,
    BLACK,
    WHITE
};
typedef enum cell cell;

/* board_rep : A union that either stores a matrix or bits. */
union board_rep {
    enum cell** matrix;
    unsigned int* bits;
};
typedef union board_rep board_rep;
 
/* type : An enum that provides the names for identifying whether a board_rep
is a matrix or bits. */
enum type {
    MATRIX, BITS
};

/* board :  A struct that holds the width and height of the board along with
the board's type and the board itself in the form of a board_rep. */
struct board {
    unsigned int width, height;
    enum type type;
    board_rep u;
};
typedef struct board board;

/* board_new : A function that creates a fully-empty board of the given size. 
The type of the board (matrix or bits) is chosen here and is not changed 
again. For now, it raises an error if the bits representation is requested. */
board* board_new(unsigned int width, unsigned int height, enum type type);

/* board_free : A function that fully frees the board including whichever 
internal representation it is using. For now, it raises an error if the bits
representation is passed in. */
void board_free(board* b);

/* board_show : A function that prints the board to the screen along with the
row and column headers. */
void board_show(board* b);

/* board_get : A function that retrieves a cell at a given row and col. Raises
an error if the row or col is out of bounds or if the board is in bits form. */
cell board_get(board* b, pos p);

/* board_set : A function that sets a cell at a certain position to a new cell
value that is provided. Raises an error if the row or col is out of bounds or 
if the board is in bits form. */
void board_set(board* b, pos p, cell c);

#endif /* BOARD_H */
