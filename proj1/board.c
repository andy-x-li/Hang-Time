/* CMSC 15200, proj 1, Andy Li, andyxli */

#include <stdlib.h>
#include <stdio.h>
#include "board.h"

/* board_new : A function that creates a fully-empty board of the given size. 
The type of the board (matrix or bits) is chosen here and is not changed 
again. For now, it raises an error if the bits representation is requested. */
board* board_new(unsigned int width, unsigned int height, enum type type)
{
    if (type == BITS)
    {
        fprintf(stderr, "board_new: type BITS not yet supported\n");
        exit(1);
    }
    if (width < 0 || height < 0)
    {
        fprintf(stderr, "board_new: col or row cannot be negative\n");
        exit(1);
    }
    board* res = (board*)malloc(sizeof(board));
    if (res == NULL)
    {
        fprintf(stderr, "board_new: res malloc failed\n");
        exit(1);
    }
    res->width = width;
    res->height = height;
    if (type == MATRIX)
    {
        res->type = type;
        cell** board_arr = (cell**)malloc(sizeof(cell*) * height);
        if (board_arr == NULL)
        {
            fprintf(stderr, "board_new: board_arr malloc failed\n");
            exit(1);
        }
        for (int r = 0; r < height; r++)
        {
            board_arr[r] = (cell*)malloc(sizeof(cell) * width);
            if (board_arr[r] == NULL)
            {
                fprintf(stderr, "board_new: board_arr[%d] malloc failed\n", r);
                exit(1);
            } 
            for (int c = 0; c < width; c++)
            {
                board_arr[r][c] = EMPTY;
            }
        }
       // bd_res.matrix = board_arr;
        res->u.matrix = board_arr;
        return res;
    }
    fprintf(stderr, "board_new: type not supported\n");
    exit(1);
}

/* board_free : A function that fully frees the board including whichever 
internal representation it is using. For now, it raises an error if the bits
representation is passed in. */
void board_free(board* b)
{
    if (b->type == BITS)
    {
        fprintf(stderr, "board_free: type BITS not yet supported\n");
        exit(1);
    }
    for (int r = 0; r < b->height; r++)
    {
        free(b->u.matrix[r]); 
    }
    free(b->u.matrix);
    free(b);
}

/* board_show : A function that prints the board to the screen along with the
row and column headers. */
void board_show(board* b)
{
    if (b->type == BITS)
    {
        fprintf(stderr, "board_show: type BITS not yet supported\n");
        exit(1);
    }
    printf("  ");
    for (int c = 0; c < b->width; c++)
    {
        if (c < 10)
        {
            printf("%d", c);
        }
        else if (c < 36)
        {
            printf("%c", c+55);
        }
        else if (c < 62)
        {
            printf("%c", c+61);
        }
        else 
        {
            printf("?");
        }
    }
    printf("\n\n");
    for (int r = 0; r < b->height; r++)
    {
        if (r < 10)
        {
            printf("%d ", r);
        }
        else if (r < 36)
        {
            printf("%c ", r+55);
        }
        else if (r < 62)
        {
            printf("%c ", r+61);
        }
        else 
        {
            printf("? ");
        }
        for (int c = 0; c < b->width; c++)
        {
            switch (b->u.matrix[r][c])
            {
                case EMPTY:
                {
                    printf(".");
                    break;
                }
                case WHITE:
                {
                    printf("o");
                    break;
                }
                case BLACK:
                {
                    printf("*");
                    break;
                }
                default: 
                {
                    fprintf(stderr, "board_show: unrecognizable cell\n");
                    exit(1);
                }
            }
        }
        printf("\n");
    }
}

/* board_get : A function that retrieves a cell at a given pos. Raise an error
if the pos row or col is out of bounds or if the board is in bits format. */
cell board_get(board* b, pos p)
{
    if (b->type == BITS)
    {
        fprintf(stderr, "board_get: type BITS not yet supported\n");
        exit(1);
    }
    if (b->height <= p.r || b->width <= p.c)
    {
        fprintf(stderr, "board_get: pos row or col is out of bounds\n");
        exit(1);
    }
    return b->u.matrix[p.r][p.c];
}

/* board_set : A function that sets a cell at a certain position to a new cell
value that is provided. Raises an error if the row or col is out of bounds or 
if the board is in bits form. */
void board_set(board* b, pos p, cell c)
{
    if (b->type == BITS)
    {
        fprintf(stderr, "board_set: type BITS not yet supported\n");
        exit(1);
    }
    if (b->height <= p.r || b->width <= p.c)
    {
        fprintf(stderr, "board_set: pos row or col is out of bounds\n");
        exit(1);
    }
    b->u.matrix[p.r][p.c] = c;
}