#if 201103L <= __cplusplus
template<typename tp>
class zip_vector {
	int tot;
	vector<int> dim;
public:
	vector<tp> data;
	zip_vector(const vector<int> &v) {
		dim = v;
		tot = 1;
		fwn_range (i, 0, dim.size()) {
			int suf = tot;
			tot *= dim[i];
			dim[i] = suf;
		}
		data.resize(tot);
	}
	template<typename ...var>
	tp &operator ()(var &&...args) {
		return data[index(args...)];
	}
	tp &operator [](int i) {
		return data[i];
	}
	size_t size() { return tot; }
	template<typename ...var>
	int index(var &&...args) {
		assert(sizeof...(args) == dim.size());
		int idx = 0;
		auto it = dim.begin();
		auto product = [&](int val) {
			idx += *it++ * val;
		};
		initializer_list<int>{(product(forward<var>(args)), 0)...};
		return idx;
	}
	vector<tp> dimension(int idx) {
		assert(inrange(idx, 0, tot - 1));
		vector<tp> ret(dim.size());
		fup (i, 0, ret.size() - 1) {
			ret[i] = idx / dim[i];
			idx -= ret[i] * dim[i];
		}
		return ret;
	}
};

template<typename tp>
class zip_valarray {
	int tot;
	valarray<int> dim;
public:
	valarray<tp> data;
	zip_valarray(const vector<int> &v) {
		dim = v;
		tot = 1;
		fwn_range (i, 0, dim.size()) {
			int suf = tot;
			tot *= dim[i];
			dim[i] = suf;
		}
		data.resize(tot);
	}
	template<typename ...var>
	tp &operator ()(var &&...args) {
		return data[index(args...)];
	}
	tp &operator [](int i) {
		return data[i];
	}
	size_t size() { return tot; }
	template<typename ...var>
	int index(var &&...args) {
		assert(sizeof...(args) == dim.size());
		int idx = 0;
		auto it = begin(dim);
		auto product = [&](int val) {
			idx += *it++ * val;
		};
		initializer_list<int>{(product(forward<var>(args)), 0)...};
		return idx;
	}
	vector<tp> dimension(int idx) {
		assert(inrange(idx, 0, tot - 1));
		vector<tp> ret(dim.size());
		fup (i, 0, ret.size() - 1) {
			ret[i] = idx / dim[i];
			idx -= ret[i] * dim[i];
		}
		return ret;
	}
};
#endif

