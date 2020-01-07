#include "main.h"

#include <stdio.h>

int main()
{
	int num, n, i;
	int count = 0;
	unsigned int check_bit = 0x80000000;

	scanf_s("%d %d", &num, &n);

	while (count < 32)
	{
		printf("%d", check_bit & num ? 1 : 0);
		check_bit >>= 1;
		count++;
	}

	printf("\n");
	check_bit = 0x80000000;

	for (i = 0; i < n; i++)
	{
		if (check_bit & num)
		{
			num <<= 1;
			num++;
		}
		else
			num <<= 1;
	}

	check_bit = 0x80000000;
	count = 0;

	while (count < 32)
	{
		printf("%d", check_bit & num ? 1 : 0);
		check_bit >>= 1;
		count++;
	}

	printf("\n");

	return 0;
}