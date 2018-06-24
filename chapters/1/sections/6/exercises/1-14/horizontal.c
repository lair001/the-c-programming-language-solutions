#include <stdio.h>

#define FIRST 33
#define LAST  126

int main()
{

	int c, frqs[LAST - FIRST + 1];

	for (int i = 0; i <= LAST - FIRST; i++) {
		frqs[i] = 0;
	}
	
	while((c = getchar()) != EOF) {
		if (c >= FIRST && c <= LAST) {
			++frqs[c - FIRST];
		}
	}

	for (int i = 0; i <= LAST - FIRST; i++) {
		putchar(i + FIRST);
		printf(" | ");
		for (int j = 0; j < frqs[i]; j++) printf("*");
		printf("\n");
	}

	return 0;
}
