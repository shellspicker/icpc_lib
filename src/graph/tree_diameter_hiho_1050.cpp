#define FAST_IO 1

#include "template.h"
#include "graph/graph.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int n, ans;
	undigraph<int> g;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n));
		g.resize(n);
		fup (t, 1, n - 1) {
			int a, b;
			fio.in(a, b);
			a--, b--;
			g.add(a, b);
		}
		ioend(1);
		return cin;
	}
	void deal() {
		vector<int> dis1 = bfs(0);
		int m2 = -inf32, cur;
		fup_range (i, 0, n) {
			if (m2 < dis1[i])
				m2 = dis1[cur = i];
		}
		vector<int> dis2 = bfs(cur);
		m2 = *max_element(it_each(dis2));
		ans = m2;
	}
	void out() {
		fio.out(ans, '\n');
	}
	vector<int> bfs(int s) {
		struct state {
			int x, d;
		};
		queue<state> que;
		vector<int> dis(n);
		vector<bool> vis(n);
		que.push({s, 0});
		while (!que.empty()) {
			int u, v, d;
			state now = que.front();
			que.pop();
			u = now.x;
			d = now.d;
			vis[u] = 1;
			dis[u] = d;
			for (auto e : g[u]) {
				auto info = g.info(e);
				v = info.to;
				if (vis[v])
					continue;
				que.push({v, d + info.cost});
			}
		}
		return dis;
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
} gkd;

int main()
{
	return 0;
}
