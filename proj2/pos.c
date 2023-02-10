/* CMSC 15200, proj 2, Andy Li, andyxli */

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "pos.h"

/* make_pos : a function that takes in a row index and a column index and 
returns a pos struct with those values stored */
pos make_pos(unsigned int r, unsigned int c)
{
    pos res;
    res.c = c;
    res.r = r;
    return res; 
}

/* posqueue_new : Allocates a new, empty queue. */
posqueue* posqueue_new()
{
    posqueue* res = (posqueue*)malloc(sizeof(posqueue));
    if (res == NULL)
    {
        fprintf(stderr, "posqueue_new: malloc failed\n");
        exit(1);
    }
    res->len = 0;
    res->head = NULL;
    res->tail = NULL;
    return res;
}

/* pos_enqueue : Adds a position to the queue, at the back. */
void pos_enqueue(posqueue* q, pos p)
{
    pq_entry* temp = (pq_entry*)malloc(sizeof(pq_entry));
    if (temp == NULL)
    {
        fprintf(stderr, "pos_enqueue: malloc failed\n");
        exit(1);
    }
    temp->p = p;
    temp->next = NULL;
    if (q->len == 0)
    {
        q->head = temp;
        q->tail = temp;
        q->len = 1;
    }
    else if (q->len == 1)
    {
        q->tail = temp;
        q->head->next = q->tail;
        q->len = q->len + 1;
    }
    else
    {
        q->tail->next = temp;
        q->tail = q->tail->next;
        q->len = q->len + 1;
    }
}

/* pos_dequeue: Removes and returns the element at the front of the queue or 
raise an error if the queue is empty. */
pos pos_dequeue(posqueue* q)
{
    if (q->len == 0)
    {
        fprintf(stderr, "pos_dequeue: empty queue passed in\n");
        exit(1);
    }
    if (q->len == 1)
    {
        free(q->head);
        q->head = NULL;
        q->tail = NULL;
        q->len = q->len - 1;
        fprintf(stderr, "pos_dequeue: queue is empty - no pos to return\n");
        exit(1);
    }
    pq_entry* next_element = q->head->next;
    free(q->head);
    q->head = next_element;
    q->len = q->len - 1;
    return q->head->p;
}

/* posqueue_member : Determines if the given pos is in the queue or not. */
bool posqueue_member(posqueue* q, pos p)
{
    bool flag = false;
    pq_entry* original_head = q->head;
    for (int i = 0; i < q->len; i++)
    {
        if (q->head->p.c == p.c && q->head->p.r == p.r)
        {
            flag = true;
            break;
        }
        q->head = q->head->next;
    }
    q->head = original_head;
    return flag;
}

/* posqueue_free : Entirely dellocates an existing queue. */
void posqueue_free(posqueue* q)
{
    for (int i = 0; i < q->len; i++)
    {
        pq_entry* next_element = q->head->next;
        free(q->head);
        q->head = next_element;
    }
    free(q);
}