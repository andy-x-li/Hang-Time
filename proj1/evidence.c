/* CMSC 15200, proj 1, Andy Li, andyxli */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "pos.h"
#include "board.h"
#include "logic.h"

/* posqueue_print : A helper function that prints out a posqueue. */
void posqueue_print(posqueue* q)
{
    pq_entry* original_head = q->head;
    for (int i = 0; i < q->len; i++)
    {
        printf("row: %d, col: %d\n", q->head->p.r, q->head->p.c);
        q->head = q->head->next;
    }
    q->head = original_head;
}

/* bool_interpreter : A helper function that prints a bool value. */
void bool_interpreter(bool a)
{
    if (a == 0)
    {
        printf("false\n");
    }
    else 
    {
        printf("true\n");
    }
}

/* cell_show : A helper function that prints out the value stored at a certain
cell. */
void cell_show(cell a)
{
    if (a == EMPTY)
    {
        printf("EMPTY\n");
    }
    else if (a == WHITE)
    {
        printf("WHITE\n");
    }
    else
    {
        printf("BLACK\n");
    }
}

/* outcome_interpreter : A helper function that prints out a given outcome */
void outcome_interpreter(outcome in)
{
    if (in == IN_PROGRESS)
    {
        printf("IN_PROGRESS\n");
    }
    else if (in == DRAW)
    {
        printf("DRAW\n");
    }
    else if (in == WHITE_WIN)
    {
        printf("WHITE_WIN\n");
    }
    else
    {
        printf("BLACK_WIN\n");
    }
}

/* evidence_make_pos : Tests make_pos. */
void evidence_make_pos()
{
    printf("==evidence_make_pos==\n");
    // returns row: 1, col: 1
    pos test1 = make_pos(1, 1);
    printf("row: %d, col: %d\n", test1.r, test1.c);
    // returns row: 2, col: 3
    pos test2 = make_pos(2, 3);
    printf("row: %d, col: %d\n", test2.r, test2.c);
}

/* evidence_posqueue_new : Tests posqueue_new. */
void evidence_posqueue_new()
{
    printf("==evidence_posqueue_new==\n");
    // returns (nil) (nil) and 0
    posqueue* test1 = posqueue_new();
    printf("len: %d\n", test1->len);
    printf("head: %p, tail: %p\n", test1->head, test1->tail);
    posqueue_free(test1);
}

/* evidence_pos_enqueue : Tests pos_enqueue. */
void evidence_pos_enqueue()
{
    printf("==evidence_pos_enqueue==\n");
    // returns len: 2 (row: 1, col: 1) (row: 2, col: 3)
    posqueue* test1 = posqueue_new();
    pos_enqueue(test1, make_pos(1, 1));
    pos_enqueue(test1, make_pos(2, 3));
    printf("len: %d\n", test1->len);
    posqueue_print(test1);
    posqueue_free(test1);
    // returns len: 3 (row: 1, col: 1) (row: 2, col: 3) (row: 4, col: 5)
    posqueue* test2 = posqueue_new();
    pos_enqueue(test2, make_pos(1, 1));
    pos_enqueue(test2, make_pos(2, 3));
    pos_enqueue(test2, make_pos(4, 5));
    printf("len: %d\n", test2->len);
    posqueue_print(test2);
    posqueue_free(test2);
    // returns len: 1 (row: 1, col: 1) 
    posqueue* test3 = posqueue_new();
    pos_enqueue(test3, make_pos(1, 1));
    printf("len: %d\n", test3->len);
    posqueue_print(test3);
    posqueue_free(test3);
}

/* evidence_pos_dequeue : Tests pos_dequeue. */
void evidence_pos_dequeue()
{
    printf("==evidence_pos_dequeue==\n");
    // returns head pos: (2, 3) len: 2 (row: 2, col: 3) (row: 4, col: 5)
    posqueue* test1 = posqueue_new();
    pos_enqueue(test1, make_pos(1, 1));
    pos_enqueue(test1, make_pos(2, 3));
    pos_enqueue(test1, make_pos(4, 5));
    pos out1 = pos_dequeue(test1);
    printf("head pos: (%d, %d)\n", out1.r, out1.c);
    printf("len: %d\n", test1->len);
    posqueue_print(test1);
    posqueue_free(test1);
    // returns head pos: (3, 3) len: 1 (row: 3, col: 3)
    posqueue* test2 = posqueue_new();
    pos_enqueue(test2, make_pos(1, 1));
    pos_enqueue(test2, make_pos(3, 3));
    pos out2 = pos_dequeue(test2);
    printf("head pos: (%d, %d)\n", out2.r, out2.c);
    printf("len: %d\n", test2->len);
    posqueue_print(test2);
    posqueue_free(test2);
}

/* evidence_posqueue_member : Tests posqueue_member. */
void evidence_posqueue_member()
{
    printf("==evidence_posqueue_member==\n");
    // test 1 should return true, true, true, false
    posqueue* test1 = posqueue_new();
    pos_enqueue(test1, make_pos(1, 1));
    pos_enqueue(test1, make_pos(2, 3));
    pos_enqueue(test1, make_pos(4, 5));
    bool_interpreter(posqueue_member(test1, make_pos(2, 3)));
    bool_interpreter(posqueue_member(test1, make_pos(4, 5)));
    bool_interpreter(posqueue_member(test1, make_pos(1, 1)));
    bool_interpreter(posqueue_member(test1, make_pos(1, 2)));
    posqueue_free(test1);
}

/* evidence_board_new : Tests board_new. */
void evidence_board_new()
{
    printf("==evidence_board_new==\n");
    // test1 should return an 65x3 empty matrix
    board* test1 = board_new(65, 3, MATRIX);
    board_show(test1);
    board_free(test1);
    // test2 should return an 5x15 empty matrix
    board* test2 = board_new(5, 15, MATRIX);
    board_show(test2);
    board_free(test2);
}

/* evidence_board_get : Tests board_get. */
void evidence_board_get()
{
    printf("==evidence_board_get==\n");
    // test1 should return EMPTY
    board* test1 = board_new(3, 3, MATRIX);
    cell t1_cell = board_get(test1, make_pos(2, 2));
    cell_show(t1_cell);
    board_free(test1);
    /* test2 should return WHITE and BLACK. */
    board* test2 = board_new(3, 3, MATRIX);
    board_set(test2, make_pos(2, 2), WHITE);
    board_set(test2, make_pos(0, 0), BLACK);
    cell t2_cell1 = board_get(test2, make_pos(2, 2));
    cell t2_cell2 = board_get(test2, make_pos(0, 0));
    cell_show(t2_cell1);
    cell_show(t2_cell2);
    board_free(test2);
}

/* evidence_board_set : Tests board_set. */
void evidence_board_set()
{
    printf("==evidence_board_set==\n");
    /* test1 should return a 3x3 matrix with the right corner set to WHITE
    and the top left corner set to BLACK. */
    board* test1 = board_new(3, 3, MATRIX);
    board_set(test1, make_pos(2, 2), WHITE);
    board_set(test1, make_pos(0, 0), BLACK);
    board_show(test1);
    board_free(test1);
}

/* evidence_new_game : Tests new_game. */
void evidence_new_game()
{
    printf("==evidence_new_game==\n");
    game* test1 = new_game(3, 2, 8, 4, MATRIX);
    board_show(test1->b);
    posqueue_print(test1->hanging);
    printf("hangtime: %d\n", test1->hangtime);
    printf("run: %d\n", test1->run);
    game_free(test1);
}

/* evidence_place_piece : Tests place_piece. */
void evidence_place_piece()
{
    printf("==evidence_place_piece==\n");
    // test1 creates a game of size 4x8 with a run of 3 and a hangtime of 2
    printf("----TEST1----\n");
    game* test1 = new_game(3, 2, 8, 4, MATRIX);
    printf("--turn 0--\n");
    board_show(test1->b);
    // should return true
    printf("--turn 1--\n");
    bool_interpreter(place_piece(test1, make_pos(1, 1)));
    board_show(test1->b);
    posqueue_print(test1->hanging);
    // should return true
    printf("--turn 2--\n");
    bool_interpreter(place_piece(test1, make_pos(0, 3)));
    board_show(test1->b);
    posqueue_print(test1->hanging);
    // should return true
    printf("--turn 3--\n");
    bool_interpreter(place_piece(test1, make_pos(2, 3)));
    board_show(test1->b);
    posqueue_print(test1->hanging);
    // should return true
    printf("--turn 4--\n");
    bool_interpreter(place_piece(test1, make_pos(1, 2)));
    board_show(test1->b);
    posqueue_print(test1->hanging);
    // should return true
    printf("--turn 5--\n");
    bool_interpreter(place_piece(test1, make_pos(0, 2)));
    board_show(test1->b);
    posqueue_print(test1->hanging);
    // should return true
    printf("--turn 6--\n");
    bool_interpreter(place_piece(test1, make_pos(1, 4)));
    board_show(test1->b);
    posqueue_print(test1->hanging);
     // should return false
    printf("--turn 7--\n");
    bool_interpreter(place_piece(test1, make_pos(1, 4)));
    board_show(test1->b);
    posqueue_print(test1->hanging);
    game_free(test1);
    // test 2 creates a game of size 5x3 with a run of 3 and a hangtime of 3
    printf("----TEST2----\n");
    game* test2 = new_game(3, 3, 5, 3, MATRIX);
    printf("--turn 0--\n");
    board_show(test2->b);
    // should return true
    printf("--turn 1--\n");
    bool_interpreter(place_piece(test2, make_pos(0, 0)));
    board_show(test2->b);
    posqueue_print(test2->hanging);
    // should return true
    printf("--turn 2--\n");
    bool_interpreter(place_piece(test2, make_pos(2, 2)));
    board_show(test2->b);
    posqueue_print(test2->hanging);
    // should return true
    printf("--turn 3--\n");
    bool_interpreter(place_piece(test2, make_pos(1, 2)));
    board_show(test2->b);
    posqueue_print(test2->hanging);
    // should return true
    printf("--turn 4--\n");
    bool_interpreter(place_piece(test2, make_pos(2, 0)));
    board_show(test2->b);
    posqueue_print(test2->hanging);
    printf("--turn 5--\n");
    bool_interpreter(place_piece(test2, make_pos(0, 1)));
    board_show(test2->b);
    posqueue_print(test2->hanging);
    printf("--turn 6--\n");
    bool_interpreter(place_piece(test2, make_pos(1, 1)));
    board_show(test2->b);
    posqueue_print(test2->hanging);
    printf("--turn 7--\n");
    bool_interpreter(place_piece(test2, make_pos(2, 4)));
    board_show(test2->b);
    posqueue_print(test2->hanging);
    printf("--turn 8--\n");
    bool_interpreter(place_piece(test2, make_pos(1, 4)));
    board_show(test2->b);
    posqueue_print(test2->hanging);
    printf("--turn 9--\n");
    bool_interpreter(place_piece(test2, make_pos(0, 4)));
    board_show(test2->b);
    posqueue_print(test2->hanging);
    game_free(test2);
}

/* evidence_game_outcome : Tests game_outcome. */
void evidence_game_outcome()
{
    printf("==evidence_game_outcome==\n");
    /* test1 creates a game of size 4x8 with a run of 3 and a hangtime of 2.
    It tests for WHITE_WIN diagonally from SW to NE. */
    printf("----TEST1----\n");
    game* test1 = new_game(3, 2, 8, 4, MATRIX);
    place_piece(test1, make_pos(1, 1));
    outcome_interpreter(game_outcome(test1)); // should return IN_PROGRESS
    place_piece(test1, make_pos(0, 3));
    outcome_interpreter(game_outcome(test1)); // should return IN_PROGRESS
    place_piece(test1, make_pos(2, 3));
    outcome_interpreter(game_outcome(test1)); // should return IN_PROGRESS
    place_piece(test1, make_pos(1, 2));
    outcome_interpreter(game_outcome(test1)); // should return IN_PROGRESS
    place_piece(test1, make_pos(0, 2));
    outcome_interpreter(game_outcome(test1)); // should return IN_PROGRESS
    place_piece(test1, make_pos(1, 4));
    board_show(test1->b);
    outcome_interpreter(game_outcome(test1)); // should return WHITE_WIN
    game_free(test1);
    /* test 2 creates a game of size 5x3 with a run of 3 and a hangtime of 3.
    It tests for a DRAW both horizontally. */
    printf("----TEST2----\n");
    game* test2 = new_game(3, 3, 5, 3, MATRIX);
    place_piece(test2, make_pos(0, 0));
    place_piece(test2, make_pos(2, 2));
    place_piece(test2, make_pos(1, 2));
    place_piece(test2, make_pos(2, 0));
    place_piece(test2, make_pos(0, 1));
    place_piece(test2, make_pos(1, 1));
    outcome_interpreter(game_outcome(test2)); // should return IN_PROGRESS
    place_piece(test2, make_pos(2, 4));
    place_piece(test2, make_pos(1, 4));
    place_piece(test2, make_pos(0, 4));
    board_show(test2->b);
    outcome_interpreter(game_outcome(test2)); // should return DRAW
    game_free(test2);
    /* test3 creates a game of size 4x8 with a run of 2 and a hangtime of 2
    It tests for BLACK_WIN horizontally. */
    printf("----TEST3----\n");
    game* test3 = new_game(2, 2, 8, 4, MATRIX);
    place_piece(test3, make_pos(3, 7));
    place_piece(test3, make_pos(1, 1));
    place_piece(test3, make_pos(0, 3));
    outcome_interpreter(game_outcome(test3)); // should return IN_PROGRESS
    place_piece(test3, make_pos(2, 3));
    place_piece(test3, make_pos(1, 2));
    board_show(test3->b);
    outcome_interpreter(game_outcome(test3)); // should return BLACK_WIN
    game_free(test3);
    /* test4 creates a game of size 4x8 with a run of 2 and a hangtime of 0
    It tests for BLACK_WIN vertically. */
    printf("----TEST4----\n");
    game* test4 = new_game(2, 0, 8, 4, MATRIX);
    place_piece(test4, make_pos(0, 0));
    place_piece(test4, make_pos(1, 1));
    place_piece(test4, make_pos(0, 0));
    board_show(test4->b);
    outcome_interpreter(game_outcome(test4)); // should return BLACK_WIN
    game_free(test4);
    /* test5 creates a game of size 4x8 with a run of 1 and a hangtime of 1
    Black should win immediately. */
    printf("----TEST5----\n");
    game* test5 = new_game(1, 1, 8, 4, MATRIX);
    place_piece(test5, make_pos(0, 0));
    board_show(test5->b);
    outcome_interpreter(game_outcome(test5)); // should return BLACK_WIN
    game_free(test5);
    /* test6 creates a game of size 4x8 with a run of 1 and a hangtime of 6
    It tests for BLACK_WIN diagonally from NW to SE. */
    printf("----TEST6----\n");
    game* test6 = new_game(2, 6, 8, 4, MATRIX);
    place_piece(test6, make_pos(0, 0));
    place_piece(test6, make_pos(2, 0));
    place_piece(test6, make_pos(1, 1));
    board_show(test6->b);
    outcome_interpreter(game_outcome(test6)); // should return BLACK_WIN
    game_free(test6);
}

/* main : Calls the evidence functions. */  
int main(int argc, char *argv[])
{
    evidence_make_pos();
    evidence_posqueue_new();
    evidence_pos_enqueue();
    evidence_pos_dequeue();
    evidence_posqueue_member();
    evidence_board_new();
    evidence_board_get();
    evidence_board_set();
    evidence_new_game();
    evidence_place_piece();
    evidence_game_outcome();
    return 0;
}

