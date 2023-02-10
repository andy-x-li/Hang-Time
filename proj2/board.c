/* CMSC 15200, proj 2, Andy Li, andyxli */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "board.h"

/* board_new : A function that creates a fully-empty board of the given size. 
The type of the board (matrix or bits) is chosen here and is not changed 
again. */
board* board_new(unsigned int width, unsigned int height, enum type type)
{
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
    res->type = type;
    if (type == MATRIX)
    {
        cell** matrix_board = (cell**)malloc(sizeof(cell*) * height);
        if (matrix_board == NULL)
        {
            fprintf(stderr, "board_new: matrix_board malloc failed\n");
            exit(1);
        }
        for (int r = 0; r < height; r++)
        {
            matrix_board[r] = (cell*)malloc(sizeof(cell) * width);
            if (matrix_board[r] == NULL)
            {
                fprintf(stderr, "board_new: board_arr[%d] malloc failed\n", r);
                exit(1);
            } 
            for (int c = 0; c < width; c++)
            {
                matrix_board[r][c] = EMPTY;
            }
        }
        res->u.matrix = matrix_board;
    }
    if (type == BITS)
    {
        int array_size;
        if ((height * width * 2) % 32 == 0)
        {
            array_size = (height * width * 2) / 32;
        }
        else 
        {
            array_size = ((height * width * 2) / 32) + 1;
        }
        unsigned int* bits_board = (unsigned int*)malloc(sizeof(unsigned int)
                                                         * array_size);
        if (bits_board == NULL)
        {
            fprintf(stderr, "board_new: bits_board malloc failed\n");
            exit(1);
        }
        for (int i = 0; i < array_size; i++)
        {
            bits_board[i] = 0;
        }
        res->u.bits = bits_board;
    }
    return res;
}

/* board_free : A function that fully frees the board including whichever 
internal representation it is using. */
void board_free(board* b)
{
    if (b->type == BITS)
    {
        free(b->u.bits);
        free(b);
    }
    else
    {
        for (int r = 0; r < b->height; r++)
        {
            free(b->u.matrix[r]); 
        }
        free(b->u.matrix);
        free(b);
    }
}

/* show_row_label : A helper function that takes in a value and prints
out the correct label for that value. */
void show_row_label(int val)
{
    if (val < 10)
    {
        printf("%d", val);
    }
    else if (val < 36)
    {
        printf("%c", val+55);
    }
    else if (val < 62)
    {
        printf("%c", val+61);
    }
    else 
    {
        printf("?");
    }
}

/* bits_show : A helper function that prints out the rows and cells of a 
bits board */
void bits_show(board* b)
{
    for (int r = 0; r < b->height; r++)
    {
        show_row_label(r);
        printf(" ");
        for (int c = 0; c < b->width; c++)
        {
            unsigned int pos_num = (c + 1) + (r * b->width);
            unsigned int arr_index;
            if (pos_num % 16 == 0)
            {
                arr_index = pos_num / 16 - 1;
            }
            else 
            {
                arr_index = pos_num / 16;
            }
            unsigned int bit_filter = 3;
            switch ((b->u.bits[arr_index] >> ((pos_num - 1) % 16) * 2) 
                    & bit_filter)
            {
                case 0:
                {
                    printf(".");
                    break;
                }
                case 2:
                {
                    printf("o");
                    break;
                }
                case 1:
                {
                    printf("*");
                    break;
                }
                default: 
                {
                    fprintf(stderr, "bits_show: unrecognizable cell\n");
                    exit(1);
                }
            } 
        }
        printf("\n");
    }
}

/* matrix_show : A helper function that prints out the rows and cells of a 
maxtrix board */
void matrix_show(board* b)
{
    for (int r = 0; r < b->height; r++)
    {
        show_row_label(r);
        printf(" ");
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
                    fprintf(stderr, "matrix_show: unrecognizable cell\n");
                    exit(1);
                }
            }
        }
        printf("\n");
    }
}

/* board_show : A function that prints the board to the screen along with the
row and column headers. */
void board_show(board* b)
{
    printf("  ");
    for (int c = 0; c < b->width; c++)
    {
        show_row_label(c);
    }
    printf("\n\n");
    if (b->type == BITS)
    {
        bits_show(b);
    }
    else 
    {
        matrix_show(b);
    }
}

/* board_get : A function that retrieves a cell at a given pos. Raise an error
if the pos row or col is out of bounds. It supports both bits and matrix
boards. */
cell board_get(board* b, pos p)
{
    if (b->height <= p.r || b->width <= p.c)
    {
        fprintf(stderr, "board_get: pos row or col is out of bounds\n");
        exit(1);
    }
    if (b->type == BITS)
    {
        unsigned int pos_num = (p.c + 1) + (p.r * b->width);
        unsigned int arr_index;
        if (pos_num % 16 == 0)
        {
            arr_index = pos_num / 16 - 1;
        }
        else 
        {
            arr_index = pos_num / 16;
        }
        unsigned int bit_filter = 3;
        switch ((b->u.bits[arr_index] >> ((pos_num - 1) % 16) * 2) 
                & bit_filter)
        {
            case 0: 
            {
                return EMPTY;
            }
            case 1:
            {
                return BLACK;
            }
            case 2: 
            {
                return WHITE;
            }
            default: 
            {
                fprintf(stderr, "board_get: unrecognizable cell\n");
                exit(1);
            }
        }
    }
    else
    {
        return b->u.matrix[p.r][p.c]; 
    }
}

/* board_set : A function that sets a cell at a certain position to a new cell
value that is provided. Raises an error if the row or col is out of bounds. It
supports both bits and matrix types. */
void board_set(board* b, pos p, cell c)
{
    if (b->height <= p.r || b->width <= p.c)
    {
        fprintf(stderr, "board_set: pos row or col is out of bounds\n");
        exit(1);
    }
    if (b->type == BITS)
    {
        unsigned int pos_num = (p.c + 1) + (p.r * b->width);
        unsigned int arr_index;
        if (pos_num % 16 == 0)
        {
            arr_index = pos_num / 16 - 1;
        }
        else 
        {
            arr_index = pos_num / 16;
        }
        unsigned int bit_value = 1;
        if (c == BLACK)
        {
            bit_value = bit_value << ((pos_num - 1) % 16) * 2;
            b->u.bits[arr_index] = b->u.bits[arr_index] | bit_value;
        }
        else if (c == EMPTY)
        {
            if (board_get(b, p) == BLACK)
            {
                bit_value = bit_value << ((pos_num - 1) % 16) * 2;
            }
            else 
            {
                bit_value = bit_value << (((pos_num - 1) % 16) * 2 + 1);
            }
            b->u.bits[arr_index] = b->u.bits[arr_index] ^ bit_value;
        }
        else 
        {
            bit_value = bit_value << (((pos_num - 1) % 16) * 2 + 1);
            b->u.bits[arr_index] = b->u.bits[arr_index] | bit_value;
        }
    }
    if (b->type == MATRIX)
    {
        b->u.matrix[p.r][p.c] = c;
    }
}