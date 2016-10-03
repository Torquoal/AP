#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

int readline(char line[], int maxline);
int writeline(const char line[]);

/* main: takes line from input, writes to output
*/
main()
{
	int length;
	char line[MAXLINE];
	
	
	printf("Enter string: ");
	length = readline(line, MAXLINE);
	while (length!=0){  // doesn't quit on no line, perhaps due to '\0'?
		writeline(line);
		printf("Enter string: ");
		length = readline(line, MAXLINE);
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
/* writeline: write line to standard output, return number of chars
written */
int writeline(const char line[])
{
	fputs(line, stdout);
	return strlen(line);
}