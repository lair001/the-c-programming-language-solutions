#include <stdio.h>
#include <float.h>

int main() {

	printf("\nHeader Ranges\n\n");
	printf("float: [%G, %G]\n", FLT_MIN, FLT_MAX);
	printf("double: [%G, %G]\n", DBL_MIN, DBL_MAX);
	printf("long double: [%LG, %LG]\n\n", LDBL_MIN, LDBL_MAX);

	/* At this time, I am unsure of an accurate and performant
	 * algorithm for computing the min and max values for the
	 * floating point types.  There are solutions floating around
	 * that assume the machine adheres to IEEE 754, with float,
	 * double, and long double corresponding to single, double, and
	 * quadruple precision, respectively.
	 *
	 * I am not sure whether such assumption would hold for a
	 * sufficiently high percentage of machines.  We could try a binary
	 * search approach if appropriate upper and lower bounds and
	 * precision could be identified.  I say just rely on the header
	 * values for this one, though.
	 */
}
