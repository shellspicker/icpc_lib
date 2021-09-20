#define FAST_IO 1
#include "template.h"
#include "data_structure/bst/splay_crtp.h"

class task {
	struct query {
		int l, r;
	};
	vector<query> qa;
	vector<int> ans;
	struct node : baseinfo<splay::node::tag_type<node, int, 1, fake_type>> {
		using base::base;
		bool rev = 0;
		void release_impl(const fake_type &arg) {
			swap(ch[0], ch[1]);
			rev ^= 1;
		}
		node *push_impl() {
			if (rev) {
				fake_type arg{};
				ch[0]->release(arg);
				ch[1]->release(arg);
				rev = 0;
			}
			return this;
		}
	};
	class tree : public
			baseinfos<
				bst::func::impl<node>,
				splay::func::basic::downtop<node>,
				splay::func::segment::impl<tree, node>,
				splay::root::single<node>
			> {
	public:
		void build(const vector<int> &v) {
			base::build_all(root, v);
		}
		void set_tag(int l, int r, const fake_type &arg) {
			base::set_tag(root, l, r, arg);
		}
		void visit(vector<int> &out) {
			out.clear();
			base::visit(root, out);
		}
	} dsm;
	void preprocess() {
		fio.set_output_float_digit(12);
		dsm.resize(100233);
	}
	istream &in() {
#define ioend(cond) \
		do {\
			if (!(cond)) { cin.setstate(ios_base::badbit); return cin; }\
		} while(0)
		int dn, qn;
		ioend(fio.in(dn, qn));
		ans.resize(dn);
		iota(it_each(ans), 1);
		qa.resize(qn);
		for (auto &q : qa)
			fio.in(q.l, q.r);
		ioend(1);
		return cin;
#undef ioend
	}
	void deal() {
		dsm.init();
		dsm.build(ans);
		for (auto q : qa) {
			dsm.set_tag(q.l, q.r, {});
		}
		dsm.visit(ans);
	}
	void out() {
		fup_range (i, 0, ans.size())
			fio.msg("%d%c", ans[i], " \n"[i == ans.size() - 1]);
	}
public:
	task(
		bool multicase = 0,
		const char *fmt_case = 0,
		bool blankline = 0) {
		static int testcase = 1 << 30;
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
};

int main()
{
	new task();
	return 0;
}
