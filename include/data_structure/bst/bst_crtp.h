#pragma once

#include "data_structure/allocator.h"
#include "data_structure/base.h"

namespace bst {

namespace node {

namespace detail {

template<class derived>
struct father {
	derived *fa;
};

template<class derived>
struct child {
	derived *ch[2];
};

template<class derived, typename key_t, class ...base>
struct impl : arg1s<derived, crtp, ptr_base>, base... {
	using key_type = key_t;
	key_t key;
	int size;
	impl() {
		this->ch[0] = this->ch[1] = this->null;
		if constexpr (has_fa())
			this->fa = this->null;
		size = 1;
	}
	impl(key_t k) : impl() {
		key = k;
	}
	static constexpr bool has_fa() {
		return is_base_of_v<father<derived>, impl<derived, key_t, base...>>;
	}
	derived *pull() {
		size = this->ch[0]->size + this->ch[1]->size + 1;
		this->self().pull_impl();
		return &this->self();
	}
	void pull_impl() {}
};

}

template<class node, typename key_t, bool has_fa>
using type =
	conditional_t<
		has_fa,
		detail::impl<node, key_t, detail::child<node>, detail::father<node>>,
		detail::impl<node, key_t, detail::child<node>>
	>;

}

namespace util {

template<class node>
node *min(node *t) {
	if (!*t)
		return t;
	while (*t->ch[0])
		t = t->ch[0];
	return t;
}

template<class node>
node *max(node *t) {
	if (!*t)
		return t;
	while (*t->ch[1])
		t = t->ch[1];
	return t;
}

template<class node>
node *link(node *u, bool d, node *v) {
	u->ch[d] = v;
	if constexpr (node::has_fa())
		v->fa = u;
	return u;
}

// d方向的子结点旋转上来.
template<class node>
void rotate(node *&t, int d) {
	[[maybe_unused]] node *k = t->ch[d], *ac;
	if constexpr (node::has_fa())
		ac = t->fa;
	link(t, d, k->ch[d ^ 1])->pull();
	link(k, d ^ 1, t);
	if constexpr (node::has_fa())
		link(ac, ac->ch[1] == t, k);
	t = k;
}

}

namespace func {

template<class node>
class impl {
	vector<node *> chain;
protected:
	using key_t = typename node::key_type;
	node *kth(node *o, int k, bool d) {
		if (!inrange(k, 1, o->size))
			return node::null;
		while (*o) {
			int s = o->ch[d]->size + 1;
			if (k == s)
				return o;
			bool ok = s < k;
			o = o->ch[d ^ ok];
			if (ok)
				k -= s;
		}
		return node::null;
	}
	/*
	 * 前驱后继, 需要父结点.
	 * d: 0为前驱, 1为后继.
	 */
	node *order(node *o, bool d) {
		if (*o->ch[d]) {
			o = o->ch[d];
			while (*o->ch[d ^ 1])
				o = o->ch[d ^ 1];
			return o;
		}
		node *last;
		if constexpr (node::has_fa()) {
			do {
				o = (last = o)->fa;
			} while (*o && o->ch[d ^ 1] != last);
		} else {
			last = o;
			this->chain.pop_back();
			while (!this->chain.empty() && this->chain.back()->ch[d ^ 1] != last) {
				last = this->chain.back();
				this->chain.pop_back();
			}
			o = this->chain.empty() ? node::null : this->chain.back();
		}
		return o;
	}
	/*
	 * 二分系列其实平衡树只能找到[)端点, 因为只能向下走,
	 * 最后端点都会往右边超界.
	 * 如果返回排名的话, 对应ans得到的是[), ans-1得到的是(].
	 * 类似的还有直接返回对应结点, so, 能返回的信息有<rank, node*>.
	 * 参数和原理类比数组版本的二分, (d, contain).
	 * 增加一个fuzzy参数, 模糊查找, 本来是给splay用的, 不过现在没有调用了, 可以删掉.
	 */
	pair<int, node *> search(node *o, key_t x, bool d, bool contain, bool fuzzy = 0) {
#define dwn(cond) \
		if ((cond)) ans += o->ch[0]->size + 1, o = o->ch[lastdir = 1];\
		else o = o->ch[lastdir = 0]
		int ans = 1;// 从1开始标号.
		node *last = node::null;
		bool lastdir;
		if (!*o)
			return {-1, node::null};
		while (*o) {
			if constexpr (!node::has_fa())
				this->chain.push_back(o);
			last = o;
			dwn((!d && o->key < x) || (d && !(x < o->key)));
		}
		ans = d ^ contain ? ans : ans - 1;
		o = d ^ contain ^ lastdir ? last : order(last, lastdir);
		if (fuzzy && o->key != x)
			o = last;
		if constexpr (!node::has_fa())
			this->chain.clear();
		return {ans, o};
#undef dwn
	}
};

}

}

