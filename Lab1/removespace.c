#include <stdio.h>
#include <string.h>

main()
{
  int c;

  while ((c=getchar()) != EOF){
    if (isspace(c)){
      putchar(c);
      while (isspace((c=getchar())) && c != EOF);       
    }
    putchar(c);
  }
  printf("\n");
}
