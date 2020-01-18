#include <iostream>
#include <cstring>
#define MAX_STACK_SIZE 100	
#pragma warning(disable:4996)

typedef enum {
	lparen, rparen, plus, minus, times, divide,
	 eos, operand
} precedence;

using std::cout;
using std::endl;
using std::cin;

char expr[MAX_STACK_SIZE];
char post_expr[MAX_STACK_SIZE];

static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

template<typename T> void print_token(T );
//template<typename T> void add(int, T );
//template<typename T> T deleteS(int *top);
template<typename T>T get_token(char *symbol, int * n);
precedence stack_empty();
bool isFull(int*);
//void postfix(void);
//int eval(void);