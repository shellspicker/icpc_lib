#pragma once

/*
 * 最(小/大)表示法.
 * first, 可求第一个或最后一个位置.
 * nxt, 下一个下标, 不能往负方向走(保证前缀相同可跳过的性质).
 * cmp, 比较方法, less或greater.
 *
 * 可支持不连续的下标, 设置一个估算的跳出层数.
 * 连续的下标, 可以求最后一个位置, 参考kmp循环串的性质.
 */
#if STEP
template<
	int limit = 23,
	class func_cmp = less<int>,
	class func_nxt = function<int(int)>>
pair<int, string> lexico_rotate(const string &s, bool first, func_nxt nxt) {
#else
template<
	class func_cmp = less<int>>
pair<int, string> lexico_rotate(const string &s, bool first) {
#endif
	pair<int, string> ret;
	int mi, lcp, len;
	func_cmp cmp = func_cmp();
	mi = 0;
	len = s.length();
	queue<int> path[2];
	vector<bool> skip(len);
#if STEP
	vector<bool> vis(len);
#endif
	fup_range (xi, 0, len) {
		if (mi == xi || skip[xi])
			continue;
		int mr = mi, xr = xi;
#if STEP
		int nos = 0;
#endif
		lcp = 0;
		while (lcp < len) {
			if (lcp) {
#if STEP
				mr = nxt(mr);
				xr = nxt(xr);
#else
				mr = round_shift(mr, 1, range(0, len));
				xr = round_shift(xr, 1, range(0, len));
#endif
			}
#if STEP
			if (vis[mr] && vis[xr] && limit <= ++nos)
				break;
			vis[mr] = 1;
			vis[xr] = 1;
#endif
			lcp++;
			path[0].push(mr);
			path[1].push(xr);
			if (s[mr] ^ s[xr]) {
				if (!cmp(s[mr], s[xr]))
					swap(mi, xi), swap(path[0], path[1]);
				break;
			}
		}
		while (!path[0].empty())
			path[0].pop();
		while (!path[1].empty()) {
			skip[path[1].front()] = 1;
			path[1].pop();
		}
		if (!first && lcp == len) {
			int cycle = xi - mi;
			mi += div_last_offset(length(mi, len - 1), cycle) * cycle;
			xi = mi;
		}
	}
	ret.first = mi;
	fup_range (d, 0, len) {
		if (d)
#if STEP
			mi = nxt(mi);
#else
			mi = round_shift(mi, 1, range(0, len));
#endif
		ret.second += s[mi];
	}
	return ret;
}

#undef STEP
