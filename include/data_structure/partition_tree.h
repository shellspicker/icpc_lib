template<typename vtp>
struct partition_tree_node {
	using value_type = vtp;
	static partition_tree_node<vtp> *null;
	partition_tree_node<vtp> *ls, *rs;
	int lef, rig;
	vector<vtp> data, tolef;
	partition_tree_node() {
		ls = rs = null;
	}
	partition_tree_node(int l, int r) {
		new (this) partition_tree_node();
		lef = l;
		rig = r;
	}
};
template<typename _1>
partition_tree_node<_1> *partition_tree_node<_1>::null;

template<typename vtp, size_t pon>
class partition_tree {
public:
	using node = partition_tree_node<vtp>;
	allocator<node, pon * 2> alloc;
	node *root, *&null = node::null;
	void build(vector<vtp> &v) {
		vector<vtp> part, sorted;
		auto init = [&]() {
			alloc.clear();
			null = new (alloc()) node();
			root = null;
			part.assign(it_each(v));
			sorted.assign(it_each(v));
			sort(it_each(sorted));
		};
		function<void(node *&, int, int)> helper = [&](node *&o, int l, int r) {
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
				helper(o->ls, l, mid - 1);
				helper(o->rs, mid, r);
			}
		};
		init();
		helper(root, 0, part.size() - 1);
	}
	vtp kth(int l, int r, int k) {
		vtp ret;
		node *o = root;
		int pre_l, pre_r, mid_l, mid_r;
		while (o->lef < o->rig) {
			pre_l = special(0, o->tolef, l - o->lef - 1);
			pre_r = length(o->lef, l - 1) - pre_l;
			mid_l = o->tolef[r - o->lef] - pre_l;
			mid_r = length(l, r) - mid_l;
			if (k <= mid_l) {
				o = o->ls;
				l = o->lef + pre_l;
				r = l + mid_l - 1;
			} else {
				o = o->rs;
				l = o->lef + pre_r;
				r = l + mid_r - 1;
				k -= mid_l;
			}
		}
		ret = o->data[0];
		return ret;
	}
};

