#include <stdio.h>
#include "string.h"
#include <stdlib.h>

#define MAXLINE 1000

char *patterns[];
// print lines that match pattern

int main( int argc, char *argv[] )
{

  char line[MAXLINE];
  int found = 0;
  int i, j, k;			//iterating ints
  int xmode = 0;		//indicates if the program is in 'x mode'
  int patlength = 0;		//how many patterns have been stored
  int p = 0;			//indicates if a pattern has matched later
  

 /* selects 'mode' based on input. 
    If 1 argument, normal mode.
    If 2 argument, check if a 'mode' is selected, if so add pattern and note mode
    Else if 2+ argument with no mode, error! quit and advise user.
 */

  if (argc >= 2){				//if we have arguments to use
	
    for (i = 1; i < argc; i++){ 		//check if arg is code or word 
    
      
      if (strcmp(argv[i], "-x")==0){		//arg is code, turn on code and move on
        xmode = 1;
        patlength++;

      } else {

          patterns[i-1] = malloc(strlen(argv[i]) + 1);     //arg is word 
          strcpy(patterns[i-1], argv[i]);		   //alloc array space and copy in
          patlength++;
      } 
      
   
    }

  } else {

    printf("Usage: find [-x] pattern \n");
    return 0;

  }
  

  //printf("%s %s\n", patterns[0], patterns[1]);
  // while standard input has a line in it

    
  while (fgets(line, MAXLINE, stdin) != NULL){
   
    /* strstr checks if pattern is in line and xmode isnt active, prints line OR
       checks if pattern isn't in line and xmode is active, prints line
    */
    if (xmode == 0) {		//if normal mode, iterate over patterns, print if match
      

      for (j = 0; j < patlength; j++){

        if (strstr(line, patterns[j]) != NULL) {
        printf("%s", line);
        found++;
        }

      }
   
    } else if (xmode == 1 ) {	//if x mode, iterate patterns, if match made p = 1.
      p = 0;			//if no match by the end, can print the word
      for (k = 1; k < patlength; k++){
        
        if (strstr(line, patterns[k]) != NULL) {
          p = 1;
        } 
      }
      if (p == 0) {
        printf("%s", line);
        found++;
        
      }    
    }
  }
  return found;

}
