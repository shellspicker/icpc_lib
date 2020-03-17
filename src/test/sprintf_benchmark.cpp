#include "template.h"
#include "basic/rand.h"

class test {
	static const int tn = 100000;
	double data[tn];
	void double_to_cstr(double x, int ndigit, char *buf) {
		int cnt = 0;
		ll xn = ll(x);
		if (xn < 0)
			*buf++ = '-', xn = -xn;
		do {
			buf[cnt++] = xn % 10 | 48;
			xn /= 10;
		} while (xn);
		reverse(buf, buf + cnt);
		buf[cnt++] = '.';
		x = x - ll(x);
		fup (t, 1, ndigit) {
			x = x * 10;
			buf[cnt++] = ll(x) | 48;
			x = x - ll(x);
		}
	}
public:
	void run() {
		char buf[50];
		int pos, sign;
		random_real<double> rd;
		clock_t t1, t2;

		rd.set(0, 100);
		for (int i = 0; i < tn; ++i)
			data[i] = rd();

		t1 = clock();
		for (int i = 0; i < tn; ++i) {
			snprintf(buf, 50, "%.20f", data[i], data[i]);
		}
		t2 = clock();
		printf("sprintf: %lu\n", (t2 - t1));

		t1 = clock();
		for (int i = 0; i < tn; ++i) {
			fcvt(data[i], 20, &pos, &sign);
		}
		t2 = clock();
		printf("fcvt: %lu\n", (t2 - t1));

		t1 = clock();
		for (int i = 0; i < tn; ++i) {
			double_to_cstr(data[i], 20, buf);
		}
		t2 = clock();
		printf("manual: %lu\n", (t2 - t1));
	}
};

int main()
{
	test gao;
	gao.run();
	return 0;
}
