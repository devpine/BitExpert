#pragma warning(disable:4996)

#include<iostream>
#include<cctype>//isalpha()함수를 통해 문자인지 검사하기 위해 선언

#define MAX 100
using std::cout;
using std::cin;
using std::endl;

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, space, operand } precedence;

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0, 0, 0, 0 };  //스택에 있는 값의 우선순위
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0, 20, 20, 20 }; //스택에 들어가는 값의 우선순위
double stack[MAX]; //스택을 정의
int top;        //top표인터 정의
char expr[MAX];
char post_expr[MAX];  //후위표기 저장
//함수원형/////////////////////////////////////////////////////////////////
void postfix(char*, char*);
precedence get_token(char*);
char print_token(precedence);
void init_stack(void);
void push(double);
double pop(void);
double eval(char* post);