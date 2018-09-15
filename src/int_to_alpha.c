#include <stdio.h>
#include <stdlib.h>
#include "int_to_alpha.h"

char* int_to_alpha(int num)
{
	int size = 1;
	int loop = 0;

	while(num/size > 9 || num/size < -9)
		size *= 10;

	char* tab = malloc(sizeof(char) * loop + 1);
	if(tab == NULL)
		return NULL;


	while (size >= 1)
	{
		if (num >= 0)
			tab[loop] = ('0' + (num / size) % 10);
		else
		{
			tab[0] = '-';
			tab[loop + 1] = ('0' - (num / size) % 10);
		}
		size /= 10;
		++loop;
	}

	tab[loop] = '\0';

	return tab;
}
