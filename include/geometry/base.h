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
		acos(dot(r) / len() / r.len());
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

/*
struct segment {
	pov a, b;
	segment() {}
	segment(pov _1, pov _2) : a(_1), b(_2) {}

	bool internal(const pov &r) {
	}
	double distance(const pov &r) {
	}
	pov projection(const pov &r) {
	}
	bool intersection(const segment &r) {
	}
};

struct line {
	pov p, v;
	line() {}
	line(pov _1, pov _2) : p(_1), v(_2) {}

	double distance(const pov &r) {
	}
	pov projection(const pov &r) {
	}
	pov intersection(const line &r) {
		pov u = p - r.p;
		double t = r.v.cross(u) / v.cross(r.p);
		return p + v * t;
	}
};
*/
