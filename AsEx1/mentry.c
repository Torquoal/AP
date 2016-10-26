/*  AUTHOR: Shaun Macdonald
 *  LOGIN: 1005872m
 *  TITLE: APH Exercise 1
 *  This is my own work as defined in the Academic Ethics agreement I have signed. 
 */

#include "mentry.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// define some char array sizes to malloc MEntry structs later
#define MAXLINE 500
#define MAXARRAY 50
#define MAXPOSTCODE 10



/* me_get returns the next file entry, or NULL if end of file*/
MEntry *me_get(FILE *fd){

	struct mentry *entry;
	char line[MAXLINE];
	
	entry = (struct mentry *)malloc(sizeof(struct mentry));
	entry->full_address = malloc(MAXLINE*(sizeof(char)));
	entry->surname = malloc(MAXARRAY*(sizeof(char)));
	entry->postcode = malloc(MAXPOSTCODE*(sizeof(char)));
	
	int i, j, x, y, z;
	int k=0; // k used to keep track of position in full_address while adding multiple lines
		 
	// get a new line from input 3 times
	for (i = 1; i < 4; i++){
	
		// check if there is anything on the line, if not, end of input, exit
		if (fgets(line, MAXLINE, fd) == NULL){
			return NULL;
		} else {		
			// Add the address line to full_address for the entry
			for(j = 0; line[j] != '\n'; j++, k++) {
   				entry->full_address[k] = line[j]; 
			}
			entry->full_address[k++] = '\n'; 
			
			// switch statement to handle the line depending on if its
			// line 1, 2 or 3 of the address
			switch (i){
		
				case 1 : // iterate chars of surname, add it to struct 
					for(x = 0; line[x] != ','; x++) {
   			 			entry->surname[x] = line[x]; 
					}
					entry->surname[x] = '\0';
					break;
				
				case 2 : // find if house number, if so, add to struct 
					if (isalnum(line[0])) {
   			 			entry->house_number = line[0] - '0';
					}
					break;
				
                case 3 : // remove non alphanum chars from postcode, put in struct
					for(y = 0, z = 0; line[y] != '\0' ; y++) {
						if (isalnum(line[y])){
   			 				entry->postcode[z] = line[y]; 
						}
					}
					entry->postcode[z] = '\0';
					break;
                
                default: // somehow we have gotten past line 3, exit
                    return NULL;
			}
		}
	}
	return entry;
}

/* me_hash computes a hash of the MEntry, mod size */
unsigned long me_hash(MEntry *me, unsigned long size){
	char temp[MAXLINE];
	int i, k;  // iterate over surname and postcode
	int j = 0; // keep track of position in temp .
	
	// add the surname, housenumber and postcode to one char array to hash
	for(i = 0; me->surname[i] != '\0'; i++, j++) {
   		temp[j] = me->surname[i]; 
	}	
	if((&me->house_number) != NULL){
		char c = me->house_number + '0';
		temp[j] = c;
		j++;
	}
	for(i = 0; me->postcode[i] != '\0'; i++, j++) {
   		temp[j] = me->postcode[i]; 
	}
	temp[j] = '\0';

	// initialise hash value, iterate over char array and build hash value

	unsigned long hash = 0;	

	// take temp char array and produce hash
	for (k=0; temp[k] != '\0'; k++){
		hash = temp[k] + (33 * hash); 
	}	
	return hash % size;
}

/* me_print prints the full address on fd */
void me_print(MEntry *me, FILE *fd){
	fputs(me->full_address, fd);
}

/* me_compare compares two mail entries, returning <0, 0, >0 if
 * me1<me2, me1==me2, me1>me2
 */
int me_compare(MEntry *me1, MEntry *me2){
	
	// check to see if surname, number and postcode are all equal. If so, return 0;
	if ((strcmp(me1->surname, me2->surname) == 0)
		&& (strcmp(me1->postcode, me2->postcode) ==0)
		&& (me1->house_number == me2->house_number)){
			return 0;
	
	/* one of the elements if no equal, check each. If its not equal, return value
	 * of the comparison.
	 */
	}else{
		int x;
		if ( (x = (strcmp(me1->surname, me2->surname)) != 0)){ 
			return x;
		}
		if ( (x = (strcmp(me1->postcode, me2->postcode)) != 0)){ 
			return x;
		}
		return me1->house_number - me2->house_number;  	
	}
}


/* me_destroy destroys the mail entry
 */
void me_destroy(MEntry *me){
	free(me);
}

