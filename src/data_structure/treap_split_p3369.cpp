#define FAST_IO 1

#include "template.h"
#include "data_structure/treap_split.h"

class query {
public:
	int op, x;
};

class task {
#define ioend(cond) \
	do {\
		if (!(cond)) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int testcase = 1 << 30;
	stringstream tid;
	direct_io fio;
	debuger bug;
	vector<query> qa;
	vector<int> ans;
	treap<int, 1, 100233> dsm;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		int qn;
		ioend(fio.in(qn));
		qa.resize(qn);
		fup (i, 0, qn - 1) {
			int op, x;
			fio.in(op, x);
			qa[i] = {op, x};
		}
		return cin;
	}
	void deal() {
		ans.clear();
		dsm.init();
		for (auto q : qa) {
			switch (q.op) {
				case 1: {
					dsm.insert(0, q.x);
					break;
				}
				case 2: {
					dsm.remove(0, q.x);
					break;
				}
				case 3: {
					auto fd = dsm.search(dsm(0), q.x, 0, 1);
					ans.emplace_back(fd.first);
					break;
				}
				case 4: {
					auto fd = dsm.kth(dsm(0), q.x, 0);
					ans.emplace_back(fd->key);
					break;
				}
				case 5: {
					auto fd = dsm.search(dsm(0), q.x, 0, 0);
					ans.emplace_back(fd.second->key);
					break;
				}
				case 6: {
					auto fd = dsm.search(dsm(0), q.x, 1, 0);
					ans.emplace_back(fd.second->key);
					break;
				}
			}
		}
	}
	void out() {
		for (auto x : ans)
			fio.out(x, '\n');
	}
public:
	task(
		bool multicase = 0,
		bool testid = 0,
		bool blankline = 0) {
		preprocess();
		if (multicase)
			fio.in(testcase);
		for (int ti = 1; ti <= testcase && in(); ++ti) {
			deal();
			if (blankline && 1 < ti)
				fio.out('\n');
			tid << "Case #" << ti << ": ";
			if (testid)
				fio.out(tid.str());
			out();
			tid.str("");
		}
	}
#undef ioend
} gkd(0, 0, 0);

int main()
{
	return 0;
}
