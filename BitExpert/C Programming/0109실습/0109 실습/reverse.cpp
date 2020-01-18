#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

/*
frev test1.txt test2.txt
*/
void main(int argc, char* argv[])
{
	FILE *fp;
	FILE *fp2;
	char ch;
	int last,count;

	if (argc = !3)
	{
		fprintf(stderr, "error\n");
		exit(1);
	}
	else
	{
		fp = fopen(argv[1], "w+");
		
		ch = getchar();
		while (ch != EOF) {
			putc(ch,fp);
			ch = getchar();
		}
		fclose(fp);

		fp = fopen(argv[1], "r");
		fp2 = fopen(argv[2], "w+");
		fseek(fp, 1L, SEEK_END);
		
		last = ftell(fp);


		for (count = 1L; count <= last; count++)
		{
			ch = getc(fp);
			if (ch != EOF)
			{
				putc(ch, fp2);
			}
			if (ch == '\n')
				fseek(fp, -3L, SEEK_CUR);
			else
				fseek(fp, -count, SEEK_END);
			
			
		}
		fclose(fp);
		fclose(fp2);
	}
	
}