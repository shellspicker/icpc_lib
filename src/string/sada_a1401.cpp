/*
 * 后缀数组, 下标跳跃.
 * 注意不需要在字符串结尾加最小字符了.
 */
#define FAST_IO 1

#include "template.h"
#define STEP 1
#include "string/sada.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond)) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int len;
	string text, ans;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(len, text));
		return cin;
	}
	void deal() {
		getans();
	}
	void out() {
		fio.out(ans, '\n');
	}
	void getans() {
		auto nxt = [=](ll i) {
			return (i * i + 1) % len;
		};
		sada<> sa(nxt);
		sa.init(text);
		sa.init_sa();

		int m2 = sa.sa[len - 1];
		ans.clear();
		fup (t, 1, len) {
			ans += text[m2];
			m2 = nxt(m2);
		}
	}
public:
	task(
		bool multicase = 0,
		bool testid = 0,
		bool blankline = 0) {
		static int testcase = 1 << 30;
		static stringstream tid;
		preprocess();
		if (multicase)
			fio.in(testcase);
		for (int ti = 1; ti <= testcase && in(); ++ti) {
			deal();
			if (blankline && 1 < ti)
				fio.out('\n');
			if (testid) {
				tid << "Case #" << ti << ": ";
				fio.out(tid.str());
				tid.str("");
			}
			out();
		}
	}
#undef ioend
} gkd(1, 1, 0);

int main()
{
	return 0;
}
