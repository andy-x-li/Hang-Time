/* CMSC 15200, proj 2, Andy Li, andyxli */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "logic.h"

/* adjusted_ascii_index : A helper function that checks if a char is in the 
bounds of row and col and returns the numerical value of the given char in
the board. */
unsigned int adjusted_ascii_index(char a)
{
    if (a > 47 && a < 58)
    {
        return a - 48;
    }
    else if (a > 64 && a < 91)
    {
        return a - 55;
    }
    else if (a > 96 && a < 123)
    {
        return a - 61;
    }
    else 
    {
        return 62;
    }
}

/* error_check : A helper function that checks for command line input
errors such as if all parameters were passed in or not and if they are in
the allowed range. */
void error_check(int height, int width, int run, int hangtime, 
                unsigned int input_count)
{
    if (input_count < 5)
    {
        fprintf(stderr, "error_check: missing command line arguments\n");
        exit(1);
    }
    if (input_count > 5)
    {
        fprintf(stderr, "error_check: too many command line arguments\n");
        exit(1);
    }
    int flag = 0;
    if (width <= 0)
    {
        fprintf(stderr, "error_check: width should be more than zero\n");
        flag = 1;
    }
    if (height <= 0)
    {
        fprintf(stderr, "error_check: height should be more than zero\n");
        flag = 1;
    }
    if (hangtime < 0)
    {
        fprintf(stderr, "error_check: hangtime cannot be negative\n");
        flag = 1;
    }
    if (run < 2)
    {
        fprintf(stderr, "error_check: run should be more than one\n");
        flag = 1;
    }
    if (flag == 1)
    {
        exit(1);
    }
}

/* main : makes a new game based on given parameters from the command line and
two parameters provided by the user(s). main also draws the state of the board
after evey turn and handles the interactions needed to process each player's 
turn and whether or not the win condition was met. */
int main(int argc, char *argv[])
{
    int temp_width;
    int temp_height;
    int temp_run;
    int temp_hangtime;
    int type_flag = 0; // 0 for bits 1 for matrix
    unsigned int input_count = 0;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "-b") == 0)
        {
            type_flag = 1;
            input_count++;
        }
        else if (strcmp(argv[i], "-m") == 0)
        {
            type_flag = 0;
            input_count++;
        }
        else if (strcmp(argv[i], "-w") == 0)
        {
            temp_width = atoi(argv[i + 1]);
            i++;
            input_count++;
        }
        else if (strcmp(argv[i], "-h") == 0)
        {
            temp_height = atof(argv[i + 1]);
            i++;
            input_count++;
        }
        else if (strcmp(argv[i], "-r") == 0)
        {
            temp_run = atof(argv[i + 1]);
            i++;
            input_count++;
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            temp_hangtime = atof(argv[i + 1]);
            i++;
            input_count++;
        }
    }
    error_check(temp_height, temp_width, temp_run, temp_hangtime, input_count);
    // unsigned ints created after checking if given parameters are negative
    unsigned int width = temp_width; 
    unsigned int height = temp_height;
    unsigned int run = temp_run;
    unsigned int hangtime = temp_hangtime;
    game* current_game;
    if (type_flag == 0)
    {
        current_game = new_game(run, hangtime, width, height, MATRIX);
    }
    else
    {
        current_game = new_game(run, hangtime, width, height, BITS);
    }
    board_show(current_game->b);
    while (game_outcome(current_game) == IN_PROGRESS)
    {
        char row;
        char col;
        printf("\n");
        if (current_game->player == BLACKS_TURN)
        {
            printf("Please enter a row and a column for black: ");
        }
        else
        {
            printf("Please enter a row and a column for white: ");
        }
        scanf("%c%c%*c", &row, &col);
        printf("\n");
        unsigned int adjusted_row = adjusted_ascii_index(row);
        unsigned int adjusted_col = adjusted_ascii_index(col);
        // adjusted_ascii_index returns 62 if the index is not supported
        if (adjusted_row == 62 && adjusted_col == 62)
        {
            printf("Row and column inputs are invalid\n");
        }
        else if (adjusted_row == 62)
        {
            printf("Row input is invalid\n");
        }
        else if (adjusted_col == 62)
        {
            printf("Column input is invalid\n");
        }
        // places the piece and changes the turn only if it is possible
        else if (place_piece(current_game, make_pos(adjusted_row, adjusted_col)))
        {
            board_show(current_game->b);
        }
    }
    printf("\n");
    if (game_outcome(current_game) == WHITE_WIN)
    {
        printf("White Wins\n\n");
    }
    else if (game_outcome(current_game) == DRAW)
    {
        printf("It's a Draw\n\n");
    }
    else
    {
        printf("Black Wins\n\n");
    }
    game_free(current_game);
}