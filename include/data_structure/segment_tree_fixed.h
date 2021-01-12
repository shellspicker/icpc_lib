int seg_id(int l, int r) { return l + r - (l != r && length(l, r) & 1); }

template<typename info, typename oper>
struct segment_tree_node {
public:
	typedef info info_t;
	typedef oper oper_t;
	info meta;
	segment_tree_node() {}
	segment_tree_node(info _1) : meta(_1) {}
};

template<typename node>
class segment_tree_base {
	typedef typename node::info_t info;
	typedef typename node::oper_t oper;
	pair<int, int> seg;
	node null;
protected:
	vector<node> mem;
	virtual void release(int, int, const oper &) {}
	virtual void push(int l, int r) {}
	virtual node pull(const node &, const node &) {}
public:
	segment_tree_base() {}
	/*
	 * [l, r]: -> [l + l, r + r].
	 * cnt = 2 * length(l, r) - 1.
	 * support idx start 0 or 1.
	 */
	void init(int l, int r) {
		seg = {l, r};
		mem.resize(2 * length(l, r) + 1);
		null = node();
	}
	void build(function<info(int)> point) {
		function<node &(int, int)> helper = [&](int l, int r) -> node & {
			int idx = seg_id(l, r);
			node &o = mem[idx];
			if (l == r) {
				o = node(point(l));
			} else {
				int m = midpoint(l, r);
				o = pull(helper(l, m - 1), helper(m, r));
			}
			return o;
		};
		helper(seg.first, seg.second);
	}
	void update(int ql, int qr, oper &op) {
		function<node &(int, int)> helper = [&](int l, int r) -> node & {
			int len;
			tie(len, ignore) = range_ins(l, r, ql, qr);
			node &o = mem[seg_id(l, r)];
			if (!len)
				return o;
			if (len == length(l, r)) {
				release(l, r, op);
			} else {
				int m = midpoint(l, r);
				push(l, r);
				o = pull(helper(l, m - 1), helper(m, r));
			}
			return o;
		};
		helper(seg.first, seg.second);
	}
	node query(int ql, int qr) {
		function<node(int, int)> helper = [&](int l, int r) -> node {
			int len;
			tie(len, ignore) = range_ins(l, r, ql, qr);
			node &o = mem[seg_id(l, r)], ret;
			if (!len) {
				ret = null;
			} else {
				if (len == length(l, r)) {
					ret = o;
				} else {
					int m = midpoint(l, r);
					push(l, r);
					ret = pull(helper(l, m - 1), helper(m, r));
					o = pull(mem[seg_id(l, m - 1)], mem[seg_id(m, r)]);
				}
			}
			return ret;
		};
		return helper(seg.first, seg.second);
	}
};

