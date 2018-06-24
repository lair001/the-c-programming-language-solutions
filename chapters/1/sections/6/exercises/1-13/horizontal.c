#include <stdio.h>
#include <ctype.h>

#define OUT 0
#define IN  1

int main()
{
	int c, is_space, lengths[10] = {0,0,0,0,0,0,0,0,0,0};
	int cur_len = 0, state = OUT;
	
	while ((c = getchar()) != EOF) {
		is_space = isspace(c);

		if (is_space) {
			state = OUT;
			if (cur_len > 9) {
				++lengths[9];
			} else if (cur_len > 0) {
				++lengths[cur_len - 1];
			}
			cur_len = 0;
		} else if (state == OUT)
			state = IN;

		if (state == IN) ++cur_len;	
	}

	for (int i = 1; i <= 10; i++) {
		i == 10 ? printf(">9") : printf(" %d", i);
		printf(" | ");
		for (int j = 0; j < lengths[i-1]; j++) printf("*");
		printf("\n");
	}

	return 0;
}
