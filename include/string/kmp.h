#pragma once

/*
 * kmp.
 * 宏: KNUTH.
 *
 * KNUTH.
 * 一般的写法叫做mp而不是kmp, 加入knuth优化的才是kmp.
 * 优化点是, 跳转发生在失配时, 那么跳转之后有相同的待匹配字符, 可以再次跳转.
 *
 * 首先要知道标准字符串表示方法, 下标起始0, 偏移length.
 * 这里, 下标即为前缀(已经匹配)长度, 也是下一个要匹配的字符.
 * 以上这句话一定要理解, 下标起始0的存储方式, 都有这个意思.
 *
 * 核心是构造最长公共真前后缀(可能有别的称呼).
 * 构造方法类似ac自动机, 不知道ac自动机也没关系, 但是要知道自动机.
 * 画个自动机就知道, null(idx:-1), root(idx:0), 字符串匹配状态(idx:[1, length]).
 * 一共length + 2个状态.
 * null->root是无条件匹配, 后面的点是相同后缀的转移.
 *
 * 应该有个自动机的图解说一下, 待补充.
 * 演算法笔记里面有图, 可以凑合看看.
 */

class kmp {
public:
	string small;
	vector<int> suf;
	kmp() {}
	kmp(string &p) : small(p) {
		suf.resize(p.length() + 1);
		build();
	}
private:
	void build() {
		suf[0] = -1;
		fup_range (cur, 0, small.length()) {
			int pre = suf[cur];
			while (~pre && small[cur] != small[pre])
				pre = suf[pre];
			suf[cur + 1] = pre + 1;
		}
#if KNUTH
		fup_range (cur, 0, small.length()) {
			int &pre = suf[cur];
			while (0 <= pre && small[cur] == small[pre])
				pre = suf[pre];
		}
#endif
	}
public:
	vector<int> search(string &big) {
		vector<int> ret;
		int pre = 0;
		fup_range (cur, 0, big.length()) {
			while (0 <= pre && big[cur] != small[pre])
				pre = suf[pre];
			if (++pre == small.length())
				ret.push_back(rtol(cur, small.length()));
		}
		return ret;
	}
	vector<int> search(string &big, string &small) {
		vector<int> ret;
		string comb = small + '$' + big;
		new (this) kmp(comb);
		int offset = small.length() * 2 + 1;
		fup (i, offset, comb.length()) {
			if (suf[i] == small.length())
				ret.push_back(i - offset);
		}
		return ret;
	}
};
