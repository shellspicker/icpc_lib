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
	template<typename iter>
	static
	vector<int> build(iter st, size_t len) {
		vector<int> ret(len + 1);
		ret[0] = -1;
		fup_range (cur, 0, len) {
			int pre = ret[cur];
			while (~pre && st[cur] ^ st[pre])
				pre = ret[pre];
			ret[cur + 1] = pre + 1;
		}
#if KNUTH
		fup_range (cur, 0, len) {
			int &pre = suf[cur];
			while (~pre && st[cur] == st[pre])
				pre = ret[pre];
		}
#endif
		return ret;
	}
	template<typename iter>
	static
	vector<int> search(
			iter big, int blen,
			iter small, int slen,
			const vector<int> &tbl) {
		vector<int> occ;
		int pre = 0;
		fup_range (cur, 0, blen) {
			while (~pre && big[cur] ^ small[pre])
				pre = tbl[pre];
			if (++pre == slen)
				occ.push_back(rtol(cur, slen));
		}
		return occ;
	}
	template<typename iter>
	static
	vector<int> search(
			iter big, int blen,
			iter small, int slen) {
		vector<int> ret;
		string comb = string(small, small + slen) + '$' + string(big, big + blen);
		vector<int> tbl = build(comb.begin(), comb.size());
		int offset = slen * 2 + 1;
		fup (i, offset, comb.size()) {
			if (tbl[i] == slen)
				ret.push_back(i - offset);
		}
		return ret;
	}
};

