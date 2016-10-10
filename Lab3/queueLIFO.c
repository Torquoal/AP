#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * implementation of a LIFO queue (currently from FIFO) using a linked list
 * ignore priority argument in add()
 */

struct q_element {
	struct q_element *next;
	void *value;
};

struct queue {
	struct q_element *head;
	struct q_element *tail;
};

/*
 * create a Queue that holds Items
 * returns NULL if the create call failed (malloc failure)
 */
Queue *q_create(void) {
	struct queue *p;

	if ((p = (struct queue *)malloc(sizeof(struct queue))) != NULL) {
		p->head = NULL;
		p->tail = NULL;
	}
	return p;
}

/*
 * add Item to the Queue; 3rd arg is priority in MIN_PRIO..MAX_PRIO;
 * return 1/0 if successful/not-successful
 */
int q_add(Queue *q, Item i, int prio) {
	struct q_element *p;

	p = (struct q_element *)malloc(sizeof(struct q_element));
	if (p != NULL) {
		p->value = i;
		p->next = NULL;
		if (q->head == NULL)
			q->head = p;
		else
			q->tail->next = p;
		q->tail = p;
		return 1;
	}
	return 0;
}

/*
 * remove next Item from queue; returns NULL if queue is empty
 */

/*
  linked list, struct q_elements are nodes, have next and value
  struct q is the queue, has a head and tail
*/
Item q_remove(Queue *q) {
	struct q_element *p;
	Item i;

	if (q->head == NULL) //if queue empty, return null
		return NULL;
	//p = q->tail;
	p = q->head; //set p to head to next until penultimate 
	while (p->next != q->tail){ //iterate until node before last
		p = p->next;
	} 				
		 
	q->tail = p;		//set tail to be penultimate
	if (q->tail != q->head){
		p = p->next;	//move to old tail node, remove value, then free
	}
	if (q->tail == NULL)		
		q->head = NULL;
	
	i = p->value;
	free(p);
	return i;
}
