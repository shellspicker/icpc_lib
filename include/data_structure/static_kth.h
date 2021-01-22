#pragma once

class blkid {
public:
	int chunk, count;
	vector<int> idx, lef, rig;
	struct info {
		int idx, lef, rig;
	};
	void init(int n, int bsz) {
		chunk = max(1, bsz);
		count = div_roundup(n, chunk);
		idx.resize(n);
		lef.resize(count);
		rig.resize(count);
		fup_range (i, 0, n)
			idx[i] = i / chunk;
		fup_range (i, 0, count) {
			lef[i] = i * chunk;
			rig[i] = lef[i] + chunk - 1;
		}
	}
	info get_info(int i) {
		return {i = idx[i], lef[i], rig[i]};
	}
};

template<typename tp>
class static_kth {
	blkid bid;
	vector<vector<tp>> blk;
	vector<tp> origin, seq;
public:
	void init(vector<tp> &data) {
		int sz;
		origin.assign(it_each(data));
		seq.assign(it_each(data));
		sort(it_each(seq));
		sz = data.size();
		bid.init(sz, sqrt(sz * log2(sz)));
		blk.resize(bid.count);
		fup (bi, 1, bid.count - 1) {
			blk[bi].clear();
			fup (i, bid.lef[bi], bid.rig[bi])
				blk[bi].push_back(data[i]);
			sort(blk[bi].begin(), blk[bi].end());
		}
	}
	tp kth(int l, int r, int k) {
		auto lt_count = [&](int ql, int qr, tp x) {
			int ret;
			blkid::info info[2];
			ret = 0;
			info[0] = bid.get_info(ql);
			info[1] = bid.get_info(qr);
			while (ql <= qr && ql <= info[0].rig)
				if (origin[ql++] < x)
					ret++;
			while (ql <= qr && info[1].lef <= qr)
				if (origin[qr--] < x)
					ret++;
			fup (bi, info[0].idx + 1, info[1].idx - 1)
				ret += lower_bound(it_each(blk[bi]), x) - blk[bi].begin();
			return ret;
		};
		int lef, rig, mid;
		lef = 0;
		rig = seq.size() - 1;
		while (lef <= rig) {
			mid = midpoint(lef, rig);
			if (lt_count(l, r, seq[mid]) < k)
				lef = mid + 1;
			else
				rig = mid - 1;
		}
		return seq[rig];
	}
};
