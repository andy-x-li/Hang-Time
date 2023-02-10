/* CMSC 15200, proj 1, Andy Li, andyxli */

#ifndef POS_H
#define POS_H

#include <stdbool.h>

/* pos : A struct that holds a location on the game board. It uses zero-based
indexing and rows and columns to achieve this. 
(The top left corner would be r=0, c=0) */
struct pos {
    unsigned int r, c;
};
typedef struct pos pos;

/* pq_entry : A struct that represents a queue element. It stores the actual
position and a next pointer. (points to NULL if it is the last element) */
typedef struct pq_entry pq_entry;
struct pq_entry {
    pos p;
    pq_entry* next;
};

/* posqueue : A struct that represents a pos linked list. Used when preforming
operations on the queue, we will pass this struct rather than a pointer to the
first element. The struct also stores the length of the queue. */
struct posqueue {
    pq_entry *head, *tail;
    unsigned int len;
};
typedef struct posqueue posqueue;

/* make_pos : a function that takes in a row index and a column index and 
returns a pos struct with those values stored */
pos make_pos(unsigned int r, unsigned int c);

/* posqueue_new : Allocates a new, empty queue. */
posqueue* posqueue_new();

/* pos_enqueue : Adds a position to the queue, at the back. */
void pos_enqueue(posqueue* q, pos p);

/* pos_dequeue: Removes and returns the element at the front of the queue or 
raise an error if the queue is empty. */
pos pos_dequeue(posqueue* q);

/* posqueue_member : Determines if the given pos is in the queue or not. */
bool posqueue_member(posqueue* q, pos p);

/* posqueue_free : Entirely dellocates an existing queue. */
void posqueue_free(posqueue* q);

#endif /* POS_H */
