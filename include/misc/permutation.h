#pragma once

template<typename iter>
vector<vector<it_vtp(iter)>> circulation(iter st, size_t len)
{
	using vtp = it_vtp(iter);
	vector<vector<vtp>> ret;
	vector<bool> vis(len);
	fup_range (x, 0, len) {
		if (!vis[x]) {
			ret.push_back(vector<vtp>());
			while (!vis[x]) {
				vis[x] = 1;
				ret.back().push_back(x);
				x = st[x];
			}
		}
	}
	return ret;
}
