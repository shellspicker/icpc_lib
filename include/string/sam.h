#pragma once

#include "data_structure/allocator.h"

#pragma message \
usage_begin("后缀自动机") \
line("END_POS") \
line("\tendpos列表: vector<int> node::endpos") \
line("VISIT") \
line("\t结点访问标记: bool node::vis") \
line("DEBUG") \
line("\t结点详细信息输出: void debug()") \
line("\tVISIT: 1") \
usage_end()

#if DEBUG
#  if !VISIT
#    define VISIT 1
#  endif
#endif

template<size_t pon, size_t sigma>
class sam {
public:
	struct node {
		static node *null;
		node *fa, *nxt[sigma];
		int m1, m2;
#if END_POS
		vector<int> endpos;
#endif
#if VISIT
		bool vis;
#endif
		node(int val = 0) {
			fa = null;
			fup_range (i, 0, sigma)
				nxt[i] = null;
			m1 = 0;
			m2 = val;
#if END_POS
			endpos.clear();
#endif
#if VISIT
			vis = 0;
#endif
		}
#if DEBUG
		void prt(const string &origin) {
			fio.msg("\nnode info %d\n", this - null - 1);
			fio.msg("fa: %d\n", fa - null - 1);
			fup_range (i, 0, sigma)
				if (nxt[i] != null)
					fio.msg("nxt[%d]: %d\n", i, nxt[i] - null - 1);
			fio.msg("m1: %d, m2: %d\n", m1, m2);
			fio.msg("strings:\n");
#  if END_POS
			fup (len, m1, m2) {
				if (len) {
					fio.msg("%s\n", origin.substr(rtol(endpos[0], len), len).data());
				}
			}
			fio.msg("endpos: ");
			fup_range (i, 0, endpos.size())
				fio.msg("%d%c", endpos[i], " \n"[i == endpos.size() - 1]);
#  endif
		}
#endif
	};
private:
	node *root, *last, *&null = node::null;
	allocator<node, pon * 2> alloc;
	string origin;
	function<int(char)> idx;
	void init() {
		alloc.clear();
		null = new (alloc()) node(-1);
		root = new (alloc()) node(0);
		fup_range (i, 0, sigma)
			null->nxt[i] = root;
#if END_POS
		root->endpos.push_back(-1);
#endif
		last = root;
	}
	node *split_node(node *o, int val) {
		node *now = new (alloc()) node();
		*now = *o;
		now->m2 = val;
		return now;
	}
	void link(node *pre, node *now) {
		now->fa = pre;
		now->m1 = pre->m2 + 1;
	}
	void extend(int pos) {
		int ci = idx(origin[pos]);
		node *pre = last, *now = new (alloc()) node(last->m2 + 1);
		while (pre != null && pre->nxt[ci] == null) {
			pre->nxt[ci] = now;
			pre = pre->fa;
		}
		node *mid = pre->nxt[ci];
		if (pre->m2 + 1 == mid->m2) {
			link(mid, now);
		} else {
			node *split = split_node(mid, pre->m2 + 1);
			link(split, mid);
			link(split, now);
			while (pre != null && pre->nxt[ci] == mid) {
				pre->nxt[ci] = split;
				pre = pre->fa;
			}
		}
		last = now;
#if END_POS
		now->endpos.push_back(pos);
		now = now->fa;
		while (now != null) {
			now->endpos.push_back(pos);
			now = now->fa;
		}
#endif
	}
public:
	sam(decltype(idx) fp) : idx(fp) {}
	void build(const string &s) {
		init();
		origin.assign(it_each(s));
		fup_range (i, 0, s.size())
			extend(i);
	}
	node *find(const string &s) {
		node *now = root;
		fup_range (i, 0, s.size()) {
			int ci = idx(s[i]);
			if (now->nxt[ci] == null)
				return null;
			now = now->nxt[ci];
		}
		return now;
	}
#if DEBUG
	void debug() {
		fio.msg("\n%s\n", __func__);
		queue<node *> que;
		que.push(root);
		while (!que.empty()) {
			node *now = que.front();
			que.pop();
			if (now->vis)
				continue;
			now->vis = 1;
			now->prt(origin);
			fup_range (i, 0, sigma) if (now->nxt[i] != null) {
				node *nxt = now->nxt[i];
				if (nxt->vis)
					continue;
				que.push(nxt);
			}
		}
		fio.msg("%s over\n", __func__);
	}
#endif
	ll substr_cnt() {
		ll ret = 0;
		fup (i, 2, alloc.size() - 1) {
			node *now = null + i;
			ret += length(now->m1, now->m2);
		}
		return ret;
	}
};
template<size_t _1, size_t _2>
typename sam<_1, _2>::node *sam<_1, _2>::node::null;

#undef END_POS
#undef VISIT
#undef DEBUG
