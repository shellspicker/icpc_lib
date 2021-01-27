template<typename tp>
class descrete {
	vector<tp> sorted;
public:
	void init(const vector<tp> &v) {
		sorted.assign(it_each(v));
		sort(it_each(sorted));
		sorted.erase(unique(it_each(sorted)), sorted.end());
	}
	void get_pos(vector<tp> &v) {
		for (auto &x : v)
			x = this->operator()(x);
	}
	int operator ()(tp x) {
		return lower_bound(it_each(sorted), x) - sorted.begin();
	}
	tp operator [](int i) {
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

