#include <stdio.h>

char charQueue[5];
int isCharLiteral = 0;
int isStringLiteral = 0;
int isSingleLineComment = 0;
int isMultiLineComment = 0;
int currentLineLength = 0;
int currentLineHasComment = 0;

int isComment(void);
void putChar(int c);
void enqueue(int c);
void clear(void);
int doesCharQueueHaveSingleLineCommentOpening(void);
void openSingleLineComment(void);
int doesCharQueueHaveMultiLineCommentOpening(void);
void openMultiLineComment(void);
int doesCharQueueHaveMultiLineCommentClosing(void);
void closeMultiLineComment(void);
int doesCharQueueHaveCharLiteral(void);
void openCharLiteral(void);
int doesCharQueueHaveDoubleQuotes(void);
void openOrCloseStringLiteral(void);
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
			isSingleLineComment = 0;
			isCharLiteral = 0;
			currentLineHasComment = 0;
		} else {
			processChar(c);
		}

	}
	flushCharQueue();

	return 0;
}

int isComment(void) {
	return isSingleLineComment || isMultiLineComment;
}

void putChar(int c) {
	if (c != '\0' && !isComment()) {
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

int doesCharQueueHaveSingleLineCommentOpening(void) {
	return charQueue[0] == '/' && charQueue[1] == '/';
}

void openSingleLineComment(void) {
	isSingleLineComment =
		isMultiLineComment
		|| isStringLiteral ? 0 : 1;
}

int doesCharQueueHaveMultiLineCommentOpening(void) {
	return charQueue[0] == '/' && charQueue[1] == '*';
}

void openMultiLineComment(void) {
	isMultiLineComment =
		isSingleLineComment
		|| isStringLiteral ? 0 : 1;
}

int doesCharQueueHaveMultiLineCommentClosing(void) {
	return charQueue[0] == '*' && charQueue[1] == '/';
}

void closeMultiLineComment(void) {
	if (isMultiLineComment) {
		isMultiLineComment = 0;
		charQueue[0] = '\0';
		charQueue[1] = '\0';
	}
}

int doesCharQueueHaveCharLiteral(void) {
	return charQueue[0] != '\\'
			&& charQueue[1] == '\''
			&& (charQueue[3] == '\''
				|| (charQueue[2] == '\\' && charQueue[4] == '\''));
}

void openCharLiteral(void) {
	if (!isComment()) isCharLiteral = 1;
}

int doesCharQueueHaveDoubleQuotes(void) {
	return charQueue[0] != '\\' && charQueue[1] == '"';
}

void openOrCloseStringLiteral(void) {
	isStringLiteral =
		isStringLiteral
		|| isComment() ? 0 : 1;
}

void checkCharQueue(void) {
	if (isCharLiteral) {
		if (charQueue[2] == '\'') isCharLiteral = 0;
	}
	else if (doesCharQueueHaveSingleLineCommentOpening()) openSingleLineComment();
	else if (doesCharQueueHaveMultiLineCommentOpening()) openMultiLineComment();
	else if (doesCharQueueHaveMultiLineCommentClosing()) closeMultiLineComment();
	else if (doesCharQueueHaveCharLiteral()) openCharLiteral();
	else if (doesCharQueueHaveDoubleQuotes()) openOrCloseStringLiteral();

	if (isComment()) currentLineHasComment = 1;
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