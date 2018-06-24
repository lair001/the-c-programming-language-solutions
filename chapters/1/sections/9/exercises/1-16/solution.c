#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */

int get_line(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main()
{
	int len; /* current line length */
	int max; /* maximum length seen so far */
	char line[MAXLINE]; /* current input line */
	char longest[MAXLINE]; /* longest line saved here */

	max = 0;
	while ((len = get_line(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	if (max > 0) { /* there was a line */
		printf("Max length: %d\n", max);
		if(max < MAXLINE)
			printf("Longest line:\n%s", longest);
		else
			printf("First %d characters of longest line:\n%s",
				MAXLINE - 2, longest);
	}

	return 0;
}

/* get_line: read a line into s, return length */
int get_line(char s[], int lim)
{
	int c, i;
	for (i=0; (c=getchar()) != EOF && c != '\n'; ++i) {
		if (i < lim - 2) s[i] = c;
	}
	if (i > 0) {
		++i;
		int end_index = i < lim ? i : lim - 1;
		s[end_index - 1] = '\n';
		s[end_index] = '\0';
	}
	return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
	int i;

	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}

