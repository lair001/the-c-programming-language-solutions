#include <stdio.h>

#define MAX_PAREN_LEVEL 127
#define MAX_BRACKET_LEVEL 127
#define MAX_BRACE_LEVEL 127

char charQueue[5];
int isCharLiteral = 0;
int isInsideDoubleQuotes = 0;
int isInsideSingleLineComment = 0;
int isInsideMultiLineComment = 0;
int currentLineNumber = 1;

/* Index 0 contains the length of the list.
 * The rest contain the line numbers of open parentheses
 * that have not been closed. */
int openParen[MAX_PAREN_LEVEL + 1];

/* Index 0 contains the length of the list.
 * The rest contain the line numbers of open brackets
 * that have not been closed. */
int openBracket[MAX_BRACKET_LEVEL + 1];

/* Index 0 contains the length of the list.
 * The rest contain the line numbers of open braces
 * that have not been closed. */
int openBrace[MAX_BRACE_LEVEL + 1];

int processChar(int c);
int charQueueHasNonNullChar(void);
int flushCharQueue(void);
void clearLists(void);
int checkCharQueueForParenBraceOrBracket(void);
int isInsideComment(void);
void enqueueInCharQueue(int c);
void clearCharQueue(void);
int checkCharQueue(void);
int pushCurrentLineNumberOn(int lineNumList[]);
int whenMaxLevelExceeded(char type[], int maxLevel);
int whenMatchedClosing(int lineNumList[]);
int whenUnmatchedClosing(char type[]);
int whenUnmatchedOpening(char type[], int lineNum);
int checkUnmatchedOpenings(void);
int handleOpening(char type[], int lineNumList[], int maxLevel);
int handleClosing(char type[], int lineNumList[]);
int checkCharQueueForParenBraceOrBracket(void);

int main() {
	int c, hasError = 0;

	clearLists();
	clearCharQueue();

	while ((c = getchar()) != EOF) {
		if (c == '\n') {
			if ((hasError = flushCharQueue()) != 0) return hasError;
			isInsideSingleLineComment = 0;
			isCharLiteral = 0;
			++currentLineNumber;
		} else {
			if ((hasError = processChar(c)) != 0) return hasError;
		}
	}

	if ((hasError = flushCharQueue()) != 0) return hasError;
	checkUnmatchedOpenings();

	return hasError;
}

int processChar(int c) {
	enqueueInCharQueue(c);
	return checkCharQueue();
}

int charQueueHasNonNullChar(void) {
	for (int i = 0; i < 5; i++) if (charQueue[i] != '\0') return 1;
	return 0;
}

int flushCharQueue(void) {
	int hasError = 0;
	while(charQueueHasNonNullChar()) {
		if ((hasError = processChar('\0')) != 0) return hasError;
	};
	return hasError;
}

void clearLists(void) {
	for (int i = 0; i < MAX_PAREN_LEVEL + 1; ++i) openParen[i] = 0;
	for (int i = 0; i < MAX_BRACKET_LEVEL + 1; ++i) openBracket[i] = 0;
	for (int i = 0; i < MAX_BRACE_LEVEL + 1; ++i) openBrace[i] = 0;
}

int isInsideComment(void) {
	return isInsideSingleLineComment || isInsideMultiLineComment;
}

void enqueueInCharQueue(int c) {
	charQueue[0] = charQueue[1];
	charQueue[1] = charQueue[2];
	charQueue[2] = charQueue[3];
	charQueue[3] = charQueue[4];
	charQueue[4] = c;
}

void clearCharQueue(void) {
	charQueue[0] = '\0';
	charQueue[1] = '\0';
	charQueue[2] = '\0';
	charQueue[3] = '\0';
	charQueue[4] = '\0';
}

int checkCharQueue(void) {
	int hasError = 0;

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
				clearCharQueue();
				isInsideMultiLineComment = 0;
			}
		}
	}
	else if (charQueue[0] != '\\') {
		if (charQueue[1] == '\'') {
			if (charQueue[3] == '\''
					|| (charQueue[2] == '\\' && charQueue[4] == '\'')) isCharLiteral = 1;
		}
		else if (charQueue[1] == '"') {
			isInsideDoubleQuotes =
				isInsideDoubleQuotes
				|| isInsideComment() ? 0 : 1;
		}
		else if (!isInsideDoubleQuotes && !isInsideComment()) {
			hasError = checkCharQueueForParenBraceOrBracket();
		}
	}
	return hasError;
}

int pushCurrentLineNumberOn(int lineNumList[]) {
	++lineNumList[0];
	lineNumList[lineNumList[0]] = currentLineNumber;
	return 0;
}

int whenMaxLevelExceeded(char type[], int maxLevel) {
	printf(
		"Critical Error: Program has more than %d levels of nested %s.\n",
		maxLevel,
		type
	);
	return 2;
}

int whenMatchedClosing(int lineNumList[]) {
	--lineNumList[0];
	return 0;
}

int whenUnmatchedClosing(char type[]) {
	printf(
		"Unmatched closing %s on line %d.\n",
		type,
		currentLineNumber
	);
	return 0;
}

int whenUnmatchedOpening(char type[], int lineNum) {
	printf(
		"Unmatched opening %s on line %d.\n",
		type,
		lineNum
	);
	return 0;
}

int checkUnmatchedOpenings(void) {
	for (int i = 1; i <= openParen[0]; ++i) whenUnmatchedOpening("parenthesis", openParen[i]);
	for (int i = 1; i <= openBrace[0]; ++i) whenUnmatchedOpening("brace", openBrace[i]);
	for (int i = 1; i <= openBracket[0]; ++i) whenUnmatchedOpening("bracket", openBracket[i]);
}

int handleOpening(char type[], int lineNumList[], int maxLevel) {
	if (lineNumList[0] < maxLevel) {
		return pushCurrentLineNumberOn(lineNumList);
	} else {
		return whenMaxLevelExceeded(
			type,
			maxLevel
		);
	}
}

int handleClosing(char type[], int lineNumList[]) {
	if (lineNumList[0] > 0) {
		return whenMatchedClosing(lineNumList);
	} else {
		return whenUnmatchedClosing(type);
	}
}

int checkCharQueueForParenBraceOrBracket(void) {
	switch(charQueue[1]) {
		case '(':
			return handleOpening("parentheses", openParen, MAX_PAREN_LEVEL);
		case '{':
			return handleOpening("braces", openBrace, MAX_BRACE_LEVEL);
		case '[':
			return handleOpening("brackets", openBracket, MAX_BRACKET_LEVEL);
		case ')':
			return handleClosing("parenthesis", openParen);
		case '}':
			return handleClosing("brace", openBrace);
		case ']':
			return handleClosing("bracket", openBracket);
		default:
			return 0;
	}
}