#include "main.h"

void main()
{
	int num;
	unsigned int check_bit;
	int i;

	check_bit = 0x80000000;
	scanf_s("%d", &num);
	

	for (i=32; i>=0; i--)
	{
		check_bit = 1 << i;
		if (num&check_bit)
			printf("1");
		else
			printf("0");
	}
	
}