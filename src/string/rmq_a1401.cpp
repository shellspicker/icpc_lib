#define FAST_IO 1

#include "template.h"
#include "basic/double_scale.h"
#define FUNC_HASH 1
#define STEP 1
#include "data_structure/rmq_hash.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int len;
	string text, ans;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(len, text));
		return cin;
		ioend(1);
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

		rmq_hash<tp, greater<tp>, seed> dsm(idx_nxt);
		dsm.init(vstr);

		int m2 = 0;
		fup_range (i, 0, len) {
			if (dsm.query(i, m2))
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
		const char *fmt_case = 0,
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
			if (fmt_case)
				fio.msg(fmt_case, ti);
			out();
		}
	}
#undef ioend
};

int main()
{
	new task(1, "Case #%d: ");
	return 0;
}
