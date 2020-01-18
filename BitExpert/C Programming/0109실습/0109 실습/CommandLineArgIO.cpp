#include<stdio.h>
#include<string.h>
#pragma warning(disable:4996)

int main(int argc, char* argv[]) {
	FILE *fp;
	FILE* fp2;
	char ch;
	/*
	argc == 1, 프로그램을 그냥 실행했을때.
	입력한 내용을 그대로 출력해줌.
	^Z로 빠져나옴.
	*/
	if (argc == 1) {
		ch = getchar();
		while (ch != EOF) {
			putchar(ch);
			ch = getchar();
		}
	}
	/*
	argc == 2, 프로그램 이름(argv[0]) argv[1] 일때
	argv[1]에 있는 파일 내용을 읽어온다(r)
	^Z로 빠져나옴.
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
	argc == 3, 프로그램 이름(argv[0]) argv[1] argv[2] 일때
	argv[1]이 @면 뒤에 있는 argv[2]의 이름으로 파일 생성, 입력한 내용을 저장한다.
	@가 없으면 argv[1]의 내용을 argv[2]에 저장함
	^Z로 빠져나옴.
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