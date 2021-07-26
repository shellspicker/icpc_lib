template<typename tp>
class allocator {
	size_t cur;
	vector<tp> mem;
	queue<tp *> cache;
public:
	allocator() {
		clear();
	}
	tp *operator ()() {
		tp *ret;
		if (cache.empty()) {
			if (mem.size() <= cur)
				mem.push_back(tp());
			ret = &mem[cur++];
		} else {
			ret = cache.front();
			cache.pop();
		}
		return ret;
	}
	void operator ()(tp *o) {
		cache.push(o);
	}
	void resize(size_t n) {
		mem.reserve(n);
	}
	void clear() {
		cur = 0;
		while (!cache.empty())
			cache.pop();
	}
	int size() { return cur; }
};

