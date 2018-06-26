#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_TAB_SIZE 4

int main(int argc, char *argv[])
{
	int c, currentLineLength = 0,
		tabSize = argc < 2 ? DEFAULT_TAB_SIZE : atoi(argv[1]);

	while((c = getchar()) != EOF) {
		if (c == '\t') {
			do {
				putchar(' ');
				++currentLineLength;
			} while (currentLineLength % tabSize != 0);
		} else {
			putchar(c);
			c == '\n' ?
				currentLineLength = 0 :
				++currentLineLength;
		}
	}

	return 0;
}
