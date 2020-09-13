#pragma once

template<typename tp>
class descrete {
	vector<tp> sorted;
public:
	void init(vector<tp> &v) {
		sorted.assign(it_each(v));
		sort(it_each(sorted));
		sorted.erase(unique(it_each(sorted)), sorted.end());
		for (auto &x : v)
			x = lower_bound(it_each(sorted), x) - sorted.begin();
	}
	tp get(int i) {
		return sorted[i];
	}
	int size() {
		return sorted.size();
	}
	tp min() {
		return sorted.front();
	}
	tp max() {
		return sorted.back();
	}
};
