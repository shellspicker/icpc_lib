#pragma once

double to_rad(double deg) {
	return deg * pi / 180.;
}
double to_deg(double rad) {
	return rad * 180. / pi;
}

struct pov {
	double x, y;
	pov() {}
	pov(double _1, double _2) : x(_1), y(_2) {}

	pov operator +(const pov &r) const {
		return pov(x + r.x, y + r.y);
	}
	pov operator -(const pov &r) const {
		return pov(x - r.x, y - r.y);
	}
	pov operator *(double r) const {
		return pov(x * r, y * r);
	}
	pov operator /(double r) const {
		return pov(x / r, y / r);
	}
	bool operator <(const pov &r) const {
		int ret[2] = {fcmp(x - r.x), fcmp(y - r.y)};
		if (!ret[0])
			return ret[1] < 0;
		return ret[0] < 0;
	}
	bool operator <=(const pov &r) const {
		return *this < r || *this == r;
	}
	bool operator ==(const pov &r) const {
		int ret[2] = {fcmp(x - r.x), fcmp(y - r.y)};
		return !ret[0] && !ret[1];
	}
	bool operator >(const pov &r) const {
		int ret[2] = {fcmp(x - r.x), fcmp(y - r.y)};
		if (!ret[0])
			return ret[1] > 0;
		return ret[0] > 0;
	}
	bool operator >=(const pov &r) const {
		return *this > r || *this == r;
	}

	double len() const {
		return sqrt(dot(*this));
	}
	double dot(const pov &r) const {
		return x * r.x + y * r.y;
	}
	double cross(const pov &r) const {
		return x * r.y - y * r.x;
	}
	double angle(const pov &r) {
		return acos(dot(r) / len() / r.len());
	}
	double area2(const pov &b, const pov &c) {
		return (b - *this).cross(c - *this);
	}
	pov rotate(double rad) {
		return pov(x * cos(rad) - y * sin(rad), x * sin(rad) + y * cos(rad));
	}
	pov norm() {
		double l = len();
		return pov(-y / l, x / l);
	}
};

struct segment {
	pov a, b;
	segment() {}
	segment(pov _1, pov _2) : a(_1), b(_2) {}

	bool internal(const pov &r) {
		return fcmp((a - r).cross(b - r)) == 0 && fcmp((a - r).dot(b - r)) < 0;
	}
	double distance(const pov &r) {
		if (a == b)
			return (r - a).len();
		pov v1 = b - a, v2 = r - a, v3 = r - b;
		if (fcmp(v1.dot(v2) < 0))
			return v2.len();
		if (0 < fcmp(v1.dot(v3)))
			return v3.len();
		return fabs(v1.cross(v2) / v1.len());
	}
	pov projection(const pov &r) {
		pov v = b - a;
		return a + v * (v.dot(r - a) / v.dot(v));
	}
	bool intersection(const segment &r) {
		pov u = r.a - a, v = r.b - b;
		double c1 = u.cross(b - a), c2 = u.cross(r.b - a),
			   c3 = v.cross(a - b), c4 = v.cross(r.a - b);
		return fcmp(c1) * fcmp(c2) < 0 && fcmp(c3) * fcmp(c4) < 0;
	}
};

struct ray {
	pov p, v;
	ray() {}
	ray(pov _1, pov _2) : p(_1), v(_2) {}

	double distance(const pov &r) {
		random_real<double> rd;
		rd.set(12, 345);
		pov e = p + v * rd();
		pov v1 = e - p, v2 = r - p;
		return fabs(v1.cross(v2) / v1.len());
	}
	pov projection(const pov &r) {
		return p + v * (v.dot(r - p) / v.dot(v));
	}
	pov intersection(const ray &r) {
		pov u = p - r.p;
		double t = r.v.cross(u) / v.cross(r.p);
		return p + v * t;
	}
};
