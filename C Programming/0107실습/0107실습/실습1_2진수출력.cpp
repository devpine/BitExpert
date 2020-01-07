#include "main.h"

void main()
{
	int num;
	int count = 0;
	unsigned int check_bit;

	check_bit = 0x80000000;
	scanf_s("%d", &num);
	
	while (count < 32)
	{
		printf("%d", check_bit & num ? 1 : 0);
		check_bit >>= 1;
		count++;	
	}
	
}