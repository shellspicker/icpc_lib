#pragma once

class sais {
public:
	string origin;
	vector<int> val, sa, rk, lcp;
	int len;
	void init(const string &s) {
		val.assign(it_each(s));
	}
	void init(const vector<int> &v) {
		val.assign(it_each(v));
	}
	void init_sa() {
		int len = val.size();
		sa.resize(len);
		init_sa(val, sa);
	}
	void init_sa(vector<int> &text, vector<int> &sa) {
		int len = text.size(), vmx = *max_element(it_each(text));
		vector<int> bk(vmx + 1), lbk(vmx + 1), sbk(vmx + 1), lms;
		vector<bool> type(len);
		auto is_lms_char = [&](int i) {
			return !type[i] && 0 < i && type[i - 1];
		};
		auto is_lms_equal = [&](int p1, int p2) {
			/*
			 * this judge can't deal one is lms and other is not lms,
			 * but text is equal, is think this can not judge equal.
			 * it is seems not affect sa.
			 */
			for (bool f1, f2; text[p1] == text[p2]
				&& (f1 = is_lms_char(++p1), f2 = is_lms_char(++p2), !(f1 & f2)););
			return (text[p1] == text[p2]);
		};
		auto reset_bk = [&]() {
			lbk[0] = sbk[0] = 0;
			fup (x, 1, bk.size() - 1) {
				lbk[x] = bk[x - 1];
				sbk[x] = bk[x] - 1;
			}
		};
		auto push_lbk = [&](int pos) {
			sa[lbk[text[pos]]++] = pos;
		};
		auto push_sbk = [&](int pos) {
			sa[sbk[text[pos]]--] = pos;
		};
		auto induced_sort = [&]() {
			fill(it_each(sa), -1);
			reset_bk();
			fwn_range (i, 0, lms.size())
				push_sbk(lms[i]);
			fup_range (i, 0, sa.size())
				if (0 < sa[i] && type[sa[i] - 1])
					push_lbk(sa[i] - 1);
			reset_bk();
			fwn_range (i, 0, sa.size())
				if (0 < sa[i] && !type[sa[i] - 1])
					push_sbk(sa[i] - 1);
		};
		for (auto x : text)
			bk[x]++;
		partial_sum(it_each(bk), bk.begin());
		type.back() = 0;
		fwn (i, 0, len - 2)
			type[i] = text[i] == text[i + 1] ? type[i + 1] : text[i] > text[i + 1];
		fup (i, 1, len - 1)
			if (is_lms_char(i))
				lms.emplace_back(i);
		induced_sort();
		vector<int> rr(len);
		int cc = 0, last = -1;
		fill(it_each(rr), -1);
		fup_range (i, 0, len) {
			int pos = sa[i];
			if (is_lms_char(pos)) {
				if (~last && !is_lms_equal(pos, last))
					cc++;
				rr[pos] = cc;
				last = pos;
			}
		}
		bool flag = cc + 1 == lms.size();
		vector<int> text1(lms.size()), sa1(lms.size());
		copy_if(it_each(rr), text1.begin(), [](int x) { return ~x; });
		if (flag)
			fup_range (i, 0, lms.size())
				sa1[text1[i]] = i;
		else
			init_sa(text1, sa1);
		transform(it_each(sa1), sa1.begin(), [&](int x) { return lms[x]; });
		lms.swap(sa1);
		induced_sort();
	}
	void init_lcp() {
		int len = val.size();
		rk.resize(len);
		lcp.resize(len);
		fup_range (i, 0, len)
			rk[sa[i]] = i;
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
