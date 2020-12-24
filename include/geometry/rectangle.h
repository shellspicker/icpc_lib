struct rectangle {
	pov low, high;
	rectangle() {}
	rectangle(pov _1, pov _2) : low(_1), high(_2) {}

	double area() {
		pov diff = high - low;
		if (0 <= fcmp(diff.x) && 0 <= fcmp(diff.y))
			return diff.x * diff.y;
		return 0;
	}
	rectangle intersection(const rectangle &r) {
		return {
			pov(max(low.x, r.low.x), max(low.y, r.low.y)),
			pov(min(high.x, r.high.x), min(high.y, r.high.y))};
	}
};

