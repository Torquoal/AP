#include <stdio.h>
#include <string.h>

#define IN 1
#define OUT 0

main()
{
	int c, wordCount, state;
	

	wordCount = 0;
	state = OUT;
	// always returns 1 word if any space is made, but returns
	// correct number of words in normal sentence
	while ((c=getchar()) != EOF){
		if (!isalpha(c)){
			if (state == OUT){
				state = IN;
				++wordCount;
				printf("Words: %d\n", wordCount);
			}	
		}else{
			state = OUT;
		}

	}
	printf("Total Word Count: %d\n", wordCount);
}
