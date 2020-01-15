#include <iostream>
#include <string>

using namespace std;

class Plane {
private:
	int num;
	string model;
	int pass;

public:
	int getNum() { return num; }
	void setNum(int n) { num = n; }
	string getModel() { return model; }
	void setModel(string m) { model = m; }
	int getPass() { return pass; }
	void setPass(int p) { pass = p; }

	Plane() :num(1) {};
	Plane(int n) :num(n){}
	Plane(int n, string m) : num(n), model(m){}
	Plane(int n, string m, int p) : num(n), model(m), pass(p){	}
	~Plane() {};

	void print() 
	{
		cout << "½Äº°  ¹øÈ£ : " << num << endl;
		cout << "¸ð      µ¨ : " << model << endl;
		cout << "½Â  °´  ¼ö : " << pass << endl;
	}
};

int main()
{
	Plane p1, p2(1), p3(2, "B-747"), p4(3, "A-330", 80);
	p1.setModel("A-380");
	p1.setPass(60);
	p2.setModel("B-787");
	p2.setPass(120);
	p3.setPass(140);
	p1.print();
	p2.print();
	p3.print();
	p4.print();
	return 0;
}