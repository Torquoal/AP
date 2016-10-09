#include <stdio.h>
#include <string.h>

#define IN 1
#define OUT 0
#define MAX 30

main()
{
	int c, state, i;
	
	state = OUT;
	// always returns 1 word if any space is made, but returns
	// correct number of words in normal sentence
	while ((c=getchar()) != EOF){
		if (isalpha(c)){
			putchar(c);
			state = IN;	
		} else {
			if (state == IN){
				putchar('\n');
			} 
			state = OUT;
		}
	}
	
	if(state == IN){
		putchar('\n');
	}
	return 0;
}
