#include "main.h"

char *revsqueeze(char*, char);

void main()
{
	char *result, str[80];
	char c;
	int i=0;

	while (((str[i++] = getchar()) != '\n')); // ;은 NULL. 아무것도 안함.
	str[--i] = '\0';
	c = getchar();

	result = revsqueeze(str, c);

	printf("%s\n",result);
	
}

char *revsqueeze(char* pstr, char c) 
{
	char *temp;
	int len = strlen(pstr);
	int i,j;
	temp = (char *)malloc(len + 1);
	
	for (i = 0; i < len; i++)
	{
		if (*(pstr + i) == c) {
			for (j = i; j < len; j++)
				pstr[j] = pstr[j + 1];
		}
	}

	len = strlen(pstr);
	i = 0;

	while (--len != -1)
	{		
		*(temp + i++) = *(pstr + len);		
	}	

	temp[strlen(pstr)] = '\0';

	return temp;
}