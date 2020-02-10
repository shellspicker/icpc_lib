#ifndef SADA_H
#define SADA_H 1

class sada {
	string origin;
	vector<int> val, sa, rk, lcp;
public:
	void init(const string &str) {
		origin.assign(str);
		origin += '#';
		int sz = origin.size();
		sa.resize(sz);
		lcp.resize(sz);
		val.assign(it_each(origin));
		rk.assign(it_each(origin));
		iota(it_each(sa), 0);
		get_sa();
		get_lcp();
	}
	void get_sa() {
		int sz = rk.size(), cc;
		vector<int> rk1(sz), sa1(sz);
		auto get_vi = [&](vector<int> &v, int i) {
			if (i < v.size())
				return v[i];
			return 0;
		};
		auto counting_sort = [&](int k) {
			int vmx = *max_element(it_each(rk));
			vector<int> cnt(vmx + 1, 0);
			fup (i, 0, sz - 1)
				cnt[get_vi(rk, sa[i] + k)]++;
			partial_sum(it_each(cnt), cnt.begin());
			fwn (i, 0, sz - 1)
				sa1[--cnt[get_vi(rk, sa[i] + k)]] = sa[i];
			sa.swap(sa1);
		};
		counting_sort(1);
		counting_sort(0);
		for (int k = 1; k < sz; k <<= 1) {
			counting_sort(k);
			counting_sort(0);
			rk1[sa[0]] = cc = 0;
			fup (i, 1, sz - 1) {
				if (get_vi(rk, sa[i]) != get_vi(rk, sa[i - 1]) ||
					get_vi(rk, sa[i] + k) != get_vi(rk, sa[i - 1] + k))
					cc++;
				rk1[sa[i]] = cc;
			}
			rk.swap(rk1);
			if (rk[sa.back()] == sz - 1)
				break;
		}
	}
	void get_lcp() {
		int d = 0;
		lcp[0] = 0;
		fup (p1, 0, sa.size() - 2) {
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
