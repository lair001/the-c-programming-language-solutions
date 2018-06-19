#include <stdio.h>

/* print Celsius-Fahrenheit table
	for celsius = 0, 20, ..., 300; floating point version */

int main()
{
	float celsius, fahr;
	int lower, upper, step;

	lower = -20; /* lower limit of temperature table */
	upper = 150; /* upper limit */
	step = 10; /* step size */

	celsius = lower;
	printf("celsius  fahr\n");
	while (celsius <= upper) {
		fahr = (9.0/5.0) * celsius + 32.0;
		printf("%7.0f  %4.1f\n", celsius, fahr);
		celsius = celsius + step;
	}
	return 0;
}
