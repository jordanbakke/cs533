/*
 * CS533 Course Project
 * Thread Queue ADT
 * queue.c
 *
 * Feel free to modify this file. Please thoroughly comment on
 * any changes you make.
 */


#include "queue.h"
#include <stdlib.h>

void thread_enqueue(queue * q, thread * t) {

  queue_node * temp = malloc(sizeof(queue_node));

  temp->t = t;
  temp->next = NULL;

  if(!q->head) {
    q->head = q->tail = temp;
    return;
  }

  q->tail->next = temp;
  q->tail = temp;  

}

thread * thread_dequeue(queue * q) {

  if(!q->head) {
    return NULL;
  }

  thread * t = q->head->t;
  queue_node * temp = q->head;
  q->head = q->head->next;
  free(temp);

  if(!q->head) {
    q->tail = NULL;
  }

  return t;

}

int is_empty(queue * q) {
  return !q->head;
}
