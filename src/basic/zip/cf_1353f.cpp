#define FAST_IO 1
#include "template.h"
#include "basic/zip.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int gr, gc;
	zip_vector<ll> grid{{1, 1}};
	ll ans;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		fio.in(gr, gc);
		new (&grid) decltype(grid)({gr, gc});
		fup_range (r, 0, gr)
			fup_range (c, 0, gc)
				fio.in(grid(r, c));
		ioend(1);
		return cin;
	}
	void deal() {
		zip_vector<ll> dp({gr, gc});
		auto trans = [&](int r0, int c0, int r1, int c1, ll add) {
			if (add < 0)
				return;
			if (!r0 && !c0) {
				dp(r0, c0) = add;
				return;
			}
			if (!inrange(r1, 0, gr - 1) || !inrange(c1, 0, gc - 1))
				return;
			if (dp(r1, c1) == get_inf<ll>())
				return;
			dp(r0, c0) = min(dp(r0, c0), dp(r1, c1) + add);
		};
		auto calc = [&](ll s) {
			if (!(s <= grid(0, 0)))
				return;
			fup_range (i, 0, dp.size())
				dp[i] = get_inf<ll>();
			fup_range (r, 0, gr) {
				fup_range (c, 0, gc) {
					ll aim, diff;
					aim = s + r + c;
					diff = grid(r, c) - aim;
					trans(r, c, r - 1, c, diff);
					trans(r, c, r, c - 1, diff);
				}
			}
			if (dp(gr - 1, gc - 1) ^ get_inf<ll>())
				ans = min(ans, dp(gr - 1, gc - 1));
		};
		ans = get_inf<ll>();
		fup_range (r, 0, gr) {
			fup_range (c, 0, gc) {
				ll fixed, start;
				fixed = grid(r, c);
				start = fixed - r - c;
				calc(start);
			}
		}
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
