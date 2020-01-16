#include <iostream>
#include <conio.h>

#pragma warning(disable:4996)

using namespace std;

int dayarr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

//윤년 체크 함수
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

	//++연산자 오버로딩
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
	//--연산자 오버로딩
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
	//외부로 출력 연산자 오버로딩을 위한 friend
	friend ostream& operator<<(ostream& cout, const Date& date);
};

//출력 연산자 오버로딩
ostream& operator<<(ostream& cout, const Date& date) {
	cout << date.year << "년 " << date.month << "월 " << date.day << "일";
	return cout;
}

void main()
{
	int y, m, d;
	cout << "Input Year[1~n] : ";
	cin >> y;

	if (y <= 0)//year이 0 이하면 exit
		exit(1);

	leapYear(y); //윤년체크

	cout << "Input Month[1~12] : ";
	cin >> m;

	if (m <= 0 || m >= 13)//month가 0이하거나 13이상이면 exit
		exit(2);

	cout << "Input Day[1~31]: ";
	cin >> d;

	if (d <= 0 || d > dayarr[m - 1])//day가 0이하거나 각 month의 최대 day를 넘어가면 exit
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

