#include "common.h"

void convertToLowerCase(char target[], char source[], int n)
{
	const unsigned base = 'a' - 'A';
	unsigned i = 0;

	for (i = 0; i < n; ++i) {
		if (source[i] >= 'A' && source[i] <= 'Z') {
			target[i] = source[i] + base;
		}
	}
}
