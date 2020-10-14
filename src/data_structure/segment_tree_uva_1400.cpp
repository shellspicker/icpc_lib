#define FAST_IO 1
#include "template.h"
struct subsection {
	int l, r;
	ll v;
	subsection() {}
	subsection(int l_, int r_, ll v_) : l(l_), r(r_), v(v_) {}
	subsection operator +(const subsection &rhs) const {
		subsection ret(l, rhs.r, v + rhs.v);
		return ret;
	}
	bool operator < (const subsection &rhs) const {
		if (v ^ rhs.v)
			return v < rhs.v;
		return make_pair(l, r) > make_pair(rhs.l, rhs.r);
	}
};
struct data_info {
	subsection all, pre, suf, sub;
	data_info() {}
	data_info(subsection a, subsection b, subsection c, subsection d) :
		all(a), pre(b), suf(c), sub(d) {}
};
struct update_info {
};
#include "data_structure/segment_tree.h"
template<typename data_tp, typename update_tp, size_t dsn, size_t pon>
void segment_tree<data_tp, update_tp, dsn, pon>::node::release(update_tp *upd) {
}
template<typename data_tp, typename update_tp, size_t dsn, size_t pon>
void segment_tree<data_tp, update_tp, dsn, pon>::node::push() {
}
template<typename data_tp, typename update_tp, size_t dsn, size_t pon>
void segment_tree<data_tp, update_tp, dsn, pon>::node::pull() {
	if (ls == null || rs == null) {
		data = ls == null ? rs->data : ls->data;
		return;
	}
	data.all = ls->data.all + rs->data.all;
	data.pre = max({ls->data.pre, ls->data.all + rs->data.pre});
	data.suf = max({rs->data.suf, ls->data.suf + rs->data.all});
	data.sub = max({ls->data.sub, rs->data.sub, ls->data.suf + rs->data.pre});
}

class task {
#define ioend(cond) \
	do {\
		if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
	} while(0)
	int n, q;
	struct command {
		int l, r;
		command() {}
		command(int l_, int r_) : l(l_), r(r_) {}
		finput(is, command, o) {
			fio.in(o.l, o.r);
			o.l--;
			o.r--;
			return is;
		}
	};
	vector<command> cmd, ans;
	vector<ll> data;
	function<data_info(int)> point = [=](int i) {
		subsection s(i, i, data[i]);
		return data_info{s, s, s, s};
	};
	segment_tree<data_info, update_info, 1, 500233> dsm{point};
	void preprocess() {
		fio.set_output_float_digit(12);
	}
	istream &in() {
		ioend(fio.in(n, q));
		data.resize(n);
		cmd.resize(q);
		fup_range (i, 0, n)
			fio.in(data[i]);
		fup_range (i, 0, q)
			cin >> cmd[i];
		ioend(1);
		return cin;
	}
	void deal() {
		dsm.build(0, 0, data.size() - 1);
		ans.clear();
		fup_range (i, 0, cmd.size()) {
			command c = cmd[i];
			auto fd = dsm.query(0, c.l, c.r);
			ans.push_back(command(fd.data.sub.l + 1, fd.data.sub.r + 1));
		}
	}
	void out() {
		fup_range (i, 0, ans.size())
			fio.msg("%d %d\n", ans[i].l, ans[i].r);
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
} gkd(0, "Case %d:\n");

int main()
{
	return 0;
}
