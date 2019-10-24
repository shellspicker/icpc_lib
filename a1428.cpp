// 题意: 给出一堆字符串, 把每个串的后缀拼起来, 求最小字典序的组合.
//
// 做法就是从后往前拼接字符串, hash二分lcp再比较下一位.
// 细节就是hash是从后往前接的, 但是字符串是从前往后算下标的, 主要就是下标计算.
// 正反同时扫描的下标都明确了就简单了, 二分很好写的.
#include <bits/stdc++.h>
using std::cin;
using std::cout;
using std::string;
using std::vector;
typedef unsigned long long ull;
ull seed = 3137;

int tc, inn;
vector<string> vs;
string ans;
ull hs[500233], xp[500233];

int idx(char ch)
{
	return ch - 'a';
}

ull calc_hs(int px, int len)
{
	return hs[px + len - 1] - hs[px - 1] * xp[len];
}

void add(string &s)
{
	int prefix = ans.length(), nowlen,
		hsst = 1;

	ans = s + ans;
	nowlen = ans.length();
	for (int i = prefix, k = s.length() - 1;
			k >= 0; ++i, --k) {
		hs[hsst + i] = hs[hsst + i - 1] * seed + idx(s[k]);
	}

	int m1i = 0;
	for (int i = 0; i < s.length(); ++i) {
		int p1, p2, m2len,
			L, R, M,
			lcp;

		p1 = i, p2 = m1i, m2len = ans.length() - std::max(p1, p2);
		L = 0, R = m2len;
		while (L <= R) {
			M = (L + R) / 2;
			if (calc_hs(hsst + nowlen - p1 - M, M) ==
					calc_hs(hsst + nowlen - p2 - M, M))
				L = M + 1;
			else
				R = M - 1;
		}
		lcp = R;
		if (lcp == m2len) {
			m1i = std::max(p1, p2);
		} else {
			if (ans[p1 + lcp] < ans[p2 + lcp])
				m1i = p1;
			else
				m1i = p2;
		}
	}
	ans.erase(ans.begin(), ans.begin() + m1i);
}

void deal()
{
	hs[0] = 0;
	for (long i = vs.size() - 1; i >= 0; --i) {
		add(vs[i]);
	}
	cout << ans << '\n';
}

void preprocess()
{
	xp[0] = 1;
	for (int i = 1; i < 500000; ++i) {
		xp[i] = xp[i - 1] * seed;
	}
}

int main()
{
	std::ios::sync_with_stdio(false);
	cin.tie(0);
	preprocess();

	cin >> tc;
	while(tc--) {
		vs.clear();
		ans.clear();

		cin >> inn;
		while(inn--) {
			string ss;
			getline(cin >> std::ws, ss);
			vs.push_back(ss);
		}
		deal();
	}
	return 0;
}
