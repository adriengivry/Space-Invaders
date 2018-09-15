#include "string_concatenate.h"

char* string_concatenate(const char* src1, const char* src2)
{
	unsigned int lengthNeeded = string_length(src1) + string_length(src2) + 1;
	char* dest = malloc(sizeof(char) * lengthNeeded);

	int i = 0;
	int j = 0;

	while (i < string_length(src1))
	{
		dest[i] = src1[i];
		++i;
	}

	while (j < string_length(src2))
	{
		dest[i + j] = src2[j];
		++j;
	}

	dest[i + j] = '\0';

	return dest;
}