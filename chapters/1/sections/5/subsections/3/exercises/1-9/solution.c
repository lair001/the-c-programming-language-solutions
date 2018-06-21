#include <stdio.h>

int main()
{
	int c, lc_blank;

	lc_blank = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ' && lc_blank == 1)
			continue;
		putchar(c);
		lc_blank = c == ' ';
	}

	return 0;
}
