#include <stdio.h>
#include <limits.h>

unsigned char computeMaxUnsignedChar();
signed char computeMinSignedChar();
signed char computeMaxSignedChar();

unsigned short computeMaxUnsignedShort();
signed short computeMinSignedShort();
signed short computeMaxSignedShort();

unsigned int computeMaxUnsignedInt();
signed int computeMinSignedInt();
signed int computeMaxSignedInt();

unsigned long computeMaxUnsignedLong();
signed long computeMinSignedLong();
signed long computeMaxSignedLong();

int main() {

	printf("\nHeader Ranges\n\n");

	printf("char\n");
	printf("unsigned: [%u, %u]\n", 0, UCHAR_MAX);
	printf("signed: [%d, %d]\n\n", SCHAR_MIN, SCHAR_MAX);

	printf("short\n");
	printf("unsigned: [%u, %u]\n", 0, USHRT_MAX);
	printf("signed: [%d, %d]\n\n", SHRT_MIN, SHRT_MAX);

	printf("int\n");
	printf("unsigned: [%u, %u]\n", 0, UINT_MAX);
	printf("signed: [%d, %d]\n\n", INT_MIN, INT_MAX);

	printf("long\n");
	printf("unsigned: [%d, %lu]\n", 0, ULONG_MAX);
	printf("signed: [%ld, %ld]\n\n", LONG_MIN, LONG_MAX);

	// Will assume 2's complement machine
	printf("Computed Ranges\n\n");

	printf("char\n");
	printf("unsigned: [%u, %u]\n", 0, computeMaxUnsignedChar());
	printf("signed: [%d, %d]\n\n",
			computeMinSignedChar(),
			computeMaxSignedChar());

	printf("short\n");
	printf("unsigned: [%u, %u]\n", 0, computeMaxUnsignedShort());
	printf("signed: [%d, %d]\n\n",
			computeMinSignedShort(),
			computeMaxSignedShort());

	printf("int\n");
	printf("unsigned: [%u, %u]\n", 0, computeMaxUnsignedInt());
	printf("signed: [%d, %d]\n\n",
			computeMinSignedInt(),
			computeMaxSignedInt());

	printf("long\n");
	printf("unsigned: [%u, %lu]\n", 0, computeMaxUnsignedLong());
	printf("signed: [%ld, %ld]\n\n",
			computeMinSignedLong(),
			computeMaxSignedLong());

}

unsigned char computeMaxUnsignedChar() {
	return ~0;
}
signed char computeMinSignedChar() {
	return computeMaxSignedChar() * -1 - 1;
}
signed char computeMaxSignedChar() {
	return computeMaxUnsignedChar()/2;
}


unsigned short computeMaxUnsignedShort() {
	return ~0;
}
signed short computeMinSignedShort() {
	return computeMaxSignedShort() * -1 - 1;
}
signed short computeMaxSignedShort() {
	return computeMaxUnsignedShort()/2;
}


unsigned int computeMaxUnsignedInt() {
	return ~0;
}
signed int computeMinSignedInt() {
	return computeMaxSignedInt() * -1 - 1;
}
signed int computeMaxSignedInt() {
	return computeMaxUnsignedInt()/2;
}

unsigned long computeMaxUnsignedLong() {
	return ~0;
}
signed long computeMinSignedLong() {
	return computeMaxSignedLong() * -1 - 1;
}
signed long computeMaxSignedLong() {
	return computeMaxUnsignedLong()/2;
}
