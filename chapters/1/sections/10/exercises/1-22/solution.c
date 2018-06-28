#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define DEFAULT_TAB_SIZE 8 
#define DEFAULT_MAX_LINE_LENGTH 72 /* not counting newline char */

int tabSize;
int maxLineLength;
int nextStoredWsIndex = 0;
int currentLineLength = 0;

int parseIntArg(char arg[], int defaultVal) {
	int i = 1, isInt = isdigit(arg[0]) ? 1 : 0;
	if (isInt) {
		while(isdigit(arg[i])) ++i;
		isInt = arg[i] == '\0' ? 1 : 0;
	}

	return isInt ? atoi(arg) : defaultVal;
}

void storeTab(char storedWs[]) {
	storedWs[nextStoredWsIndex] = '\t';
	++nextStoredWsIndex;
	currentLineLength = (currentLineLength / tabSize + 1) * tabSize;
}

void storeSpace(char storedWs[]) {
	storedWs[nextStoredWsIndex] = ' ';
	++nextStoredWsIndex;
	++currentLineLength;
}

void putStoredWs(char storedWs[]) {
	for (int i = 0; i < nextStoredWsIndex; ++i)
		putchar(storedWs[i]);
	nextStoredWsIndex = 0;
}

void putNewline(void) {
	putchar('\n');
	currentLineLength = 0;
	nextStoredWsIndex = 0;
}

void putChar(int c, char storedWs[]) {
	if (c == '\t') storeTab(storedWs);
	else if (c == ' ') storeSpace(storedWs);
	else if (c == '\n') putNewline();
	else {
		if (currentLineLength < maxLineLength) {
			putStoredWs(storedWs);
			putchar(c);
			++currentLineLength;
		}
		else putNewline();
	}
}
	

int main(int argc, char *argv[])
{
	int c;

	tabSize = argc < 2 ?
				DEFAULT_TAB_SIZE :
				parseIntArg(argv[1], DEFAULT_TAB_SIZE);

	maxLineLength = argc < 3 ?
				DEFAULT_MAX_LINE_LENGTH :
				parseIntArg(argv[2], DEFAULT_MAX_LINE_LENGTH);

	char storedWs[maxLineLength];

	while((c = getchar()) != EOF) putChar(c, storedWs); 
	putStoredWs(storedWs);

	return 0;
}
