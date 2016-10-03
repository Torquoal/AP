#include <stdio.h>
#include <string.h>

#define IN 1
#define OUT 0
#define MAX 30

main()
{
	int c, state, i;
	char  currentWord[MAX];
	
	i = 0;
	state = OUT;
	// always returns 1 word if any space is made, but returns
	// correct number of words in normal sentence
	while ((c=getchar()) != EOF){
		if (isalpha(c)){
			if (state == OUT){
				state = IN;
				
			} 
			currentWord[i] = tolower(c);
			i++;
			
		}else{
			if(state = IN){
				currentWord[i] = '\0';
				printf("Previous Word: %s\n", currentWord);
				memset( currentWord, 0, MAX);
				state = OUT;
				i = 0;
			}
			
		}

	}
	
}