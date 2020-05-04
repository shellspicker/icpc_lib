#ifndef SADA_H
#define SADA_H 1

#ifndef STEP
#define STEP 0
#endif

/*
 * 后缀数组, 倍增.
 * 宏: STEP.
 * STEP, 下标跳跃.
 *
 * 下标连续
 * 初始化记得在后面加上极小字符值(一般字符串用'$').
 * 多串拼接起来, 传入vector, 字符值自行映射.
 */
#if STEP
template<class func_nxt = function<int(int)>>
#else
#endif
class sada {
public:
	vector<int> val, sa, rk, lcp;
	int vmx;
#if STEP
	vector<int> pnxt[2];
	func_nxt nxt;
#endif
#if STEP
	sada(func_nxt fn) : nxt(fn) {}
#endif
	void init(const string &s) {
		val.assign(it_each(s));
	}
	void init(const vector<int> &v) {
		val.assign(it_each(v));
	}
	void init_sa() {
		int len = val.size();
		sa.resize(len);
		iota(it_each(sa), 0);
		rk.assign(it_each(val));
		vmx = *max_element(it_each(rk));
		vector<int> rk1(len), sa1(len), rksa(len), cnt;
#if STEP
		auto counting_sort = [&](bool nxt_blk) {
#else
		auto counting_sort = [&]() {
#endif
			cnt.assign(vmx + 1, 0);
			fup_range (i, 0, len) {
#if STEP
				if (nxt_blk)
					rksa[i] = special(rk, pnxt[0][sa[i]], 0);
				else
					rksa[i] = rk[sa[i]];
#else
				rksa[i] = rk[sa[i]];
#endif
			}
			fup_range (i, 0, len)
				cnt[rksa[i]]++;
			partial_sum(it_each(cnt), cnt.begin());
			fwn_range (i, 0, len)
				sa1[--cnt[rksa[i]]] = sa[i];
			sa.swap(sa1);
		};
#if STEP
		fup (i, 0, 1)
			pnxt[i].resize(len);
		fup_range (i, 0, len)
			pnxt[0][i] = special(sa, nxt(i), -1);
		counting_sort(0);
#else
		counting_sort();
#endif
		// combine 2 segment which length is k.
		for (int k = 1; k < len; k <<= 1) {
#if STEP
			counting_sort(1);
			counting_sort(0);
#else
			int cc = 0;
			fwn_range_r (i, len - 1, k)
				sa1[cc++] = i;
			fup_range (i, 0, len)
				if (k <= sa[i])
					sa1[cc++] = sa[i] - k;
			sa.swap(sa1);
			counting_sort();
#endif
			rk1[sa[0]] = vmx = 0;
			fup (i, 1, len - 1) {
				bool f1, f2;
				f1 = rk[sa[i - 1]] ^ rk[sa[i]];
#if STEP
				f2 = special(rk, pnxt[0][sa[i - 1]], 0) ^ special(rk, pnxt[0][sa[i]], 0);
#else
				f2 = special(rk, sa[i - 1] + k, 0) ^ special(rk, sa[i] + k, 0);
#endif
				if (f1 || f2)
					vmx++;
				rk1[sa[i]] = vmx;
			}
			rk.swap(rk1);
#if STEP
			pnxt[0].swap(pnxt[1]);
			fup_range (i, 0, len)
				pnxt[0][i] = special(pnxt[1], pnxt[1][i], -1);
#endif
			if (vmx == len - 1)
				break;
		}
	}
	// this func can only deal connect index?
	void init_lcp() {
		int len = val.size();
		lcp.resize(len);
		lcp[0] = 0;
		for (int d = 0, p1 = 0; p1 < len - 1; ++p1) {
			if (d)
				d--;
			int p2 = sa[rk[p1] - 1];
			while (val[p1 + d] == val[p2 + d])
				d++;
			lcp[rk[p1]] = d;
		}
	}
};

#endif
