#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
�ǽ�)�־��� ���ڿ����� �� �ٸ� �־��� ���ڸ� �����ϰ� �������Ŀ� ����ȭ��Ų ���ڿ��� ����� �ִ� �Լ� revequeeze(str,c)�� ����ÿ�
-main���� char *result, str[80];
-�Է���
while((str[i++]=getchar())!='\n'); //;�� ���鹮��(null) \n�� �ƴϸ� �ٽ� �Է¹ް� \n�̸� �������ͼ� (\n���������� �Է¹ޱ�)
str[--i)='\0';   //���� \0�� �ִ´�
c=getchar();
-call�� result=revsqueeze(str,c);
-����� printf("%s",result);

-�Լ�����
malloc ����ؼ� ������ڿ��� ������ų��
�ݵ�� ������ ����Ұ�
-char *temp;
len = strlen(pstr);   //strlen()-> <string.h)
temp=(char *)malloc(len+1);   //malloc-><stdlib.h>
*/

char* revequeeze(char*, char);

int main()
{
	char* result, str[80];
	char c;
	int i = 0;
	while ((str[i++] = getchar()) != '\n');
	str[--i] = '\0';
	c = getchar();

	result = revequeeze(str, c);


	printf("%s", result);
}

//�ǽ� ��� - ������ ���ÿ� �������� ����
char* revequeeze(char* pstr, char c)
{
	char* temp;
	int len = 0;
	int i, count = 0;
	len = strlen(pstr);
	temp = (char*)malloc(len + 1);

	while (len > 0)
	{
		for (i = 0; i < strlen(pstr); i++)
		{
			if ((*(pstr + (len - 1))) != c)
			{
				*(temp + i) = (*(pstr + (len - 1)));
				len--;
			}
			else
			{
				i--;
				len--;
				count++;
			}
		}
	}
	*(temp + strlen(pstr) - count) = '\0';
	return temp;
}