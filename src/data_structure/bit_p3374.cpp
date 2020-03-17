#include "template.h"
#include "data_structure/bit.h"

class query {
public:
	int op, x, v;
	finput(is, query, o) {
		is >> o.op >> o.x >> o.v;
		return is;
	}
};

class data {
	vector<ll> v, ans;
	vector<query> qa;
	bit<ll> bb;
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
		bb.init(v.size() + 1);
		ans.clear();
		fup (i, 0, v.size() - 1)
			bb.add(i + 1, v[i]);
		for (auto q : qa) {
			if (q.op == 1) {
				bb.add(q.x, q.v);
			} else {
				ans.emplace_back(bb.presum_range(q.x, q.v));
			}
		}
	}
	void out() {
		for (auto x : ans)
			cout << x << endl;
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
