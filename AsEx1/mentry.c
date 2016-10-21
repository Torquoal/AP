#include "mentry.h"
//#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <ctype.h>
#define MAXLINE 200
#define MAXARRAY 50
#define MAXPOSTCODE 10
#define HASHVALUE 101



/* me_get returns the next file entry, or NULL if end of file*/
MEntry *me_get(FILE *fd){
	struct mentry *entry;
	char line[MAXLINE];
	entry = (struct mentry *)malloc(sizeof(struct mentry));
	entry->full_address = malloc(MAXLINE*(sizeof(char)));
	entry->surname = malloc(MAXARRAY*(sizeof(char)));
	entry->postcode = malloc(MAXPOSTCODE*(sizeof(char)));
	int i, j, x, y, z;
	int k=0;
		 
	// get a new line 
	for (i = 1; i < 4; i++){
		fgets(line, MAXLINE, fd);
		
		if (line[0] ==  '\0' || !isalnum(line[0])){  //bandaid to stop mem issues
			printf("END");
			return NULL;
		} else {		

			// Add the address line to full_address for the entry
			for(j = 0; line[j] != '\n'; j++) {
   				entry->full_address[k] = line[j]; 
				k++;
			}
			
			entry->full_address[k++] = '\n'; 
			//printf("Address Line: %s\n", entry->full_address);
			
		
			switch (i){
		
				case 1 : // iterate chars of surname, add it to struct 
					for(x = 0; line[x] != ','; x++) {
   			 			entry->surname[x] = line[x]; 
					}
					x++;
					entry->surname[x] = '\0';
					//printf("Entry->Surname: %s\n", entry->surname);
					break;
				
				case 2 : // find if house number, if so, add to struct 
					if (isalnum(line[0])) {
   			 			entry->house_number = line[0] - '0';
					}
					//printf("Entry->HouseNum: %d\n", entry->house_number);
					break;
				
                case 3 : // remove non alphanum chars from postcode, put in struct
				
					for(y = 0, z = 0; line[y] != '\0' ; y++) {
					if (isalnum(line[y])){
   			 				entry->postcode[z] = line[y]; 
							z++;
						}
					}
					z++;
					entry->postcode[z] = '\0';
					//printf("Entry->Postcode: %s\n", entry->postcode);
					break;
                
                default: // somehow we have gotten past line 4 or some other weird value, exit
                    return NULL;

		
			}
		}
	}
	printf("Address Line: %s\n", entry->full_address);
	printf("%ld\n",me_hash(entry, HASHVALUE ));
	return entry;
	//return NULL;
}

/* me_hash computes a hash of the MEntry, mod size */
unsigned long me_hash(MEntry *me, unsigned long size){
	char temp[MAXLINE];
	int i, k;
	int j = 0;
	
	// add the surname, housenumber and postcode to one char array to hash
	for(i = 0; me->surname[i] != '\0'; i++) {
   		temp[j] = me->surname[i]; 
		j++;
	}	
	if((&me->house_number) != NULL){
		char c = me->house_number + '0';
		temp[j] = c;
		j++;
	}
	
	for(i = 0; me->postcode[i] != '\0'; i++) {
   		temp[j] = me->postcode[i]; 
		j++;
	}
	temp[j] = '\0';
	//printf("HashString: %s\n", temp);
	// initialise hash value, iterate over char array and build hash value

	unsigned long hash = 0;	

	for (k=0; temp[k] != '\0'; k++){
		hash = temp[k] + (33 * hash); 
	}	
	
	//printf("Hash Gen'd: %ld\n", hash % size);
	return hash % size;
	//return 1;
}

/* me_print prints the full address on fd */
void me_print(MEntry *me, FILE *fd){
	fputs(me->full_address, fd);
}

/* me_compare compares two mail entries, returning <0, 0, >0 if
 * me1<me2, me1==me2, me1>me2
 */
int me_compare(MEntry *me1, MEntry *me2){
	unsigned long hash1, hash2;
		
	
	hash1 = me_hash(me1, HASHVALUE );
	//printf("hash1: %ld\n", hash1);
	//printf("\0");
	
	hash2 = me_hash(me2, HASHVALUE);
	//printf("hash2: %ld\n", hash2);
	//printf("\0");
	return hash1 - hash2;
	//return 1;
}

/* me_destroy destroys the mail entry
 */
void me_destroy(MEntry *me){
	free(me);
}

