#include "template.h"
#include "basic/radix_sort.h"

class data {
	vector<uint> v;
	istream &ioend() {
		cin.setstate(ios_base::badbit);
		return cin;
	}
public:
	istream &in() {
		int n;
		cin >> n;
		if (!cin)
			return ioend();
		v.resize(n);
		fup (i, 0, n - 1)
			cin >> v[i];
		return cin;
	}
	void deal() {
		radix_sort(v);
	}
	void out() {
		fup (i, 0, v.size() - 1)
			cout << v[i] << " \n"[i == v.size() - 1];
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
