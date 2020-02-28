#include "template.h"
#include "math/mod.h"

int main()
{
	modular::mod = 666;
	modular a(233), b(233), c(233);
	cout << (a * b) << endl;
	cout << (a ^ b) << endl;
	cout << (a * b * c) << endl;
	return 0;
}
