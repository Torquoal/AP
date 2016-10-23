#include "mentry.h"
#include "mlist.h"
#include <stdlib.h>
#include <stdio.h>
#define HASHVALUE 101

typedef struct mlistnode {
	struct mlistnode *next;
	MEntry *entry;
} MListNode;

struct mlist {
	//mlist contains 2d array, ** = pointer to array of MListNode pointers
	struct mlistnode **table; 
};

int ml_verbose = 0;	/* if true, prints diagnostics on stderr */

/* ml_create - created a new mailing list */
MList *ml_create(void) {
	MList *ml;
	int i;

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
	MListNode *q;
	unsigned long hashme;
	
	p = *ml;
	if (ml_lookup(p, me) != NULL)
		return 1;
	

	
	hashme = me_hash(me, HASHVALUE);
	
	//printf("Mentry: %s\n", me->full_address); 	
	
	if ((q = (MListNode *)malloc(sizeof(MListNode))) == NULL){
		return 0;
	}
	q->entry = me;
	q->next = p->table[hashme]; 
	p->table[hashme] = q;
	//printf("TableEntry: %s\n", p->table[hashme]->entry->surname);
	
	
	
	return 1;
}	

/* ml_lookup - looks for MEntry in the list, returns matching entry or NULL */
MEntry *ml_lookup(MList *ml, MEntry *me){
	MList *p;
	MListNode *q;
	unsigned long hashme = me_hash(me, HASHVALUE);
	
	if (ml_verbose){
		fprintf(stderr, "mlist: ml_lookup() entered\n");
	}	
	p = ml;
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

