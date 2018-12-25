#include <stdio.h>

float df_to_dc(float fahr) {
	return (5.0/9.0) * (fahr-32.0);
}

int main()
{
	int lower = 0, upper = 300, step = 20;
	float fahr = lower;

	while (fahr <= upper) {
		printf("%3.0f %6.1f\n", fahr, df_to_dc(fahr));
		fahr += step;
	}

	return 0;
}
