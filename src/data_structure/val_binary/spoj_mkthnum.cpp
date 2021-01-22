#define FAST_IO 1
#include "template.h"
#include "data_structure/bit.h"
#include "basic/descrete.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	struct query {
		int type;
		union {
			struct {
				int x, v;
			} upd;
			struct {
				int id, l, r, k;
			} que;
		};
	};
	int n, q;
	vector<int> data, ans;
	vector<query> que;
	bit<int> dsm;
	descrete<int> des;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n) && fio.in(q));
		data.clear();
		que.clear();
		fup_range (i, 0, n) {
			int x;
			fio.in(x);
			que.push_back((query){
				.type = 1,
				{
					.upd = {
						.x = i + 1,
						.v = x,
					},
				},
			});
			data.push_back(x);
		}
		fup_range (i, 0, q) {
			int l, r, k;
			fio.in(l, r, k);
			que.push_back((query){
				.type = 2,
				{
					.que = {
						.id = i,
						.l = l,
						.r = r,
						.k = k,
					},
				},
			});
		}
		ioend(1);
		return cin;
	}
	void deal() {
		dsm.init(n + 5);
		des.init(data);
		ans.resize(q);
		fup_range (i, 0, n) {
			query &qa = que[i];
			qa.upd.v = data[i];
		}
		function<void(int, int, int, int)> val_binary = [&](int m1, int m2, int st, int ed) {
			if (!length(st, ed))
				return;
			if (m1 == m2) {
				fup (i, st, ed) {
					query &qy = que[i];
					if (qy.type == 2)
						ans[qy.que.id] = des.get(m1);
				}
				return;
			}
			int mm = midpoint(m1, m2);
			vector<query> split[2];
			fup (qi, st, ed) {
				query qy = que[qi];
				if (qy.type == 1) {
					if (qy.upd.v < mm) {
						split[0].push_back(qy);
						dsm.add(qy.upd.x, 1);
					} else {
						split[1].push_back(qy);
					}
				} else {
					int cnt = dsm.presum_range(qy.que.l, qy.que.r);
					if (qy.que.k <= cnt) {
						split[0].push_back(qy);
					} else {
						qy.que.k -= cnt;
						split[1].push_back(qy);
					}
				}
			}
			fup (qi, st, ed) {
				query qy = que[qi];
				if (qy.type == 1 && qy.upd.v < mm)
					dsm.add(qy.upd.x, -1);
			}
			copy(it_each(split[0]), it_i(que, st));
			copy(it_each(split[1]), it_i(que, st + split[0].size()));
			val_binary(m1, mm - 1, range(st, split[0].size()));
			val_binary(mm, m2, range_r(ed, split[1].size()));
		};
		val_binary(0, des.size() - 1, 0, que.size() - 1);
	}
	void out() {
		fup_range (i, 0, q)
			fio.msg("%d\n", ans[i]);
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
	new task();
	return 0;
}
