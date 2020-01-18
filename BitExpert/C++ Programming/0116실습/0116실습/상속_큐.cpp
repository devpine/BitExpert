#include <iostream>
#include <conio.h>
#define SIZE 101
#pragma warning(disable:4996)
using namespace std;

class List
{
	int rear;
	int front;
	int size;
	int *list;

public:
	
	List()
	{
		size = SIZE;
		list = new int[size];
		rear = 0;
		front = 0;
	}
	~List()
	{
		delete[] list;
	}
	bool isFull()
	{
		if ((rear + 1) % size == front)
			return true;
		else
			return false;
	}

	bool empty() {
		if (rear == front)
			return true;
		else
			return false;
	}

	void push_front(int data) {
		if (!isFull())
		{
			list[rear] = data;
			rear = (rear + 1) % size;
		}
		else
			cout << "FULL" << endl;
	}

	void pop_front() {
		if (!empty())
			front = (front + 1) % size;
		else
			cout << "Empty" << endl;		
	}
	
	void print()
	{
		cout << "front [ ";
		for (int i = front; i < rear ; i++)
		{
			cout << list[i];
			if (i < rear - 1) cout << " | ";
		}
		cout << " ] rear" << endl;
	}
};

class Queue : private List
{
public:
	void push(int data) { List::push_front(data); }
	void pop() { List::pop_front(); }
	void print() { List::print(); }
};


int main() {
	int data;
	int c;
	Queue q;
	
	while (1) {
		system("cls");
		cout << "[1]삽입 [2]삭제 [else]종료"<<endl;
		q.print();
		c = getch();
		if (c == '1'){
			cout << "값 입력 : ";
			cin >> data;
			q.push(data);
		}
		else if (c == '2') {
			q.pop();
		}
		else
			exit(1);
	}
}