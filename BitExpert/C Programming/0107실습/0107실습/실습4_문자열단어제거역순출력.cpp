#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
실습)주어진 문자열에서 또 다른 주어진 문자를 제거하고 압축한후에 역순화시킨 문자열을 만들어 주는 함수 revequeeze(str,c)를 만드시오
-main에서 char *result, str[80];
-입력은
while((str[i++]=getchar())!='\n'); //;는 공백문자(null) \n이 아니면 다시 입력받고 \n이면 빠져나와서 (\n받을때까지 입력받기)
str[--i)='\0';   //공백 \0을 넣는다
c=getchar();
-call은 result=revsqueeze(str,c);
-출력은 printf("%s",result);

-함수에서
malloc 사용해서 결과문자열을 생성시킬것
반드시 포인터 사용할것
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

//실습 방법 - 삭제와 동시에 역순으로 저장
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