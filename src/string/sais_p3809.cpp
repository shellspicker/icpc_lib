#include "template.h"
#include "string/sais.h"

class data {
	string s;
	sais sa;
	istream &ioend() {
		cin.setstate(ios_base::badbit);
		return cin;
	}
public:
	istream &in() {
		cin >> s;
		return cin;
	}
	void deal() {
		sa.init(s);
	}
	void out() {
		fup (i, 1, sa.sa.size() - 1)
			cout << sa.sa[i] + 1 << " \n"[i == sa.sa.size() - 1];
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
