//#include "mentry.h"
#include "mlist.h"
#include <stdlib.h>
#include <stdio.h>
#define HASHVALUE 101


// Hash table is size of HASHVALUE, each entry is a linked list (bucket)
// when lookup and add for a entry, take the hash value of the entry, go to the bucket
// with that hash value and iterate through bucket. For each item, compare.
// if none match, add to the end of the bucket. 

//structure should be array of linkedLists the size of HASHVALUE (static)
typedef struct mlistnode {
	struct mlistnode *next;
	MEntry *entry;
} MListNode;

//struct mlist { // hash table is array of MEntry linked lists
//	MListNode *buckets;
//};
struct mlist{
	struct mlistnode **table;
};

typedef struct mlist MList;

int ml_verbose = 0;		/* if true, prints diagnostics on stderr */

/* ml_create - created a new mailing list */
MList *ml_create(void){
	MList *m = NULL;
	int i;

	if (ml_verbose){
		fprintf(stderr, "mlist: creating mailing list\n");
	}
	// set array of mentry buckets to hashsize
	if( ( m = malloc( sizeof( MListNode * ) * HASHVALUE ) ) == NULL ) {
		return NULL;
	}
	for( i = 0; i < HASHVALUE; i++ ) {
		m[i] = NULL;
	}
	//new = malloc(HASHVALUE*(sizeof(MEntry)));	
	printf("Test: %ld\n", sizeof(m));
	return m;
	
}

/* ml_add - adds a new MEntry to the list;
 * returns 1 if successful, 0 if error (malloc)
 * returns 1 if it is a duplicate */
int ml_add(MList **ml, MEntry *me) {
	//MList *current;
	MListNode *node;
	unsigned long hash;

	// check to see if present
	if (ml_lookup(*ml, me) != NULL){
		return 1;
	}	
	// if not present, allocate node memory and put mentry into node
	if ((node = (MListNode *)malloc(sizeof(MListNode))) == NULL)
		return 0;
	node->entry = me;
	
	// get hash value for this entry, use as key into table
	hash = me_hash(me, HASHVALUE);
	node = ml->table[hash];
	while (node != NULL){
		node = node->next;
	}
	return 1;
}


/* ml_lookup - looks for MEntry in the list, returns matching entry or NULL */
MEntry *ml_lookup(MList *ml, MEntry *me) {
	MList *current;
	MListNode *node = NULL;

	if (ml_verbose){
		fprintf(stderr, "mlist: ml_lookup() entered\n");
	}	
	long hash;
	hash = me_hash(me, HASHVALUE);
	node = ml[hash];
	while (node != NULL){
		if (me_compare(me, node->entry) == 0){
			return node->entry;
		} else {
			node = node->next;
		}	
	}	
	return NULL;	
}

/*struct MEntry *ml_lookup(MList *ml, MEntry *me)
{

struct MList *mp;       
       
for (mp = ml[me_hash(me, HASHVALUE)]; mp != NULL; mp = mp->next) 
	if (me_compare(me, mp) == 0)
		return mp; // found  
	//return NULL; // not found 
//}*/


/* ml_destroy - destroy the mailing list */
void ml_destroy(MList *ml){
	free(ml);
}
	

