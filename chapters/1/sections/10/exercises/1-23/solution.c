#include <stdio.h>

char charQueue[5];
int isCharLiteral = 0;
int isInsideDoubleQuotes = 0;
int isInsideSingleLineComment = 0;
int isInsideMultiLineComment = 0;
int currentLineLength = 0;
int currentLineHasComment = 0;

int isInsideComment(void);
void putChar(int c);
void enqueue(int c);
void clear(void);
void checkCharQueue(void);
void processChar(int c);
int charQueueHasNonNullChar(void);
void flushCharQueue(void);

int main() {
	int c;

	clear();

	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			flushCharQueue();
			if (currentLineLength > 0 || !currentLineHasComment) {
				putchar('\n');
			}
			currentLineLength = 0;
			isInsideSingleLineComment = 0;
			isCharLiteral = 0;
			currentLineHasComment = 0;
		} else {
			processChar(c);
		}

	}
	flushCharQueue();

	return 0;
}

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
	charQueue[1] = charQueue[2];
	charQueue[2] = charQueue[3];
	charQueue[3] = charQueue[4];
	charQueue[4] = c;
}

void clear(void) {
	charQueue[0] = '\0';
	charQueue[1] = '\0';
	charQueue[2] = '\0';
	charQueue[3] = '\0';
	charQueue[4] = '\0';
}

void checkCharQueue(void) {
	if (isCharLiteral) {
		if (charQueue[2] == '\'') isCharLiteral = 0;
	}
	else if (charQueue[0] == '/') {
		if (charQueue[1] == '/')
			isInsideSingleLineComment =
				isInsideMultiLineComment
				|| isInsideDoubleQuotes ? 0 : 1;
		else if (charQueue[1] == '*')
			isInsideMultiLineComment =
				isInsideSingleLineComment
				|| isInsideDoubleQuotes ? 0 : 1;
	}
	else if (charQueue[0] == '*') {
		if (charQueue[1] == '/') {
			if (isInsideMultiLineComment) {
				isInsideMultiLineComment = 0;
				charQueue[0] = '\0';
				charQueue[1] = '\0';
			}
		}
	}
	else if (charQueue[0] != '\\') {
		if (charQueue[1] == '\'') {
			if (charQueue[3] == '\''
					|| (charQueue[2] == '\\' && charQueue[4] == '\'')) isCharLiteral = 1;
		}
		else if (charQueue[1] == '"')
			isInsideDoubleQuotes =
				isInsideDoubleQuotes
				|| isInsideComment() ? 0 : 1;
	}
	if (isInsideComment()) currentLineHasComment = 1;
}

void processChar(int c) {
	enqueue(c);
	checkCharQueue();
}

int charQueueHasNonNullChar(void) {
	for (int i = 0; i < 5; i++) if (charQueue[i] != '\0') return 1;
	return 0;
}

void flushCharQueue(void) {
	while(charQueueHasNonNullChar()) {
		processChar('\0');
	}
}