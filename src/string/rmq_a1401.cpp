#define FAST_IO 1

#include "template.h"
#define FUNC_HASH 1
#include "data_structure/rmq.h"

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
		getans<ull, 3137>();
	}
	void out() {
		fio.out(ans, '\n');
	}
	template<typename tp, tp seed>
	void getans() {
		auto nxt = [=](ll i) {
			return (i * i + 1) % len;
		};
		vector<int> idx_nxt;
		idx_nxt.resize(len);
		fup_range (i, 0, len)
			idx_nxt[i] = nxt(i);

		vector<tp> vstr;
		vstr.assign(it_each(text));

		rmq<tp, greater<tp>, seed> dsm(
				[](tp a, tp b) { return a + b; },
				idx_nxt);
		dsm.init(vstr);

		int m2 = 0;
		fup_range (i, 0, len) {
			if (dsm.range_query(i, m2))
				m2 = i;
		}

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
