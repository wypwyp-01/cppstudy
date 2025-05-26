#include<iostream>
using namespace std;
class Base {
public:
	int a = 1;
	virtual void funç(int a = 10, int b = 20) {
		std::cout << "func(" << a << "b" << std::endl;
	}
		
};

class Derived : public Base {
public:
	int b = 21;
		virtual void funç(int a = 1, int b = 2) {
		std::cout << "func(" << a << "b" << std::endl;
	}
	};
	
int main() {
	Base * a = new Derived[10];
	a[7].funç();
	return 0;
}