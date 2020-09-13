#pragma once

#pragma message \
usage_begin("allocator.h") \
line("template<tp, pon>") \
line("tp: 分配类型.") \
line("pon: 预留空间大小.") \
line("\t可以非常大, 只有使用到的才会分配内存.") \
usage_end()

template<typename tp, size_t pon>
class allocator {
	size_t cur;
	vector<tp> mem;
	queue<tp *> cache;
public:
	allocator() {
		cur = 0;
		mem.reserve(pon);
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
	void clear() {
		cur = 0;
		while (!cache.empty())
			cache.pop();
	}
	int size() { return cur; }
};
