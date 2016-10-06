#include <stdio.h>
#include "string.h"

#define MAXLINE 1000
#define OFF 0
#define ON  1

char pattern[];
// print lines that match pattern

int main( int argc, char *argv[] )

{

  char line[MAXLINE];
  int found = 0;
  int xmode = 0;
  

 /* selects 'mode' based on input. 
    If 1 argument, normal mode.
    If 2 argument, check if a 'mode' is selected, if so add pattern and note mode
    Else if 2+ argument with no mode, error! quit and advise user.
 */

  if (argc >= 2){
    if (strcmp(argv[1], "-x") == 0 ){
      strcpy(pattern, argv[2]);
      xmode = 1;
    } else if (argc == 2) {
        strcpy(pattern, argv[1]);
    } else {
      printf("Usage: find [-x] pattern \n");
      return 0;
    }
  }else{
    printf("Usage: find [-x]  pattern \n");
    return 0;
  }

  // while standard input has a line in it
  while (fgets(line, MAXLINE, stdin) != NULL)
    
    /* strstr checks if pattern is in line and xmode isnt active, prints line OR
       checks if pattern isn't in line and xmode is active, prints line
    */
    if ( (strstr(line, pattern) != NULL) && (xmode == 0))  {
      printf("%s", line); 
      found++;
   
    } else if ((strstr(line, pattern) == NULL) && (xmode == 1 )) {
      printf("%s", line);
      found++;
    }

  return found;

}
