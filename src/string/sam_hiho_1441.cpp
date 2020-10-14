#define FAST_IO 1
#include "template.h"
#define END_POS 1
#include "string/sam.h"

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	function<int(char)> sam_idx = [=](char ch) {
		return ch - 'a';
	};
	sam<88, 26> dsm{sam_idx};
	string text;
	int n_query;
	vector<string> v_que;
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(text));
		fio.in(n_query);
		v_que.resize(n_query);
		fup_range (i, 0, v_que.size())
			fio.in(v_que[i]);
		ioend(1);
		return cin;
	}
	void deal() {
		dsm.build(text);
	}
	void out() {
		fup_range (i, 0, v_que.size()) {
			auto fd = dsm.find(v_que[i]);
			fio.msg(
				"%s %s ",
				text.substr(rtol(fd->endpos[0], fd->m1), fd->m1).data(),
				text.substr(rtol(fd->endpos[0], fd->m2), fd->m2).data());
			fup_range (i, 0, fd->endpos.size())
				fio.msg("%d%c", fd->endpos[i] + 1, " \n"[i == fd->endpos.size() - 1]);
		}
	}
public:
	task(
		bool multicase = 0,
		const char *fmt_case = 0,
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
			if (fmt_case)
				fio.msg(fmt_case, ti);
			out();
		}
	}
#undef ioend
} gkd;

int main()
{
	return 0;
}
