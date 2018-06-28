#include <stdio.h>

char charQueue[2];
int isInsideDoubleQuotes = 0;
int isInsideSingleQuotes = 0;
int isInsideSingleLineComment = 0;
int isInsideMultiLineComment = 0;
int currentLineLength = 0;
int currentLineHasComment = 0;

int isInsideComment(void) {
	return isInsideSingleLineComment || isInsideMultiLineComment;
}

void putChar(int c) {
	if (c != '\0' && !isInsideComment()) {
		putchar(c);
		++currentLineLength;
	}
}

void enqueue(int c) {
	putChar(charQueue[0]);
	charQueue[0] = charQueue[1];
	charQueue[1] = c;
}

void clear(void) {
	putChar(charQueue[0]);
	putChar(charQueue[1]);
	charQueue[0] = '\0';
	charQueue[1] = '\0';
}

void checkCharQueue(void) {
	if (charQueue[0] == '/') { 
		if (charQueue[1] == '/')
			isInsideSingleLineComment = 
				isInsideMultiLineComment
				&& isInsideSingleQuotes
				&& isInsideDoubleQuotes ? 0 : 1;
		else if (charQueue[1] == '*')
			isInsideMultiLineComment =
				isInsideSingleLineComment
				&& isInsideSingleQuotes
				&& isInsideDoubleQuotes ? 0 : 1;
	}	
	else if (charQueue[0] == '*') {
		if (charQueue[1] == '/') {
			if (isInsideMultiLineComment) {
				clear();
				isInsideMultiLineComment = 0;
			}
		}
	}
	else if (charQueue[0] != '\\') {
		if (charQueue[1] == '"')
			isInsideDoubleQuotes =
				isInsideDoubleQuotes
				&& isInsideSingleQuotes
				&& isInsideSingleLineComment
				&& isInsideMultiLineComment ? 0 : 1;
		else if (charQueue[1] == '\'')
			isInsideSingleQuotes =
				isInsideSingleQuotes
				&& isInsideDoubleQuotes
				&& isInsideSingleLineComment
				&& isInsideMultiLineComment ? 0 : 1;
	}
	if (isInsideComment()) currentLineHasComment = 1;
}

int main() {
	int c;

	clear();

	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			clear();
			if (currentLineLength > 0 || !currentLineHasComment) {
				putchar('\n');
			}
			currentLineLength = 0;
			currentLineHasComment = 0;
		} else {
			enqueue(c);
			checkCharQueue();
		}

	}

	return 0;
}

/* Tests */
// Ipsum //
// Lorem
/* Ipsum
 * Lorem
 **/
/* Ipsum
lorem // add
florum */
