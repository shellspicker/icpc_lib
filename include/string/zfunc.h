#ifndef ZFUNC_H
#define ZFUNC_H 1

/*
 * z algorithm, 国内一些憨憨称为exkmp...
 *
 * 计算一个字符串的每个后缀和其本身的lcp.
 * 核心思想: 利用之前计算过的最长lcp和其对应的下标.
 *
 * 计算2个字符串, pattern的后缀和text的lcp, 可以拼接这2个串, 也可以不拼接.
 */

class zfunc {
public:
	zfunc() {}
	/*
	 * 单串
	 */
	vector<int> gao(const string &s) {
		int len = s.length();
		vector<int> ret(len);
		for (int i = 1, c = 0, r = 0; i < len; ++i) {
			int &lcp = ret[i];
			if (i <= r)
				lcp = min(length(i, r), (ll)ret[i - c]);
			while (i + lcp < len && s[lcp] == s[i + lcp])
				lcp++;
			if (r < ltor(i, lcp))
				r = ltor(c = i, lcp);
		}
		return ret;
	}
	/*
	 * 求pattern的所有后缀和text的lcp.
	 * 拼接2个串.
	 */
	vector<int> gao(const string &t, const string &p) {
		string s = t + '$' + p;
		return gao(s);
	}
	/*
	 * 求pattern的所有后缀和text的lcp.
	 * text, 需要预处理zfunc.
	 */
	vector<int> gao(const string &t, const vector<int> &tz, const string &p) {
		int tlen = t.length(), plen = p.length();
		vector<int> ret(plen);
		for (int i = 0, c = 0, r = 0; i < plen; ++i) {
			int &lcp = ret[i];
			if (i <= r)
				lcp = min(length(i, r), (ll)tz[i - c]);
			while (lcp < tlen && i + lcp < plen && t[lcp] == p[i + lcp])
				lcp++;
			if (r < ltor(i, lcp))
				r = ltor(c = i, lcp);
		}
		return ret;
	}
};

#endif
