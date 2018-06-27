#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFAULT_TAB_SIZE 8 

int tabSize;
int storedSpaces = 0;
int currentLineLength = 0;

int parseTabSize(char arg[]) {
	int i = 1, isInt = isdigit(arg[0]) ? 1 : 0;
	if (isInt) {
		while(isdigit(arg[i])) ++i;
		isInt = arg[i] == '\0' ? 1 : 0;
	}

	return isInt ? atoi(arg) : DEFAULT_TAB_SIZE;
}

void putTab(void) {
	putchar('\t');
	storedSpaces = 0;
	currentLineLength = (currentLineLength / tabSize + 1) * tabSize;
}

void storeSpace(void) {
	++storedSpaces;
	++currentLineLength;
	if (currentLineLength % tabSize == 0) putTab();
}

void putStoredSpaces(void) {
	while (storedSpaces > 0) {
 		putchar(' ');
		--storedSpaces;
	}
}

void putChar(int c) {
	if (c == '\t') putTab();
	else if (c == ' ') storeSpace();
	else {
		putStoredSpaces();
		putchar(c);
		c == '\n' ? currentLineLength = 0  : ++currentLineLength;
	}
}
	

int main(int argc, char *argv[])
{
	int c;

	tabSize = argc < 2 ? DEFAULT_TAB_SIZE : parseTabSize(argv[1]);

	while((c = getchar()) != EOF) putChar(c); 
	putStoredSpaces();

	return 0;
}
