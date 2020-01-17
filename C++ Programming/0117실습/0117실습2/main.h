#pragma warning(disable:4996)

#include<iostream>
#include<cctype>//isalpha()�Լ��� ���� �������� �˻��ϱ� ���� ����

#define MAX 100
using std::cout;
using std::cin;
using std::endl;

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, space, operand } precedence;

int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0, 0, 0, 0 };  //���ÿ� �ִ� ���� �켱����
int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0, 20, 20, 20 }; //���ÿ� ���� ���� �켱����
double stack[MAX]; //������ ����
int top;        //topǥ���� ����
char expr[MAX];
char post_expr[MAX];  //����ǥ�� ����
//�Լ�����/////////////////////////////////////////////////////////////////
void postfix(char*, char*);
precedence get_token(char*);
char print_token(precedence);
void init_stack(void);
void push(double);
double pop(void);
double eval(char* post);