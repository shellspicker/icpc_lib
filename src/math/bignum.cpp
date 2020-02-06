#include "template.h"
#include "math/bignum.h"

int main()
{
	int x, y;
	string x_str;
	cin >> x >> y >> x_str;
	bignum a;
	a.set_base(x);
	a(x_str);
	auto b = a.trans_base(y);
	cout << b << endl;
	return 0;
}
