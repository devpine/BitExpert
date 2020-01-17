#include "main.h"

void main()
{
	double result;
	int i;
	cout << "수식을 입력해주세요 :";
	cin >> expr;

	postfix(expr, post_expr);

	//출력

	for (i = 0; post_expr[i] != '\0'; i++)
	{
		cout << post_expr[i];
	}
	cout << endl;

	result = eval(post_expr);
	cout << expr<<" = " << result << endl;
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
		cout << "수식 입력 에러" << endl;
		exit(1);
	}
	return pop();
}


//중위표기법을 후위표기법으로 변환 시키는 함수/////////////
void postfix(char* str, char* post_expr)
{
	int i = 0, j = 0, flag = 0, count = 0;
	precedence token;

	init_stack(); //스택 초기화
	push(eos);    //우선순위가 가장 낮은 '\0'를 삽입
	while ((token = get_token(str + i)) != eos) // str이 널값이면 변환 중지
	{
		if (token == operand) // operand이면 post_expr에 바로 삽입
		{
			if (count && count % 2)
			{
				*(post_expr + j++) = '-';
				count = 0;
			}
			*(post_expr + j++) = *(str + i);
			flag = 1;     //operand가 실행 되었다는것을 표시
		}
		else if (token == lparen && count % 2)

		{
			strncat(post_expr + j, "0 ", 2);  //operand 뒤에 공백 삽입
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
				*(post_expr + j++) = ' ';
				flag = 0;
			}
			if (token == rparen) // token이 ')'이면 '('이 나올때까지 post_expr에 삽입
			{
				while ((token = precedence((int)pop())) != lparen)
				{
					*(post_expr + j++) = ' ';
					*(post_expr + j++) = print_token(token);
					*(post_expr + j++) = ' ';
				}
			}

			else
			{   // token값이 stack[top]값보다 우선순위가 높을때까지 post_expr에 삽입
				while (icp[token] <= isp[(int)stack[top]])
				{
					*(post_expr + j++) = ' ';
					*(post_expr + j++) = print_token(precedence((int)pop()));
					*(post_expr + j++) = ' ';
				}
				push(token); //마지막에 token값을 푸쉬
			}
		}
		i++;
	}
	*(post_expr + j++) = ' ';  //operand와 구분 시켜 주기위해 공백 삽입 
	while ((token = precedence((int)pop())) != eos)   //스택에 남은 값들을 post_expr에 삽입
		*(post_expr + j++) = print_token(token);
	*(post_expr + j) = '\0'; //post_expr 맨마지막에 null 삽입
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
		cout << "스택이 다 차있습니다." << endl;
		exit(2);
	}
	stack[++top] = in;
}

double pop(void)
{
	if (top < 0)
	{
		cout << "스택이 비어있습니다." << endl;
		exit(3);
	}
	return stack[top--];
}