#pragma once

#ifdef SUB_QUERY
template<typename _1, typename _2, typename _3>
#else
template<typename _1, typename _2>
#endif
struct segment_tree_node {
	using meta_t = _1;
	using op_t = _2;
#ifdef SUB_QUERY
	using sbq_t = _3;
#endif
	segment_tree_node *ls, *rs;
	int lef, rig;
	meta_t meta;
	segment_tree_node() {};
	segment_tree_node(int l, int r) : lef(l), rig(r) {}
	virtual void release(op_t *) {}
	virtual void push() {}
	virtual void pull() {}
#ifdef SUB_QUERY
	virtual void pull(sbq_t *) {}
#endif
};

template<class node, size_t pon>
class segment_tree {
public:
	using meta_t = typename node::meta_t;
	using op_t = typename node::op_t;
#if SUB_QUERY
	using sbq_t = typename node::sbq_t;
#endif
#if PERSISTENT
	using alloc_node_t = allocator<node, pon * (2 + size_t(log2(pon)) * 2)>;
#else
	using alloc_node_t = allocator<node, pon * 2>;
#endif
	using alloc_query_t = allocator<node, pon * 2>;
	static alloc_node_t alloc;
	static alloc_query_t alloc_query;
	static node *&null;
	using fn_point = function<meta_t(int)>;
	static fn_point point;
	static void init() {
		alloc.clear();
		alloc_query.clear();
		null = new (alloc()) node();
		null->ls = null->rs = null;
	}
	static void set_point(fn_point fp) {
		point = fp;
	}
	segment_tree() {}
	node *root;
	void build(int l, int r) {
		function<void(node *&, int, int)> helper = [&](node *&o, int l, int r) {
			o = new (alloc()) node(l, r);
			if (l == r) {
				o->meta = point(l);
			} else {
				int mid = midpoint(l, r);
				helper((node *&)o->ls, l, mid - 1);
				helper((node *&)o->rs, mid, r);
				o->pull();
			}
		};
		helper(root, l, r);
	}
	void update(int ql, int qr, op_t *otp) {
		function<void(node *)> helper = [&](node *o) {
			int len;
			tie(len, ignore) = range_ins(o->lef, o->rig, ql, qr);
			if (len == 0)
				return;
			if (len == length(o->lef, o->rig)) {
				o->release(otp);
			} else {
				o->push();
				helper((node *)o->ls);
				helper((node *)o->rs);
				o->pull();
			}
		};
		helper(root);
	}
#if PERSISTENT
	void update(node *pre, int ql, int qr, op_t *otp) {
		function<void(node *, node *&)> helper = [&](node *pre, node *&now) {
			int len;
			tie(len, ignore) = range_ins(pre->lef, pre->rig, ql, qr);
			if (len == 0) {
				now = pre;
				return;
			} else {
				now = new (alloc()) node();
				if (len == length(pre->lef, pre->rig)) {
					*now = *pre;
					now->release(otp);
				} else {
					pre->push();// now or pre ?
					*now = *pre;
					helper((node *)pre->ls, (node *&)now->ls);
					helper((node *)pre->rs, (node *&)now->rs);
					now->pull();
				}
			}
		};
		helper(pre, root);
	}
#endif
#ifdef SUB_QUERY
	node query(int ql, int qr, sbq_t *sbq)
#else
	node query(int ql, int qr)
#endif
	{
		function<node *(node *)> helper = [&](node *o) {
			int len;
			tie(len, ignore) = range_ins(o->lef, o->rig, ql, qr);
			node *ret;
			if (!len) {
				ret = null;
			} else {
				if (len == length(o->lef, o->rig)) {
					ret = o;
				} else {
					ret = new (alloc_query()) node();
					o->push();
					ret->ls = helper((node *)o->ls);
					ret->rs = helper((node *)o->rs);
#ifdef SUB_QUERY
					if (!sbq)
						ret->pull();
#else
					ret->pull();
#endif
				}
			}
#ifdef SUB_QUERY
			if (sbq)
				ret->pull(sbq);
#endif
			return ret;
		};
		node ret = *helper(root);
		alloc_query.clear();
		return ret;
	}
#if PERSISTENT
	node query_cnt(node *pre, int cnt) {
		node *nd[2] = {pre, root};
		int cc;
		assert(inrange(cnt, 1, nd[1]->meta.sum - nd[0]->meta.sum));
		while (nd[0]->lef < nd[0]->rig) {
			cc = nd[1]->ls->meta.sum - nd[0]->ls->meta.sum;
			assert(0 <= cc);
			if (cnt <= cc) {
				fup_range (i, 0, 2)
					nd[i] = (node *)nd[i]->ls;
			} else {
				fup_range (i, 0, 2)
					nd[i] = (node *)nd[i]->rs;
				cnt -= cc;
			}
		}
		return *nd[0];
	}
#endif
};
template<class _1, size_t _2>
typename segment_tree<_1, _2>::alloc_node_t segment_tree<_1, _2>::alloc;
template<class _1, size_t _2>
typename segment_tree<_1, _2>::alloc_query_t segment_tree<_1, _2>::alloc_query;
template<class _1, size_t _2>
_1 *&segment_tree<_1, _2>::null = _1::null;
template<class _1, size_t _2>
typename segment_tree<_1, _2>::fn_point segment_tree<_1, _2>::point;

#undef SUB_QUERY
#undef PERSISTENT
