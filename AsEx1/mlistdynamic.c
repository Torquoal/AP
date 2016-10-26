/*  AUTHOR: Shaun Macdonald
 *  LOGIN: 1005872m
 *  TITLE: APH Exercise 1
 *  This is my own work as defined in the Academic Ethics agreement I have signed. 
 */

#include "mentry.h"
#include "mlist.h"
#include <stdlib.h>
#define HASHVALUE 4

typedef struct mlistnode {
	struct mlistnode *next;
	MEntry *entry;
} MListNode;

struct mlist {
	//mlist contains 2d array, ** = pointer to array of MListNode pointers
	struct mlistnode **table;
	int size; 
};

int ml_verbose = 0;	/* if true, prints diagnostics on stderr */

/* ml_create - created a new mailing list */
MList *ml_create(void) {
	MList *ml;
	unsigned int i;

	// if -v print that new list being made
	if (ml_verbose){
		fprintf(stderr, "mlist: creating mailing list\n");
	}	
	
		
	// allocate memory to list. If successful, allocate memory to the hashtable within
	// the list. Then fill the hashtable with nulls. Then return the list. 	
	if ((ml = (MList *)malloc(sizeof(MList))) != NULL) {
		if( ( ml->table = malloc( sizeof( MListNode * ) * HASHVALUE ) ) == NULL ) {
			return NULL;
		}
		
		for( i = 0; i < HASHVALUE; i++ ) {
			ml->table[i] = NULL;
		}
	}
	//printf("TableSize: %d\n", sizeof(ml->table));
	ml->size = HASHVALUE;
	return ml;
}

/* ml_add - adds a new MEntry to the list;
 * returns 1 if successful, 0 if error (malloc)
 * returns 1 if it is a duplicate */
int ml_add(MList **ml, MEntry *me){
	
	// check if me already in the list using ml_lookup, if not then..
	// compute hash value of me. Go to index of hashtable and check if
	// there are any entries. if there are, iterate through them until at the end.
	// then append. If not, make it the first entry in that bucket.
	MList *p;
	MListNode *q, *r;
	unsigned long hashme;
	int i = 0;
	
	p = *ml;
	if (ml_lookup(p, me) != NULL)
		return 1;
	

	//printf("ListSize: %d\n", p->size);	
	hashme = me_hash(me, p->size);
	
	//printf("Mentry: %s\n", me->full_address); 	
	
	if ((q = (MListNode *)malloc(sizeof(MListNode))) == NULL){
		return 0;
	}
	q->entry = me;
	// adds to the front
	q->next = p->table[hashme]; 
	p->table[hashme] = q;
	printf("Added Entry: %s\n at bucket %lu\n", q->entry->surname, hashme);

	for (r = p->table[hashme]; r != NULL; r = r->next){
		i++;
	}

	//printf("i: %d\n", i);
	
	// if a bucket is over 20, should make a new table with larger size. Then for
	// each entry in old table, add to the new one, then destroy it. Once finished,
	// destroy the old table and set MList table to the new one.


	if (i > 2){ 
		if (ml_verbose){
			fprintf(stderr, "mlist: resizing mailing list\n");
		}
		printf("Resize time!\n");
		int j = 0;
		int oldSize = p->size;
		p->size = (p->size)*2;				

		MListNode **newTable = malloc(sizeof(MListNode*)*p->size);
		printf("Table resized from %d to %d\n", oldSize, p->size);

		// for each bucket in table
		for (j = 0; j < oldSize; j++){  
			// for each entry in the bucket
			for (r = p->table[j]; r != NULL; r = r->next){
				// add entries to newTable, then free destroy this entry 			
				MListNode *temp;
				
				hashme = me_hash(r->entry, p->size);
				
				temp->entry = r->entry;
				temp->next = newTable[hashme]; 
				newTable[hashme] = temp;
				printf("Reallocated Entry: %s at bucket %d\n", temp->entry->surname, j);
			}
		}
		p->table = newTable;	
		
	}	
	return 1;
}	

/* ml_lookup - looks for MEntry in the list, returns matching entry or NULL */
MEntry *ml_lookup(MList *ml, MEntry *me){
	MList *p;
	MListNode *q;
	
	
	if (ml_verbose){
		fprintf(stderr, "mlist: ml_lookup() entered\n");
	}	
	p = ml;
	unsigned long hashme = me_hash(me, p->size);
	//printf("ListSize: %d\n", p->size);
	q = p->table[hashme];
	//printf("test q: %s\n", q->entry->surname);
	for (q = p->table[hashme]; q != NULL; q = q->next){
		//printf("CompareTime\n");
		
		// q->entry causes a seg fault when access is attempted.
		// seg fault only happens once we reach a bucket with 1/more elements
		if (me_compare(me, q->entry) == 0){
			return q->entry;
		}
	}		
	return NULL;		
}	

/* ml_destroy - destroy the mailing list */
void ml_destroy(MList *ml){
	MListNode *q;
	int i = 0;

	if (ml_verbose){
		fprintf(stderr, "mlist: ml_destroy() entered\n");
	}	
	q = ml->table[i];
	while (q != NULL) {
		MListNode *r = q->next;
		me_destroy(q->entry);
		free(q);
		q = r;
	}
	free(ml);
}

