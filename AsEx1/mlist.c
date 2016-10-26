/*  AUTHOR: Shaun Macdonald
 *  LOGIN: 1005872m
 *  TITLE: APH Exercise 1
 *  This is my own work as defined in the Academic Ethics agreement I have signed. 
 */


#include "mentry.h"
#include "mlist.h"
#include <stdlib.h>
#define HASHVALUE 101

typedef struct mlistnode {
	struct mlistnode *next;
	MEntry *entry;
} MListNode;

struct mlist {
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
	ml->size = HASHVALUE;
	return ml;
}

/* ml_add - adds a new MEntry to the list;
 * returns 1 if successful, 0 if error (malloc)
 * returns 1 if it is a duplicate */
int ml_add(MList **ml, MEntry *me){
	
	/* check if me already in the list using ml_lookup, if not then..
	 * compute hash value of me. Go to index of hashtable and check if
	 * there are any entries. if there are, iterate through them until at the end.
	 * then append. If not, make it the first entry in that bucket.
	 */
	MList *p;
	MListNode *q;
	unsigned long hashme;
	
	p = *ml;
	if (ml_lookup(p, me) != NULL)
		return 1;
		
	hashme = me_hash(me, p->size);
	
	if ((q = (MListNode *)malloc(sizeof(MListNode))) == NULL){
		return 0;
	}
	q->entry = me;
	// adds to the front
	q->next = p->table[hashme]; 
	p->table[hashme] = q;
	
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
	
	// calculate hash index to check in table
	unsigned long hashme = me_hash(me, p->size);
	
	// iterate though index bucket, check each element, return if match found
	for (q = p->table[hashme]; q != NULL; q = q->next){
		
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
	// for each index in hash table
	for (q = ml->table[i]; i<= ml->size; i++){
		
		// iterate through bucket, free each element.
		while (q != NULL){ 
			MListNode *r = q->next;
			me_destroy(q->entry);
			free(q);
			q = r;
		}	
	}
	free(ml);
}

