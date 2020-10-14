#pragma once

template<typename vtp, size_t pon>
class partition_tree {
public:
	class node {
	public:
		static node *null;
		node *ls, *rs;
		int lef, rig;
		vector<vtp> data, tolef;
		node() : lef(-1), rig(-1) {
			ls = rs = null;
		}
		node(int l, int r) : lef(l), rig(r) {}
	};
	allocator<node, pon * 2> alloc;
	node *root, *&null = node::null;
	vector<vtp> part, sorted;
	void init(vector<vtp> &v) {
		alloc.clear();
		null = new (alloc()) node();
		null->ls = null->rs = null;
		root = null;
		part.assign(it_each(v));
		sorted.assign(it_each(v));
		sort(it_each(sorted));
	}
	void build_helper(node *&o, int l, int r) {
		o = new (alloc()) node(l, r);
		o->data.assign(part.begin() + l, part.begin() + r + 1);
		if (l ^ r) {
			int mid, same, pos, cuti, cc;
			vtp cut;
			o->tolef.resize(length(l, r));
			mid = midpoint(l, r);
			cut = sorted[cuti = mid - 1];
			for (pos = cuti; 0 <= pos && sorted[pos] == cut; --pos);
			same = cuti - pos;
			cc = 0;
			fup (i, l, r) {
				if (part[i] < cut || (part[i] == cut && same)) {
					if (part[i] == cut)
						same--;
					cc++;
				}
				o->tolef[i - l] = cc;
			}
			stable_partition(part.begin() + l, part.begin() + r + 1, [=](vtp x) {
					return x <= cut;
					});
			build_helper(o->ls, l, mid - 1);
			build_helper(o->rs, mid, r);
		}
	}
	void build(vector<vtp> &v) {
		init(v);
		build_helper(root, 0, part.size() - 1);
	}
	vtp query_helper(node *o, int ql, int qr, int k) {
		vtp ret;
		int pre_l, pre_r, mid_l, mid_r;
		while (o->lef < o->rig) {
			pre_l = special(0, o->tolef, ql - o->lef - 1);
			pre_r = length(o->lef, ql - 1) - pre_l;
			mid_l = o->tolef[qr - o->lef] - pre_l;
			mid_r = length(ql, qr) - mid_l;
			if (k <= mid_l) {
				o = o->ls;
				ql = o->lef + pre_l;
				qr = ql + mid_l - 1;
			} else {
				o = o->rs;
				ql = o->lef + pre_r;
				qr = ql + mid_r - 1;
				k -= mid_l;
			}
		}
		ret = o->data[0];
		return ret;
	}
	vtp kth(int l, int r, int k) {
		return query_helper(root, l, r, k);
	}
};
template<typename vtp, size_t pon>
typename partition_tree<vtp, pon>::node *partition_tree<vtp, pon>::node::null;
