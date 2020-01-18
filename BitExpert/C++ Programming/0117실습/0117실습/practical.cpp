#pragma warning(disable:4996)
#include<iostream>

#define MAX 100
using std::cout;
using std::cin;
using std::endl;

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, space, operand } precedence;

char expr[MAX];
char post_expr[MAX];  //����ǥ�� ����

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

// ������ ���� �������� �Լ�
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
	int isp[11] = { 0, 19, 12, 12, 13, 13, 13, 0, 0, 0, 0 };  //���ÿ� �ִ� ���� �켱����
	int icp[11] = { 20, 19, 12, 12, 13, 13, 13, 0, 20, 20, 20 }; //���ÿ� ���� ���� �켱����

public:
	precedence get_token(char* symbol);
	char print_token(precedence token);
	int get_isp(int idx);
	int get_icp(int idx);
	Token() {
	}
};

//precedence������ �� ����
template <typename T>
precedence Token<T>::get_token(char* symbol)
{
	//oper�� �´� ������ ��ȯ
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

//precedence�ǰ����� ���� ����
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

// isp �켱���� �� ��������
template <typename T>
int  Token<T>::get_isp(int idx) {
	return isp[idx];
}


// icp �켱���� �� ��������
template <typename T>
int  Token<T>::get_icp(int idx) {
	return icp[idx];
}


//����ǥ���-> ����ǥ��� ��ȯ
void postfix(char* str, char* post_expr)
{
	int i = 0, j = 0, count = 0;

	bool flag = false;//operand ���� ����
	precedence token;
	
	// ���ð� ��ū ��ü ����
	Stack<double> stack1 = Stack<double>();
	Token<double> token1 = Token<double>();

	//�켱���� ���� ���� '\0'�� ����
	stack1.push(eos);

	while ((token = token1.get_token(str + i)) != eos) // str�� null�̸� ��ȯ ����
	{
		if (token == operand) // token�� operand�̸� post_expr�� �ٷ� ����
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
			strncat(post_expr + j, "0 ", 2);  //operand �ڿ� ���� ����
			j += 2;
			// ���ÿ� ���� �ֱ�
			stack1.push(minus);
			stack1.push(token);
			count = 0;
		}

		//token�� '-' �϶� �������� ��ȣ���� �Ǵ�
		else if (token == minus && !flag && token1.get_token(str + i - 1) != rparen)
			count++;
		else
		{
			if (flag) //operand�� ���� ���� �ֱ����� ���� ����, flag�� true�̸� operand�� ���� �Ȱ�
			{
				*(post_expr + j++) = ' ';
				flag = false;
			}
			if (token == rparen) // token�� ')'�϶� '('�� ���ö����� post_expr�� ����
			{
				while ((token = precedence((int)stack1.pop())) != lparen)
				{
					*(post_expr + j++) = ' ';
					*(post_expr + j++) = token1.print_token(token);
					*(post_expr + j++) = ' ';
				}
			}

			else
			{   // token���� stack[top]������ �켱���� ���������� post_expr�� ����
				while (token1.get_icp(token) <= token1.get_isp((int)stack1.peek()))
				{
					*(post_expr + j++) = ' ';
					*(post_expr + j++) = token1.print_token(precedence((int)stack1.pop()));
					*(post_expr + j++) = ' ';
				}
				stack1.push(token); //�������� token�� Ǫ��
			}
		}
		i++;
	}
	*(post_expr + j++) = ' ';  //operand�� ���� ���� �ֱ����� ���� ���� 
	while ((token = precedence((int)stack1.pop())) != eos)   //���ÿ� ���� ������ post_expr�� ����
		*(post_expr + j++) = token1.print_token(token);
	*(post_expr + j) = '\0'; //post_expr �Ǹ������� null ����
}

//���� ǥ������� ��ȯ�� �������� �� ���
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
		if (token == space && i > 0) //'\0'�� ������ token�� �Ǽ��� ��ȯ
		{
			t[i] = '\0';
			// ���ڿ��� �Ǽ��� ��ȯ
			temp = atof(t);
			stack1.push(temp);
			cnt_operand++;
			i = 0;
		}
		//���ڰ� �ƴϰ� operand�̰ų� '-'�̸鼭 ������ operand�̸� ����
		else if ((!isalpha(*post) && operand == token) || (token == minus && token1.get_token(post + 1) == operand))
			t[i++] = *post;

		else   //operator�̸� switch�� ����
		{
			if (!(token >= eos && token <= operand) && !isalpha(*post) && token != lparen)
				cnt_operator++;
			// ��ȣ�� �°� ����
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