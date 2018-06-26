#include <stdio.h>

#define TABSIZE 4

int main()
{
	int c;
	int currentLineLength = 0;

	while((c = getchar()) != EOF) {
		if (c == '\t') {
			do {
				putchar(' ');
				++currentLineLength;
			} while (currentLineLength % TABSIZE != 0);
		} else {
			putchar(c);
			c == '\n' ?
				currentLineLength = 0 :
				++currentLineLength;
		}
	}

	return 0;
}
