#pragma once

void double_scale(vector<vector<int>> &ret) {
	int sz, xp;
	sz = ret[0].size();
	xp = half2xp(sz);
	ret.resize(xp + 1);
	fup (b, 1, xp) {
		ret[b].resize(sz);
		fup_range (s, 0, sz)
			ret[b][s] = special(-1, ret[b - 1], ret[b - 1][s]);
	}
}

vector<vector<int>> double_scale(const vector<int> &step) {
	vector<vector<int>> ret;
	ret.resize(1);
	ret[0].assign(it_each(step));
	double_scale(ret);
	return ret;
}
