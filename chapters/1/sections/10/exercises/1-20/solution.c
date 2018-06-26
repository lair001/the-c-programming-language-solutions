#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFAULT_TAB_SIZE 4

int parseTabSize(char arg[]) {
	int i = 1, isInt = isdigit(arg[0]) ? 1 : 0;
	if (isInt) {
		while(isdigit(arg[i])) ++i;
		isInt = arg[i] == '\0' ? 1 : 0;
	}

	return isInt ? atoi(arg) : DEFAULT_TAB_SIZE;
}

int main(int argc, char *argv[])
{
	int c, currentLineLength = 0,
		tabSize = argc < 2 ? DEFAULT_TAB_SIZE : parseTabSize(argv[1]);

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
