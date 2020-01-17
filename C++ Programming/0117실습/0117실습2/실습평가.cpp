#include "main.h"

void main()
{
	double result;
	int i;
	cout << "������ �Է����ּ��� :";
	cin >> expr;

	postfix(expr, post_expr);

	//���

	for (i = 0; post_expr[i] != '\0'; i++)
	{
		cout << post_expr[i];
	}
	cout << endl;

	result = eval(post_expr);
	cout << expr<<" = " << result << endl;
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
			if (!(token >= eos && token <= operand) && !isalpha(*post) && token != lparen)
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
		cout << "���� �Է� ����" << endl;
		exit(1);
	}
	return pop();
}


//����ǥ����� ����ǥ������� ��ȯ ��Ű�� �Լ�/////////////
void postfix(char* str, char* post_expr)
{
	int i = 0, j = 0, flag = 0, count = 0;
	precedence token;

	init_stack(); //���� �ʱ�ȭ
	push(eos);    //�켱������ ���� ���� '\0'�� ����
	while ((token = get_token(str + i)) != eos) // str�� �ΰ��̸� ��ȯ ����
	{
		if (token == operand) // operand�̸� post_expr�� �ٷ� ����
		{
			if (count && count % 2)
			{
				*(post_expr + j++) = '-';
				count = 0;
			}
			*(post_expr + j++) = *(str + i);
			flag = 1;     //operand�� ���� �Ǿ��ٴ°��� ǥ��
		}
		else if (token == lparen && count % 2)

		{
			strncat(post_expr + j, "0 ", 2);  //operand �ڿ� ���� ����
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
				*(post_expr + j++) = ' ';
				flag = 0;
			}
			if (token == rparen) // token�� ')'�̸� '('�� ���ö����� post_expr�� ����
			{
				while ((token = precedence((int)pop())) != lparen)
				{
					*(post_expr + j++) = ' ';
					*(post_expr + j++) = print_token(token);
					*(post_expr + j++) = ' ';
				}
			}

			else
			{   // token���� stack[top]������ �켱������ ���������� post_expr�� ����
				while (icp[token] <= isp[(int)stack[top]])
				{
					*(post_expr + j++) = ' ';
					*(post_expr + j++) = print_token(precedence((int)pop()));
					*(post_expr + j++) = ' ';
				}
				push(token); //�������� token���� Ǫ��
			}
		}
		i++;
	}
	*(post_expr + j++) = ' ';  //operand�� ���� ���� �ֱ����� ���� ���� 
	while ((token = precedence((int)pop())) != eos)   //���ÿ� ���� ������ post_expr�� ����
		*(post_expr + j++) = print_token(token);
	*(post_expr + j) = '\0'; //post_expr �Ǹ������� null ����
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
	default: return '\0';
	}
}

void init_stack(void)
{
	top = -1;
}

void push(double in)
{
	if (top >= MAX - 1)
	{
		cout << "������ �� ���ֽ��ϴ�." << endl;
		exit(2);
	}
	stack[++top] = in;
}

double pop(void)
{
	if (top < 0)
	{
		cout << "������ ����ֽ��ϴ�." << endl;
		exit(3);
	}
	return stack[top--];
}