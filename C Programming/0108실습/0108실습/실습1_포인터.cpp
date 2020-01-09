#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define NUM 1
#define CHARCT 2

int numcmp(const char *, const char *); // 함수 numcmp 선언, 전부 숫자면 numcmp실행
void fcmp(int (**)(const char *,const char *),const char *,const char *);



int main()
{
	char s[80], t[80];
	int (*ptr)(const char *, const char *); // 변수 ptr 선언
	int i = 0;

	while ((s[i++] = getchar()) != '\n');
	s[--i] = '\0';
	i = 0;
	while ((t[i++] = getchar()) != '\n');
	t[--i] = '\0';

	fcmp(&ptr, s, t); 
	printf("%d\n", ptr(s, t));
	//printf("%d\n", (*ptr)(s, t));
	return 0;
}

int numcmp(const char *ps, const char *pt)
{
	float a, b;

	a = atof(ps);
	b = atof(pt);

	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else
		return 0;
}

void fcmp(int (**pstr)(const char *pss, const char *ptt), const char *ps, const char *pt)
{
	/*int count = 0;
	int len = strlen(ps) > strlen(pt) ? strlen(ps) : strlen(pt);

	while (count < len)
	{
		if (ps[count] != '\0')
		{
			if (ps[count] >= '-' && ps[count] <= '9' && ps[count]!='/')
			{
				if (pt[count] >= '-' && pt[count] <= '9' && pt[count] != '/')
					*pstr = numcmp;			
			}
			else
				*pstr = strcmp;
		}
		count++;
	}*/
	int cond;

	cond = NUM;

	if (*ps == '-')
		ps++;
	while (cond == NUM && *ps != NULL)
		if (isdigit(*ps) || *ps == '.')
			ps++;
		else
			cond = CHARCT;

	if (*pt == '-')
		pt++;
	while (cond == NUM && *pt != NULL)
		if (isdigit(*pt) || *pt == '.')
			pt++;
		else
			cond = CHARCT;

	if (cond == NUM)
		*pstr = numcmp;
	else
		*pstr = strcmp;
}
