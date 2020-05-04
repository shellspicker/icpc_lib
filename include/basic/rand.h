#ifndef RAND_H
#define RAND_H 1

/*
 * 随机数生成器, 整数版本.
 */
template<typename tp, class twist = mt19937_64>
class random_int {
	using dist = uniform_int_distribution<tp>;
	dist segment;
	twist gen{random_device{}()};
public:
	void set(tp l, tp r) {
		new (&segment) dist{l, r};
	}
	pair<tp, tp> get() {
		assert(segment.a() == segment.min());
		assert(segment.b() == segment.max());
		return {segment.a(), segment.b()};
	}
	tp operator ()() {
		return segment(gen);
	}
};
/*
 * 随机数生成器, 浮点数版本.
 */
template<typename tp, class twist = mt19937_64>
class random_real {
	using dist = uniform_real_distribution<tp>;
	dist segment;
	twist gen{random_device{}()};
public:
	void set(tp l, tp r) {
		new (&segment) dist{l, r};
	}
	pair<tp, tp> get() {
		assert(segment.a() == segment.min());
		assert(segment.b() == segment.max());
		return {segment.a(), segment.b()};
	}
	tp operator ()() {
		return segment(gen);
	}
};
/*
 * 随机字符串生成器.
 *
 * 现在还很简单, 只开启了小写字母随机.
 */
class random_string {
	random_int<int> rd_numer, rd_lower, rd_upper;
public:
	random_string() {
		rd_lower.set('a', 'z');
		rd_upper.set('A', 'Z');
		rd_numer.set('0', '9');
	}
	string ref;
	void rand_len(int len) {
		ref.clear();
		ref.resize(len);
		fup_range (i, 0, len)
			ref[i] = rd_lower();
	}
	void repeat(int time) {
		time--;
		string tmp(ref);
		fup_range (t, 0, time)
			ref += tmp;
	}
	void cycle(int cyc, int len) {
		assert(len / cyc * cyc == len);
		int rep = len / cyc;
		rand_len(cyc);
		repeat(rep);
	}
	void swap(int pos) {
		string tmp(ref);
		ref = tmp.substr(pos) + tmp.substr(0, pos);
	}
};

#endif
