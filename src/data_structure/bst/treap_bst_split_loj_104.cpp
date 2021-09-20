#define FAST_IO 1
#include "template.h"
#include "data_structure/bst/treap_crtp.h"

class task {
	struct query {
		int op, x;
	};
	vector<query> qa;
	vector<int> ans;
	struct node : baseinfo<treap::node::type<node, int, 0>> {
		using base::base;
	};
	class tree : public
				baseinfos<
					bst::func::impl<node>,
					treap::func::bst::split_impl<tree, node>,
					treap::root::single<node, greater>
				> {
	public:
		void insert(int k) {
			base::insert(root, k);
		}
		void remove(int k) {
			base::remove(root, k);
		}
		node *kth(int k, int d) {
			return base::kth(root, k, d);
		}
		pair<int, node *> search(int k, bool d, bool contain) {
			return base::search(root, k, d, contain);
		}
	} dsm;
	void preprocess() {
		fio.set_output_float_digit(12);
		dsm.resize(100233);
	}
	istream &in() {
#define ioend(cond) \
		do {\
			if (!(cond) || !fio.ok()) { cin.setstate(ios_base::badbit); return cin; }\
		} while(0)
		int qn;
		ioend(fio.in(qn));
		qa.resize(qn);
		for (auto &q : qa)
			fio.in(q.op, q.x);
		ioend(1);
		return cin;
#undef ioend
	}
	void deal() {
		ans.clear();
		dsm.init();
		for (auto q : qa) {
			switch (q.op) {
				case 1: {
					dsm.insert(q.x);
					break;
				}
				case 2: {
					dsm.remove(q.x);
					break;
				}
				case 3: {
					auto fd = dsm.search(q.x, 0, 1);
					ans.emplace_back(fd.first);
					break;
				}
				case 4: {
					auto fd = dsm.kth(q.x, 0);
					ans.emplace_back(fd->key);
					break;
				}
				case 5: {
					auto fd = dsm.search(q.x, 0, 0);
					ans.emplace_back(fd.second->key);
					break;
				}
				case 6: {
					auto fd = dsm.search(q.x, 1, 0);
					ans.emplace_back(fd.second->key);
					break;
				}
			}
		}
	}
	void out() {
		for (auto x : ans)
			fio.msg("%d\n", x);
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
