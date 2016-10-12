#include "queue.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * implementation of a Priority queue using a linked list
 * use priority argument in add() to iterate through queue and place
 */

struct q_element {
	struct q_element *next;
	void *value;
	int prio;
	
	//may have to add prio value, pre value
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
 * if empty, p is head. else check if p prio > heads. If so, p is head
 * else iterate through list until prio is less and stop.
 */
int q_add(Queue *q, Item i, int prio) {
	struct q_element *p;
	struct q_element *temp;
	struct q_element *temp1;
	struct q_element *new_node;

	p = (struct q_element *)malloc(sizeof(struct q_element));
	if (p != NULL) {
		p->value = i;
		p->next = NULL;
		p->prio = prio;
		
		if (q->head == NULL)
			q->head = p;
		else
			if (p->prio > q->head->prio){ // this works i think, sorts first
				printf("PrioHead: %d\n", p->prio);				
				p->next = q->head;    // 1-10 as 10-1	
				q->head = p;
			}else{	
				p->next = q->head->next;
				temp = p;	
				//p->next = q->head->next; //p at positon 2 in queue
				//q->head->next = p;	
				printf("PrioSort: %d %d\n", p->prio, p->next->prio);
				while ((temp->next!= NULL)&&(temp->prio) <= (temp->next->prio)){
					temp = temp->next;
					printf("Prio3: %d", temp->prio);
					printf(" Prio4: %d\n", temp->next->prio);
					
				}
				temp1 = temp->next;
				temp->next = new_node;
				new_node->next;temp1;
//http://www.c4learn.com/data-structure/insert-node-at-middle-position-singly-linked-list/
				
				
			}
		return 1;
	}
	return 0;
}

/*
 * remove next Item from queue; returns NULL if queue is empty
 */

Item q_remove(Queue *q) {
	struct q_element *p;
	Item i;
	int prio;

	if (q->head == NULL)
		return NULL;
	p = q->head;
	q->head = p->next;
	if (q->head == NULL)
		q->tail = NULL;
	i = p->value;
	prio = p->prio;
	printf("Prio: %d\n", p->prio); //works!
	free(p);
	return i;
}
