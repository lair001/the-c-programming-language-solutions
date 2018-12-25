#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main()
{
	int len; /* current line length */
	char line[MAXLINE]; /* current input line */

	while ((len = get_line(line, MAXLINE)) > 0)
		printf("%s", line);

	return 0;
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim)
{
	int c, i;
	int non_blank_index = -1;
	for (i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i) {
		s[i] = c;
		if (c != ' ' && c != '\t') non_blank_index = i;
	}
	
	if (i > 0) {
		++non_blank_index;
		s[non_blank_index] = '\n';
	}

	if (c == '\n') ++i;
	
	s[non_blank_index + 1] = '\0';

	return i;
}

