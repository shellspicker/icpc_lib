#include "template.h"
#include "math/lagrange_interpolation.h"
#include "math/newton_interpolation.h"

vector<double> x{10, 11, 12}, y{1345, 1633, 1949};

void test_newton()
{
	ull dimx = 1000000000;
	ull ret = newton_interpolation(x, y, dimx);
	assert(ret == 13999999994000000005llu);
}

void test_lagrange()
{
	vector<double> xiuu = lagrange_interpolate(x, y);
	assert(xiuu[0] == 5.0f);
	assert(xiuu[1] == -6.0f);
	assert(xiuu[2] == 14.0f);
}

int main()
{
	test_newton();
	test_lagrange();
	return 0;
}
