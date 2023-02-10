/* CMSC 15200, proj 1, Andy Li, andyxli */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "logic.h"

/* new_game : A function that creates a new game with the specified size and
and parameters and using the desired data representation. Raises an error if
the board cannot have a certain run size. */
game* new_game(unsigned int run, unsigned int hangtime, unsigned int width,
               unsigned int height, enum type type)
{
    if (run == 0)
    {
        fprintf(stderr, "new_game: run cannot be zero\n");
        exit(1);
    }
    if (run > height && run > width)
    {
        fprintf(stderr, "new_game: no win condition with run and board\n");
        exit(1);
    }
    game* res = (game*)malloc(sizeof(game));
    if (res == NULL)
    {
        fprintf(stderr, "new_game: res malloc failed\n");
        exit(1);
    }
    res->b = board_new(width, height, type);
    res->hanging = posqueue_new();
    res->run = run;
    res->hangtime = hangtime;
    res->player = BLACKS_TURN;
    return res;
}

/* game_free : A function that frees a game and the board and posqueue 
it stored. */
void game_free(game* g)
{
    posqueue_free(g->hanging);
    board_free(g->b);
    free(g);
}

/* place_piece : A function that places a piece belonging to the player whose
turn it is at the specified coordinates. if the spot is taken, it does nothing
and returns false. Otherwise it returns true. After placing the current piece,
the function should also stimulate the effects of gravity on any unsupported
pieces that have lost their ability to hover. The function also changes the 
turn to the next player. If an illegal move was requested, the same player 
should call the function again. */
bool place_piece(game* g, pos p)
{
    if (board_get(g->b, p) != EMPTY)
    {
        return false;
    }
    if (g->player == WHITES_TURN)
    {
        board_set(g->b, p, WHITE);
        g->player = BLACKS_TURN;
    }
    else 
    {
        board_set(g->b, p, BLACK);
        g->player = WHITES_TURN;
    }
    if (g->hangtime == 0)
    {
        if (p.r != g->b->height - 1 && 
            board_get(g->b, make_pos(p.r + 1, p.c)) == EMPTY)
        {
            int falled_index = p.r;
            for (int i = 1; i < g->b->height - p.r; i++)
            {
                if (board_get(g->b, make_pos(p.r + i, p.c)) != EMPTY)
                {
                    break;
                }
                falled_index++;
            }
            board_set(g->b, make_pos(falled_index, p.c), board_get(g->b, p));
            board_set(g->b, p, EMPTY);
            return true;
        }
        return true;
    }
    pos_enqueue(g->hanging, p);
    if (g->hanging->len == g->hangtime + 1)
    {
        pos removed = g->hanging->head->p;
        pos_dequeue(g->hanging);
        if (removed.r != g->b->height - 1 &&
            board_get(g->b, make_pos(removed.r + 1, removed.c)) == EMPTY)
        {
            for (int i = removed.r; i >= 0; i--)
            {
                if (board_get(g->b, make_pos(i, removed.c)) == EMPTY ||
                    posqueue_member(g->hanging, make_pos(i, removed.c)))
                {
                    break;
                }
                cell removed_type = board_get(g->b, make_pos(i, removed.c));
                board_set(g->b, make_pos(i, removed.c), EMPTY);
                int falled_index = i;
                for (int j = i + 1; j < g->b->height; j++)
                {
                    if (board_get(g->b, make_pos(j, removed.c)) != EMPTY)
                    {
                        break;
                    }
                    falled_index++;
                }
                if (removed_type == WHITE)
                {
                    board_set(g->b, make_pos(falled_index, removed.c), WHITE);
                }
                else
                {
                    board_set(g->b, make_pos(falled_index, removed.c), BLACK);
                }
            }
        }
    }
    return true;
}

/* cross_check : A helper function that checks the north, east, south, or 
west of a given pos depending on the given char representing direction. It 
also checks for diagonal directions. */
bool cross_check(game* g, pos p, enum cell cell_type, char direction)
{
    switch(direction)
    {
        case 'N':
        {
            for (int i = 1; i < g->run; i++)
            {
                if (board_get(g->b, make_pos(p.r - i, p.c)) != cell_type)
                {
                    return false;
                }
            }
            break;
        }
        case 'E':
        {
            for (int i = 1; i < g->run; i++)
            {
                if (board_get(g->b, make_pos(p.r, p.c + i)) != cell_type)
                {
                    return false;
                }
            }
            break;
        }
        case 'S':
        {
            for (int i = 1; i < g->run; i++)
            {
                if (board_get(g->b, make_pos(p.r + i, p.c)) != cell_type)
                {
                    return false;
                }
            }
            break;
        }
        case 'W':
        {
            for (int i = 1; i < g->run; i++)
            {
                if (board_get(g->b, make_pos(p.r, p.c - i)) != cell_type)
                {
                    return false;
                }
            }
            break;
        }
        case 'a': // northeast check
        {
            int NE = 1;
            while (NE < g->run)
            {
                if (board_get(g->b, make_pos(p.r - NE, p.c + NE)) != cell_type)
                {
                    return false;
                }
                NE++;
            }
            break;
        }
        case 'b': // northwest check
        {
            int NW = 1;
            while (NW < g->run)
            {
                if (board_get(g->b, make_pos(p.r - NW, p.c - NW)) != cell_type)
                {
                    return false;
                }
                NW++;
            }
            break;
        }
        case 'c': // southwest check
        {
            int SW = 1;
            while (SW < g->run)
            {
                if (board_get(g->b, make_pos(p.r + SW, p.c - SW)) != cell_type)
                {
                    return false;
                }
                SW++;
            }
            break;
        }
        case 'd': // southeast check
        {
            int SE = 1;
            while (SE < g->run)
            {
                if (board_get(g->b, make_pos(p.r + SE, p.c + SE)) != cell_type)
                {
                    return false;
                }
                SE++;
            }
            break;
        }
        default: 
        {
            fprintf(stderr, "cross_check: no match for direction given\n");
            exit(1);
        }
    }
    return true;
}

/* check_around : A helper function that checks all possible direction for a 
win. */
bool check_around(game* g, pos p,  enum cell cell_type)
{
    bool left = p.c >= g->run - 1;
    bool right = g->b->width - p.c >= g->run;
    bool up = p.r >= g->run - 1;
    bool down = g->b->height - p.r >= g->run;
    if (left)
    {
        if (cross_check(g, p, cell_type, 'W'))
        {
            return true;
        }
    }
    if (right)
    {
        if (cross_check(g, p, cell_type, 'E'))
        {
            return true;
        }
    }  
    if (up)
    {
        if (cross_check(g, p, cell_type, 'N'))
        {
            return true;
        }
    }
    if (down)
    {
        if (cross_check(g, p, cell_type, 'S'))
        {
            return true;
        }
    }
    if (right && up)
    {
        if (cross_check(g, p, cell_type, 'a'))
        {
            return true;
        }
    }
    if (left && up)
    {
        if (cross_check(g, p, cell_type, 'b'))
        {
            return true;
        }
    }
    if (left && down)
    {
        if (cross_check(g, p, cell_type, 'c'))
        {
            return true;
        }
    }
    if (right && down)
    {
        if (cross_check(g, p, cell_type, 'd'))
        {
            return true;
        }
    }
    return false;
}

/* game_outcome : A function that reports the outcome of a completed game or
that the game is still in progress. */
outcome game_outcome(game* g)
{
    bool b_win_flag = false;
    bool w_win_flag = false;
    for (int r = 0; r < g->b->height; r++)
    {
        for (int c = 0; c < g->b->width; c++)
        {
            if (b_win_flag && w_win_flag)
            {
                break;
            }
            cell cell_type = board_get(g->b, make_pos(r, c));
            if (cell_type == BLACK && b_win_flag == false)
            {
                if (check_around(g, make_pos(r, c), cell_type))
                {
                    b_win_flag = true;
                }
            }
            if (cell_type == WHITE && w_win_flag == false)
            {
                if (check_around(g, make_pos(r, c), cell_type))
                {
                    w_win_flag = true;
                }
            }
        }
    }
    if (w_win_flag && b_win_flag)
    {
        return DRAW;
    }
    else if (w_win_flag == true)
    {
        return WHITE_WIN;
    }
    else if (b_win_flag == true)
    {
        return BLACK_WIN;
    }
    else 
    {
        return IN_PROGRESS;
    }
}