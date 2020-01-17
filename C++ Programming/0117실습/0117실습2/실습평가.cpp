#pragma warning(disable:4996)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<math.h>

#define MAX 100

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, Sin, Cos, Tan, space, operand } precedence;

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0, 0, 0, 0 };  //���ÿ� �ִ� ���� �켱����
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0, 20, 20, 20 }; //���ÿ� ���� ���� �켱����
double stack[MAX]; //������ ����
int top;        //topǥ���� ����



//�Լ�����/////////////////////////////////////////////////////////////////
void change_postfix(char*, char*);
precedence get_token(char*);
char print_token(precedence);
void init_stack(void);
void push(double);
double pop(void);
double eval(char* post);

//Main �Լ�//////////////////////////////////////////////////////////////////
void main()
{

	char infix[MAX];
	char postfix[MAX] = { 0 };  //����ǥ����� �����ϴ� �迭
	double result;
	int i;
	printf("������ �Է��Ͽ��ּ��� : ");
	gets_s(infix);

	change_postfix(infix, postfix);

	//���
	printf("����ǥ��� : %s\n", infix);

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



//���� ǥ������� ��ȯ�� ������ �̿��Ͽ� ���� ����ϴ� �Լ�//////
double eval(char* post)
{
	char t[MAX];
	precedence token;
	double temp;
	int i = 0, j = 0, cnt_operand = 0, cnt_operator = 0;

	init_stack();  //���� �ʱ�ȭ
	while ((token = get_token(post)) != eos)
	{
		if (token == space && i > 0) //������ ������ token�� �Ǽ������� ��ȯ
		{
			t[i] = '\0';
			temp = atof(t);
			push(temp);
			cnt_operand++;
			i = 0;
		}
		//���ڰ� �ƴϰ� operand�̰ų� '-'�̸鼭 ������ operand�̸� ����
		else if ((!isalpha(*post) && operand == token) || (token == minus && get_token(post + 1) == operand))
			t[i++] = *post;

		else   //operator�̸� switch�� ����
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
		puts("����!!!!!!!!!!.   ������ ���� �ʽ��ϴ�.");
		exit(1);
	}
	return pop();
}


//����ǥ����� ����ǥ������� ��ȯ ��Ű�� �Լ�/////////////
void change_postfix(char* str, char* postfix)
{
	int i = 0, j = 0, flag = 0, count = 0, s_c_t;
	precedence token;

	init_stack(); //���� �ʱ�ȭ
	push(eos);    //�켱������ ���� ���� '\0'�� ����
	while ((token = get_token(str + i)) != eos) // str�� �ΰ��̸� ��ȯ ����
	{
		if (token == operand) // operand�̸� postfix�� �ٷ� ����
		{
			if (count && count % 2)
			{
				*(postfix + j++) = '-';
				count = 0;
			}
			*(postfix + j++) = *(str + i);
			flag = 1;     //operand�� ���� �Ǿ��ٴ°��� ǥ��
		}
		else if (token == lparen && count % 2)

		{
			strncat(postfix + j, "0 ", 2);  //operand �ڿ� ���� ����
			j += 2;
			push(minus);
			push(token);
			count = 0;
		}

		//���� �Ǻ� ���� : token�� '-' �̰�, operand �Ǵ�(or)     ')' �ٷ� �ڿ� '-'�� ���� ��ȣ��
		//                 ���� operand�� ���� �ȵǸ鼭(and),   ')'�� ������ ������ '-'�� ��ȣ ǥ�� ��ȣ�̴�.
		else if (token == minus && !flag && get_token(str + i - 1) != rparen)
			count++;
		else
		{
			if (flag) //operand�� ���� ���� �ֱ����� ���� ����, flag�� 1�̸� operand�� ���� �Ǿ��� ����
			{
				*(postfix + j++) = ' ';
				flag = 0;
			}
			if (token == rparen) // token�� ')'�̸� '('�� ���ö����� postfix�� ����
			{
				while ((token = precedence((int)pop())) != lparen && !(token >= Sin && token <= Tan))
				{
					*(postfix + j++) = ' ';
					*(postfix + j++) = print_token(token);
					*(postfix + j++) = ' ';
				}
				if (token != lparen)  //sin => $ , cos => @ , tan => # ��ȣ ����
				{
					*(postfix + j++) = print_token(token);
					*(postfix + j++) = ' ';
				}
			}

			else
			{   // token���� stack[top]������ �켱������ ���������� postfix�� ����
				while (icp[token] <= isp[(int)stack[top]])
				{
					*(postfix + j++) = ' ';
					*(postfix + j++) = print_token(precedence((int)pop()));
					*(postfix + j++) = ' ';
				}
				push(token); //�������� token���� Ǫ��
			}
		}
		i++;
	}

	*(postfix + j++) = ' ';  //operand�� ���� ���� �ֱ����� ���� ���� 

	while ((token = precedence((int)pop())) != eos)   //���ÿ� ���� ������ postfix�� ����
		*(postfix + j++) = print_token(token);
	*(postfix + j) = '\0'; //postfix �Ǹ������� null ����
}


//precedence�� ������ ���� �����ϴ� �Լ�///////////////////////////
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

//precedence�ǰ��� �Է� �޾Ƽ� ���ڸ� �����ϴ� �Լ�///////
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

//���� �ʱ�ȭ �Լ�/////////////////////////////////////////////////
void init_stack(void)
{
	top = -1;
}

//���ÿ� Ǫ�� �ϴ� �Լ�////////////////////////////////////////

void push(double in)
{
	if (top >= MAX - 1)
	{
		puts("Stack is Full !!!!!!!!!!!");
		exit(1);
	}
	stack[++top] = in;
}

//���ÿ��� ���ϴ� �Լ�///////////////////////////////////////////

double pop(void)
{
	if (top < 0)
	{
		puts("Stack is Empty !!!!!!!!!!!");
		exit(1);
	}
	return stack[top--];
}