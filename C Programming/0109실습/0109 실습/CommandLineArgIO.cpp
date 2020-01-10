#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int main(int argc, char* argv[]) {
	FILE *fp;
	FILE* fp2;
	char ch;
	/*
	argc == 1, ���α׷��� �׳� ����������.
	�Է��� ������ �״�� �������.
	^Z�� ��������.
	*/
	if (argc == 1) {
		ch = getchar();
		while (ch != EOF) {
			putchar(ch);
			ch = getchar();
		}
	}
	/*
	argc == 2, ���α׷� �̸�(argv[0]) argv[1] �϶�
	argv[1]�� �ִ� ���� ������ �о�´�(r)
	^Z�� ��������.
	*/
	else if (argc == 2) {            
		fp = fopen(argv[1], "r");
		ch = getc(fp);
		while (ch != EOF)
		{
			putchar(ch);
			ch = getc(fp);
		}

	}
	/*
	argc == 3, ���α׷� �̸�(argv[0]) argv[1] argv[2] �϶�
	argv[1]�� @�� �ڿ� �ִ� argv[2]�� �̸����� ���� ����, �Է��� ������ �����Ѵ�.
	@�� ������ argv[1]�� ������ argv[2]�� ������
	^Z�� ��������.
	*/
	else {
		if (strcmp(argv[1], "@") == 0) {  
			fp = fopen(argv[2], "w+");
			ch = getchar();
			while (ch != EOF) {
				putc(ch, fp);
				ch = getchar();
			}
		}
		else {                    
			fp = fopen(argv[1], "r");
			fp2 = fopen(argv[2], "w+");
			ch = getc(fp);
			while (ch != EOF)
			{
				putc(ch, fp2);
				ch = getc(fp);
			}
		}
	}
}