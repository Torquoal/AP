#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int readline(char line[], int maxline);

/* Program to count the lines entered and display them.
*/
main()
{
	int length, lineCount;
	char line[MAXLINE];
	
	lineCount = 0;
	
	printf ("Type a line..  ");
	length = readline(line, MAXLINE);
	while (length!=0){  //ask about this condition, can set to 1 to fix?
		lineCount++;
		printf("%d lines so far...\n", lineCount);
		printf("Enter string: ");
		length = readline(line, MAXLINE); //would like to type total once lines are done
		
	}
	return 0;
}
	










/* readline: read a line from standard input, return its length or 0
*/
int readline(char line[], int max)
{
	if (fgets(line, max, stdin) == NULL){
		return 0;
	}else{
		return strlen(line);
	}	
}