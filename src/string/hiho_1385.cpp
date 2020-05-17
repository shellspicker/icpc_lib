#define FAST_IO 1

#include "template.h"
#include "string/utils.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	string line;
	vector<string> paragraph;
	map<string, int> mmp;
	int m2;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		paragraph.clear();
		while (fio.readline(line)) {
			if (line == "####")
				break;
			paragraph.push_back(line);
		}
		ioend(1);
		return cin;
	}
	void deal() {
		mmp.clear();
		m2 = -inf32;
		for (auto line : paragraph) {
			vector<string> token_by_dot = get_token(line, ",.");
			for (auto tok_dot : token_by_dot) {
				vector<string> token_by_blank = get_token(tok_dot, " ");
				if (token_by_blank.size() < 2)
					continue;
				fup (i, 1, token_by_blank.size() - 1) {
					string phrase = token_by_blank[i - 1] + ' ' + token_by_blank[i];
					m2 = max(m2, ++mmp[phrase]);
				}
			}
		}
	}
	void out() {
		for (auto it : mmp) {
			if (it.second == m2) {
				fio.out(it.first, ':', it.second, '\n');
				break;
			}
		}
	}
public:
	task(
		bool multicase = 0,
		bool testid = 0,
		bool blankline = 0) {
		static int testcase = 1 << 30;
		static stringstream tid;
		preprocess();
		if (multicase)
			fio.in(testcase);
		for (int ti = 1; ti <= testcase && in(); ++ti) {
			deal();
			if (blankline && 1 < ti)
				fio.out('\n');
			if (testid) {
				tid << "Case #" << ti << ": ";
				fio.out(tid.str());
				tid.str("");
			}
			out();
		}
	}
#undef ioend
} gkd(0, 0, 0);

int main()
{
	return 0;
}
