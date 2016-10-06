#include <stdio.h>

int main(int argc, char *argv[])

{

  int i;

  /* argc - number of command line arguements
     argv - array of pointers to the character strings of the arguements
     'echo' is the first cmd line arguement
  */

  // for each thing in command line
  for (i = 1; i< argc; i++)

    // print that string (from pointer) and add a space if its not the last
    printf("%s%s", argv[i], (i < argc - 1) ? " ": "");

  printf("\n");
  return 0;

}
