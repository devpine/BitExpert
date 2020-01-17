#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

#define MAX 100

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, Sin, Cos, Tan, space, operand } precedence;

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0, 0, 0, 0 };  //스택에 있는 값의 우선순위
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0, 20, 20, 20 }; //스택에 들어가는 값의 우선순위
double stack[MAX]; //스택을 정의
int top;        //top표인터 정의



//함수원형/////////////////////////////////////////////////////////////////
void change_postfix(char*, char*);
precedence get_token(char*);
char print_token(precedence);
void init_stack(void);
void push(double);
double pop(void);
double eval(char* post);

//Main 함수//////////////////////////////////////////////////////////////////
void main()
{

	char infix[MAX];
	char postfix[MAX] = { 0 };  //후위표기법을 저장하는 배열
	double result;
	int i;
	printf("수식을 입력하여주세요 : ");
	gets_s(infix);

	change_postfix(infix, postfix);

	//출력
	printf("중위표기법 : %s\n", infix);

	for (i = 0; postfix[i] != '\0'; i++)
	{
		if (postfix[i] == '$' || postfix[i] == '@' || postfix[i] == '#')
			printf(")");
		else
			printf("%c", postfix[i]);
	}
	printf("\n");

	result = eval(postfix);
	printf("%s = %f\n", infix, result);
}



//후위 표기법으로 변환된 수식을 이용하여 값을 계산하는 함수//////
double eval(char* post)
{
	char t[MAX];
	precedence token;
	double temp;
	int i = 0, j = 0, cnt_operand = 0, cnt_operator = 0;

	init_stack();  //스택 초기화
	while ((token = get_token(post)) != eos)
	{
		if (token == space && i > 0) //공백을 만나면 token을 실수형으로 변환
		{
			t[i] = '\0';
			temp = atof(t);
			push(temp);
			cnt_operand++;
			i = 0;
		}
		//문자가 아니고 operand이거나 '-'이면서 다음에 operand이면 실행
		else if ((!isalpha(*post) && operand == token) || (token == minus && get_token(post + 1) == operand))
			t[i++] = *post;

		else   //operator이면 switch문 실행
		{
			if (!(token >= Sin && token <= space) && !isalpha(*post) && token != lparen)
				cnt_operator++;
			switch (token)
			{
			case plus: push(pop() + pop());
				break;
			case minus: temp = pop();
				push(pop() - temp);
				break;
			case times: push(pop() * pop());
				break;
			case divide: if ((temp = pop()) != 0)
				push(pop() / temp);
				break;
			case mod: temp = pop();
				push((int)pop() % (int)temp);
				break;
			}
		}
		post++;
	}

	if (cnt_operand - cnt_operator != 1)
	{
		puts("에러!!!!!!!!!!.   수식이 맞지 않습니다.");
		exit(1);
	}
	return pop();
}


//중위표기법을 후위표기법으로 변환 시키는 함수/////////////
void change_postfix(char* str, char* postfix)
{
	int i = 0, j = 0, flag = 0, count = 0, s_c_t;
	precedence token;

	init_stack(); //스택 초기화
	push(eos);    //우선순위가 가장 낮은 '\0'를 삽입
	while ((token = get_token(str + i)) != eos) // str이 널값이면 변환 중지
	{
		if (token == operand) // operand이면 postfix에 바로 삽입
		{
			if (count && count % 2)
			{
				*(postfix + j++) = '-';
				count = 0;
			}
			*(postfix + j++) = *(str + i);
			flag = 1;     //operand가 실행 되었다는것을 표시
		}
		else if (token == lparen && count % 2)

		{
			strncat(postfix + j, "0 ", 2);  //operand 뒤에 공백 삽입
			j += 2;
			push(minus);
			push(token);
			count = 0;
		}

		//음수 판별 조건 : token은 '-' 이고, operand 또는(or)     ')' 바로 뒤에 '-'는 뺄셈 부호임
		//                 따라서 operand가 선행 안되면서(and),   ')'가 이전에 없으면 '-'는 부호 표시 기호이다.
		else if (token == minus && !flag && get_token(str + i - 1) != rparen)
			count++;
		else
		{
			if (flag) //operand와 구분 시켜 주기위해 공백 삽입, flag가 1이면 operand가 삽입 되었단 말임
			{
				*(postfix + j++) = ' ';
				flag = 0;
			}
			if (token == rparen) // token이 ')'이면 '('이 나올때까지 postfix에 삽입
			{
				while ((token = precedence((int)pop())) != lparen && !(token >= Sin && token <= Tan))
				{
					*(postfix + j++) = ' ';
					*(postfix + j++) = print_token(token);
					*(postfix + j++) = ' ';
				}
				if (token != lparen)  //sin => $ , cos => @ , tan => # 기호 삽입
				{
					*(postfix + j++) = print_token(token);
					*(postfix + j++) = ' ';
				}
			}

			else
			{   // token값이 stack[top]값보다 우선순위가 높을때까지 postfix에 삽입
				while (icp[token] <= isp[(int)stack[top]])
				{
					*(postfix + j++) = ' ';
					*(postfix + j++) = print_token(precedence((int)pop()));
					*(postfix + j++) = ' ';
				}
				push(token); //마지막에 token값을 푸쉬
			}
		}
		i++;
	}

	*(postfix + j++) = ' ';  //operand와 구분 시켜 주기위해 공백 삽입 

	while ((token = precedence((int)pop())) != eos)   //스택에 남은 값들을 postfix에 삽입
		*(postfix + j++) = print_token(token);
	*(postfix + j) = '\0'; //postfix 맨마지막에 null 삽입
}


//precedence의 형태의 값을 리턴하는 함수///////////////////////////
precedence get_token(char* symbol)
{
	switch (*symbol)
	{
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '*': return times;
	case '/': return divide;
	case '%': return mod;
	case '\0': return eos;
	case ' ': return space;
	case '$': return Sin;
	case '@': return Cos;
	case '#': return Tan;
	default: return operand;
	}
}

//precedence의값을 입력 받아서 문자를 리턴하는 함수///////
char print_token(precedence token)
{
	switch (token)
	{
	case plus: return '+';
	case minus: return '-';
	case times: return '*';
	case divide: return '/';
	case mod: return '%';
	case Sin: return '$';
	case Cos: return '@';
	case Tan: return '#';
	default: return '\0';
	}
}

//스택 초기화 함수/////////////////////////////////////////////////
void init_stack(void)
{
	top = -1;
}

//스택에 푸쉬 하는 함수////////////////////////////////////////

void push(double in)
{
	if (top >= MAX - 1)
	{
		puts("Stack is Full !!!!!!!!!!!");
		exit(1);
	}
	stack[++top] = in;
}

//스택에서 팝하는 함수///////////////////////////////////////////

double pop(void)
{
	if (top < 0)
	{
		puts("Stack is Empty !!!!!!!!!!!");
		exit(1);
	}
	return stack[top--];
}