#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */

int get_line(char line[], int maxline);
void rev_copy(char to[], char from[]);

/* print longest input line */
int main()
{
	int len; /* current line length */
	char line[MAXLINE]; /* current input line */
	char rev_line[MAXLINE]; /* reversed line */

	while ((len = get_line(line, MAXLINE)) > 0) {
			rev_copy(rev_line, line);
			printf("%s", rev_line);
	}

	return 0;
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim)
{
	int c, i;
	for (i=0; i<lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';

	return i;
}

/* rev_copy: create a reversed copy 'from' into 'to'; assume to is big enough */
void rev_copy(char to[], char from[])
{
	int i;
	
	i = 0;

	int from_len = 0;

	while(from[from_len] != '\0') ++from_len;

	int index_before_newline = from_len - 2;
	for (int i = index_before_newline; i >= 0; --i) 
		to[index_before_newline - i] = from[i];

	to[index_before_newline + 1] = '\n';
	to[index_before_newline + 2] = '\0';

}
