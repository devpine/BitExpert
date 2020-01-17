#include "0117Test.h"
class Stack {
	precedence *stack;
	int top;
public:
	Stack() {
		stack = new precedence[MAX_STACK_SIZE];
		top = -1;
	}
	precedence *getStack() { return stack; };
	~Stack()
	{
		delete[] stack;
	}

	void add(int *top, precedence item)
	{
		if (!isFull(top))
			exit(1);
		else
			stack[++*top] = item;
	}
	precedence deleteS(int *top)
	{
		if (*top == -1)
			return stack_empty();
		return stack[(*top)--];
	}
};
template<typename T>
class Postfix : Stack{
	int n;
	int top;
	char str;
	T token;
public:
	Postfix()
	{
		n = 0;
		top = 0;
	}
	void postfix()
	{
		getStack()[0] = eos;
		for (token = get_token(&str, &n); token != eos; token = get_token(&str, &n)) {
			if (token == operand)
				print_token(str);
			else if (token == rparen) {
				while (getStack()[top] != lparen)
					print_token(deleteS(&top));
				deleteS(&top);
			}
			else {
				while (isp[getStack()[top]] >= icp[token])
					print_token(deleteS(&top));
				add(&top, token);
			}
		}
		while ((token = deleteS(&top)) != eos)
			print_token(token);
		print_token(eos);

		strcpy(expr, post_expr);
		puts(expr);
	}
};
template<typename T>
class Eval : Stack {
	T token;
	int op1, op2;
	int n = 0;
	int top = -1;
public:
	int eval(void)
	{		
		char str;
		
		token = get_token(&str, &n);
		while (token != eos) {
			if (token == operand)
				add(&top, T(str - '0'));
			else {
				op2 = deleteS(&top);
				op1 = deleteS(&top);
				switch (token) {
				case plus:	add(&top, T(op1 + op2)); break;
				case minus:	add(&top, T(op1 - op2)); break;
				case times:	add(&top, T(op1 * op2)); break;
				case divide:add(&top, T(op1 / op2)); break;
				}
			}
			token = get_token(&str, &n);
		}
		return deleteS(&top);
	}
};

int main(void)
{
	Postfix<precedence>pfix;
	Eval<precedence>eval;
	
	cout << "계산식 입력 : "<<endl;
	cin >> expr;
	pfix.postfix();
	cout << "후위 표기 : " << eval.eval() << endl;
	return 0;
}

template<typename T>
void print_token(T token)
{
	static int index = 0;
	char aChar;

	switch (token) {
	case plus: aChar = '+'; break;
	case minus: aChar = '-'; break;
	case divide: aChar = '/'; break;
	case times: aChar = '*'; break;
	case eos: aChar = '\0'; break;
	default: aChar = token;
	}
	post_expr[index++] = aChar;
}

template<typename T>
T get_token(char *str, int * n)
{
	*str = expr[(*n)++];
	switch (*str) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '\0': return eos;
	default: return operand;
	}
}
bool isFull(int *top)
{
	if (*top >= MAX_STACK_SIZE - 1)
		return 0;
	else
		return 1;
}

template<typename T>
T stack_empty()
{
	exit(1);
}