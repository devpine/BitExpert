#pragma warning(disable:4996)
#include<iostream>

#define MAX 100
using std::cout;
using std::cin;
using std::endl;

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, space, operand } precedence;

char expr[MAX];
char post_expr[MAX];  //후위표기 저장

template <typename T>
class Stack {
private:
	T *stack;
	int top;
public:
	void push(const T& in);
	double pop();
	T peek();
	Stack() {
		stack = new T[MAX];
		top = -1;
	}
};

template <typename T>
void Stack<T>::push(const T& in)
{
	if (top >= MAX - 1)
	{
		cout << "Stack is Full" << endl;
		exit(2);
	}
	stack[++top] = in;
}

template <typename T>
double Stack<T>::pop()
{
	if (top < 0)
	{
		cout << "Stack is Empty" << endl;
		exit(3);
	}
	return stack[top--];
}

// 스택의 값을 가져오는 함수
template <typename T>
T Stack<T>::peek() {
	if (top == -1)
	{
		cout << "Stack is Empty" << endl;
		exit(3);
	}
	else {
		return stack[top];
	}
}

template <typename T>
class Token {
private:
	int isp[11] = { 0, 19, 12, 12, 13, 13, 13, 0, 0, 0, 0 };  //스택에 있는 값의 우선순위
	int icp[11] = { 20, 19, 12, 12, 13, 13, 13, 0, 20, 20, 20 }; //스택에 들어가는 값의 우선순위

public:
	precedence get_token(char* symbol);
	char print_token(precedence token);
	int get_isp(int idx);
	int get_icp(int idx);
	Token() {
	}
};

//precedence형태의 값 리턴
template <typename T>
precedence Token<T>::get_token(char* symbol)
{
	//oper에 맞는 연산자 반환
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

//precedence의값으로 문자 리턴
template <typename T>
char Token<T>::print_token(precedence token)
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

// isp 우선순위 값 가져오기
template <typename T>
int  Token<T>::get_isp(int idx) {
	return isp[idx];
}


// icp 우선순위 값 가져오기
template <typename T>
int  Token<T>::get_icp(int idx) {
	return icp[idx];
}


//중위표기법-> 후위표기법 변환
void postfix(char* str, char* post_expr)
{
	int i = 0, j = 0, count = 0;

	bool flag = false;//operand 실행 유무
	precedence token;
	
	// 스택과 토큰 객체 생성
	Stack<double> stack1 = Stack<double>();
	Token<double> token1 = Token<double>();

	//우선순위 가장 낮은 '\0'를 삽입
	stack1.push(eos);

	while ((token = token1.get_token(str + i)) != eos) // str이 null이면 변환 중지
	{
		if (token == operand) // token이 operand이면 post_expr에 바로 삽입
		{
			if (count && count % 2)
			{
				*(post_expr + j++) = '-';
				count = 0;
			}
			*(post_expr + j++) = *(str + i);
			flag = true;     
		}
		else if (token == lparen && count % 2)

		{
			strncat(post_expr + j, "0 ", 2);  //operand 뒤에 공백 삽입
			j += 2;
			// 스택에 값을 넣기
			stack1.push(minus);
			stack1.push(token);
			count = 0;
		}

		//token이 '-' 일때 음수인지 부호인지 판단
		else if (token == minus && !flag && token1.get_token(str + i - 1) != rparen)
			count++;
		else
		{
			if (flag) //operand와 구분 시켜 주기위해 공백 삽입, flag가 true이면 operand가 삽입 된것
			{
				*(post_expr + j++) = ' ';
				flag = false;
			}
			if (token == rparen) // token이 ')'일때 '('이 나올때까지 post_expr에 삽입
			{
				while ((token = precedence((int)stack1.pop())) != lparen)
				{
					*(post_expr + j++) = ' ';
					*(post_expr + j++) = token1.print_token(token);
					*(post_expr + j++) = ' ';
				}
			}

			else
			{   // token값이 stack[top]값보다 우선순위 높을때까지 post_expr에 삽입
				while (token1.get_icp(token) <= token1.get_isp((int)stack1.peek()))
				{
					*(post_expr + j++) = ' ';
					*(post_expr + j++) = token1.print_token(precedence((int)stack1.pop()));
					*(post_expr + j++) = ' ';
				}
				stack1.push(token); //마지막에 token값 푸쉬
			}
		}
		i++;
	}
	*(post_expr + j++) = ' ';  //operand와 구분 시켜 주기위해 공백 삽입 
	while ((token = precedence((int)stack1.pop())) != eos)   //스택에 남은 값들을 post_expr에 삽입
		*(post_expr + j++) = token1.print_token(token);
	*(post_expr + j) = '\0'; //post_expr 맨마지막에 null 삽입
}

//후위 표기법으로 변환된 수식으로 값 계산
double eval(char* post)
{
	char t[MAX];
	precedence token;
	double temp;
	int i = 0, j = 0, cnt_operand = 0, cnt_operator = 0;

	Stack<double> stack1 = Stack<double>();
	Token<int> token1 = Token<int>();

	while ((token = token1.get_token(post)) != eos)
	{
		if (token == space && i > 0) //'\0'을 만나면 token을 실수로 변환
		{
			t[i] = '\0';
			// 문자열을 실수로 변환
			temp = atof(t);
			stack1.push(temp);
			cnt_operand++;
			i = 0;
		}
		//문자가 아니고 operand이거나 '-'이면서 다음에 operand이면 실행
		else if ((!isalpha(*post) && operand == token) || (token == minus && token1.get_token(post + 1) == operand))
			t[i++] = *post;

		else   //operator이면 switch문 실행
		{
			if (!(token >= eos && token <= operand) && !isalpha(*post) && token != lparen)
				cnt_operator++;
			// 기호에 맞게 연산
			switch (token)
			{
			case plus: stack1.push(stack1.pop() + stack1.pop());
				break;
			case minus: temp = stack1.pop();
				stack1.push(stack1.pop() - temp);
				break;
			case times: stack1.push(stack1.pop() * stack1.pop());
				break;
			case divide: if ((temp = stack1.pop()) != 0)
				stack1.push(stack1.pop() / temp);
				break;
			case mod: temp = stack1.pop();
				stack1.push((int)stack1.pop() % (int)temp);
				break;
			}
		}
		post++;
	}

	if (cnt_operand - cnt_operator != 1)
	{
		cout << "Formula error" << endl;
		exit(1);
	}
	return stack1.pop();
}

void main() {
	double result;
	int i;
	cout << "Input Infix :";
	cin >> expr;

	postfix(expr, post_expr);
	cout << "Postfix : ";
	for (i = 0; post_expr[i] != '\0'; i++)
	{
		cout << post_expr[i];
	}
	cout << endl;

	result = eval(post_expr);
	cout << "Result : "<< expr << " = " << result << endl;
	system("pause");
}