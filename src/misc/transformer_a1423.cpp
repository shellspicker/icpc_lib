#define FAST_IO 1
#include "template.h"
#include "string/hash.h"
#include "math/exgcd.h"
#include "math/gcd_lcm.h"
#include "math/mod.h"
#include "misc/transformer.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	ll n, p, mmp[35], ans;
	using perm = permutation<30>;
	typename cube<perm>::vpm face, buf;
	void preprocess() {
		fio.set_output_float_digit(12);
		cube<perm>::init();
		face.push_back({{9,10,11,12,13,14,15,16,17,0,1,2,3,4,5,6,7,8,20,19,18,29,28,27,26,25,24,23,22,21}});
		face.push_back({{2,5,8,1,4,7,0,3,6,15,12,9,16,13,10,17,14,11,21,22,23,24,25,26,27,28,29,18,19,20}});
		face.push_back({{9,10,11,3,4,5,6,7,8,0,1,2,12,13,14,15,16,17,20,19,18,29,22,23,24,25,26,27,28,21}});
		cube<perm>::level_bfs(buf, face, 100233);
		memset(mmp, 0, sizeof mmp);
		for (auto &o : buf) {
			vector<vector<int>> cycle;
			tie(cycle, ignore) = o.cycle();
			mmp[cycle.size()]++;
		}
	}
	istream &in() {
		fio.in(n, p);
		ioend(1);
		return cin;
	}
	void deal() {
		modulo::mod = p * buf.size();
		modulo tans = 0;
		fup (x, 1, 30)
			tans += modulo(mmp[x]) * (modulo(n) ^ modulo(x));
		ans = ll(tans) / buf.size();
	}
	void out() {
		fio.msg("%lld\n", ans);
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
	new task(1);
	return 0;
}
