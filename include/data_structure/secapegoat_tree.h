#ifndef SECAPEGOAT_TREE_H
#define SECAPEGOAT_TREE_H 1

#include "data_structure/bst.h"

/*
 * 替罪羊树.
 * 核心思想在rebuild, 暴力重构, 重构的条件可以微调, 和alpha有关.
 * 结点核心cover和exist, exist是删除的lazy tag,
 * cover表示虚拟结点(包括删除的点), size表示真实结点(不包括删除的点).
 * cover和size变量名可以换一下, 目前先这样表示.
 * 需要重写搜索树的行为, 所有查找到当前结点的判断, 需要加上exist判断.
 * 目前只简单写了kth和search, 和标准bst的查找行为(参数)有点偏差,
 * 之后看看能不能统一参数.
 * 现在是手动维护插入删除的结点变化, 没有调用pull.
 */
template<typename tp, size_t dsn, size_t pon>
class secapegoat : public bst<tp> {
private:
	static constexpr double alpha = 0.75;
	class node : public bst<tp>::node {
	public:
		static node *null;
		int cover;
		bool exist;
		// 附加信息
		//int val;// 模拟map用.
		node() {}
		node(node *f, tp k) : bst<tp>::node(f, k) {
			cover = exist = 1;
		}
		bool bad() {
			return (cover * alpha + 5 < ((node *)this->ls)->cover) ||
				(cover * alpha + 5 < ((node *)this->rs)->cover);
		}
		node *pull() {
			this->size = this->ls->size + this->rs->size + exist;
			this->cover = ((node *)this->ls)->cover + ((node *)this->rs)->cover + 1;
			return this;
		}
	};
	allocator<node, pon> alloc;
public:
	node *root[dsn], *&null = node::null;// null must be reference.
	void init() {
		alloc.clear();
		null = new (alloc()) node(null, -1);
		bst<tp>::null = null;
		null->size = null->cover = 0;
		fup (i, 0, dsn - 1)
			root[i] = null;
	}
	node *&operator ()(int idx) {
		return root[idx];
	}
	void rebuild(node *&o) {
		static vector<node *> v;
		function<void(node *)> visit = [&](node *o) {
			if (o == null)
				return;
			visit((node *)o->ls);
			if (o->exist) {
				v.emplace_back(o);
			} else {
				alloc(o);
			}
			visit((node *)o->rs);
		};
		function<void(node *&o, int l, int r)> divide = [&](node *&o, int l, int r) {
			if (length(l, r) == 0) {
				o = null;
				return;
			}
			int mid = midpoint(l, r);
			o = v[mid];
			divide((node *&)o->ls, l, mid - 1);
			divide((node *&)o->rs, mid + 1, r);
			o->pull();
		};
		v.clear();
		visit(o);
		divide(o, 0, v.size() - 1);
	}
	void insert(node *&o, tp x) {
		function<node **(node *&, tp)> helper =
		[&](node *&o, tp x) -> node** {
			node **ret;
			if (o == null) {
				o = new (alloc()) node(null, x);
				ret = &null;
			} else {
				bool d = o->key < x;// equal or not is don't care.
				o->size++, o->cover++;
				ret = help((node *&)o->ch[d], x);
				if (o->bad())
					ret = &o;
			}
			return ret;
		};
		node **fix = help(o, x);
		if (*fix != null)
			rebuild(*fix);
	}
	void remove(node *&o, tp x) {
		int k = search(o, x);
		function<void(node *, int)> help = [&](node *o, int k) -> void {
			while (o != null) {
				o->size--;
				int s = o->ls->size + o->exist;
				if (o->exist && k == s) {
					o->exist = 0;
					break;
				}
				bool ok = s < k;
				o = (node *)o->ch[ok];
				if (ok)
					k -= s;
			}
		};
		help(o, k);
		if (o->size < o->cover * alpha)
			rebuild(o);
	}
	node *kth(node *o, int k) {
		while (o != null) {
			int s = o->ls->size + o->exist;
			if (o->exist && k == s)
				return o;
			bool ok = s < k;
			o = (node *)o->ch[ok];
			if (ok)
				k -= s;
		}
		return null;
	}
	int search(node *o, tp x) {
#define dwn(cond) \
		if ((cond)) ans += o->ls->size + o->exist, o = (node *)o->rs;\
		else o = (node *)o->ls
		int ans = 1;// 从1开始标号.
		while (o != null) {
			dwn(o->key < x);
		}
		return ans;
#undef dwn
	}
};
template<typename tp, size_t dsn, size_t pon>
typename secapegoat<tp, dsn, pon>::node *secapegoat<tp, dsn, pon>::node::null;

#endif
