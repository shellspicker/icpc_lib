#ifndef RAND_H
#define RAND_H 1

template<typename tp, class twist = mt19937_64>
class random_int {
	using dist = uniform_int_distribution<tp>;
	using param_type = typename dist::param_type;
	dist segment;
	twist gen{random_device{}()};
public:
	void set(tp l, tp r) {
		segment.param(param_type{l, r});
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
template<typename tp, class twist = mt19937_64>
class random_real {
	using dist = uniform_real_distribution<tp>;
	using param_type = typename dist::param_type;
	dist segment;
	twist gen{random_device{}()};
public:
	void set(tp l, tp r) {
		segment.param(param_type{l, r});
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

#endif
