#include <stdio.h>
#include <ctype.h>

#define IN 1 /* inside a word */
#define OUT 0 /* outside a word */

int main()
{

	int c, is_space;
	int state = OUT;

	while ((c = getchar()) != EOF) {
		is_space = isspace(c);
		if (is_space)
			state = OUT;
		else if (state == OUT) {
			state = IN;
			putchar('\n');
		}
		if (!is_space) putchar(c);
	}
	putchar('\n');

	return 0;
}
