#include <stdio.h>
#include <ctype.h>

#define OUT 0
#define IN  1
#define COLUMNS 18

int main()
{
	int c, is_space, lengths[COLUMNS];
	int cur_len = 0, state = OUT;

	for (int i = 0; i < COLUMNS; ++i) lengths[i] = 0;
	
	while ((c = getchar()) != EOF) {
		is_space = isspace(c);

		if (is_space) {
			state = OUT;
			if (cur_len > COLUMNS - 1) {
				++lengths[COLUMNS - 1];
			} else if (cur_len > 0) {
				++lengths[cur_len - 1];
			}
			cur_len = 0;
		} else if (state == OUT)
			state = IN;

		if (state == IN) ++cur_len;	
	}

	int max_occur = 0;
	for (int i = 0; i < COLUMNS; ++i)
		if (lengths[i] > max_occur) max_occur = lengths[i];

	for (int i = max_occur; i > 0; --i) {
		printf("%4d | ", i % 10000);
		for (int j = 0; j < COLUMNS; j++)
			lengths[j] >= i ? printf("*** ") : printf("    ");
		putchar('\n');
	}

	printf("      ");
	for (int i = 0; i < COLUMNS; i++) printf("‾‾‾‾");
	printf("\n       ");
	for (int i = 1; i < COLUMNS; i++) printf("%3d ", i);
	printf(">%2d \n", COLUMNS - 1);

	return 0;
}
