#include <iostream>
#include <conio.h>

#pragma warning(disable:4996)

using namespace std;

int dayarr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

//���� üũ �Լ�
void leapYear(int year) { 
	if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
		dayarr[1] = 29;
	else
		dayarr[1] = 28;
}

class Date {
	int year;
	int month;
	int day;
	
public:
	Date(int y, int m, int d) :year(y), month(m), day(d) {}
	Date()	{}

	//++������ �����ε�
	Date& operator++()
	{
		leapYear(this->year);
		if (this->day >= dayarr[this->month - 1]) {
			this->day = 1;
			this->month++;

			if (this->month > 12) {
				this->month = 1;
				this->year++;
			}
		}
		else
		this->day++;
		return *this;
	}
	//--������ �����ε�
	Date& operator--()
	{
		leapYear(this->year);
		if (this->day <= 1){
			if (this->month <= 1) {
				this->month = 12;
				this->year--;
			}else {
				this->month--;
			}
			this->day = dayarr[this->month - 1];
		}else
		this->day--;

		return *this;
	}
	//�ܺη� ��� ������ �����ε��� ���� friend
	friend ostream& operator<<(ostream& cout, const Date& date);
};

//��� ������ �����ε�
ostream& operator<<(ostream& cout, const Date& date) {
	cout << date.year << "�� " << date.month << "�� " << date.day << "��";
	return cout;
}

void main()
{
	int y, m, d;
	cout << "Input Year[1~n] : ";
	cin >> y;

	if (y <= 0)//year�� 0 ���ϸ� exit
		exit(1);

	leapYear(y); //����üũ

	cout << "Input Month[1~12] : ";
	cin >> m;

	if (m <= 0 || m >= 13)//month�� 0���ϰų� 13�̻��̸� exit
		exit(2);

	cout << "Input Day[1~31]: ";
	cin >> d;

	if (d <= 0 || d > dayarr[m - 1])//day�� 0���ϰų� �� month�� �ִ� day�� �Ѿ�� exit
		exit(3);

	Date date(y, m, d);

	while (1) {
		char c;	
		system("cls");
		cout << "[Input Number 1 = ++]" << endl;
		cout << "[Input Number 2 = --]" << endl;
		cout << "[Else Key Exit..    ]" << endl;
		cout << date << endl;
		c = getch();
		if (c == '1') {
			++date;
		}
		else if (c == '2') {
			--date;
		}
		else
			break;
	}
	exit(0);
}

