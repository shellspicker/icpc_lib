#include "template.h"
#include "data_structure/rmq.h"

class query {
public:
	int l, r, ans;
	finput(is, query, o) {
		is >> o.l >> o.r;
		o.l--;
		o.r--;
		return is;
	}
	foutput(os, query, o) {
		os << o.ans;
		return os;
	}
};

class data {
	vector<int> v;
	vector<query> qa;
	rmq<int> dsm{[](int a, int b) { return max(a, b); }};
	istream &ioend() {
		cin.setstate(ios_base::badbit);
		return cin;
	}
public:
	istream &in() {
		int vn, qn;
		cin >> vn >> qn;
		if (!cin)
			return ioend();
		v.resize(vn);
		fup (i, 0, vn - 1)
			cin >> v[i];
		qa.resize(qn);
		fup (i, 0, qn - 1)
			cin >> qa[i];
		return cin;
	}
	void deal() {
		dsm.init(v);
		for (auto &q : qa)
			q.ans = dsm.query(q.l, q.r);
	}
	void out() {
		for (auto &q : qa)
			cout << q << endl;
	}
};

class task {
	int testcase = 1 << 30;
	stringstream tid;
	data gkd{};
public:
	task(
		bool multicase = false,
		bool testid = false,
		bool blankline = false) {
		ios::sync_with_stdio(0);
		cin.tie(0);
		cout.setf(ios::fixed);
		cout.precision(20);
		if (multicase)
			cin >> testcase;
		for (int ti = 1; ti <= testcase && gkd.in(); ++ti) {
			gkd.deal();
			if (blankline && 1 < ti)
				cout << endl;
			tid << "Case #" << ti << ": ";
			if (testid)
				cout << tid.str();
			gkd.out();
			tid.str("");
		}
	}
};

int main()
{
	task gkd(0, 0, 0);
	return 0;
}
