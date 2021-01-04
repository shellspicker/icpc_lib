class bitwrap {
	int v;
public:
	bitwrap(int x = 0) : v(x) {}
	operator int() { return v; }
	bool set(size_t l) {
		bool ret = 1;
		int a = v;
		a |= 1 << l;
		if (a == v)
			ret = 0;
		v = a;
		return ret;
	}
	bool reset(size_t l) {
		bool ret = 1;
		int a = v;
		a &= ~(1 << l);
		if (a == v)
			ret = 0;
		v = a;
		return ret;
	}
	bool test(size_t l) {
		return v >> l & 1;
	}
};

class bitwrap_ll {
	ll v;
public:
	bitwrap_ll(ll x = 0) : v(x) {}
	operator int() { return v; }
	bool set(size_t l) {
		bool ret = 1;
		ll a = v;
		a |= 1ll << l;
		if (a == v)
			ret = 0;
		v = a;
		return ret;
	}
	bool reset(size_t l) {
		bool ret = 1;
		ll a = v;
		a &= ~(1ll << l);
		if (a == v)
			ret = 0;
		v = a;
		return ret;
	}
	bool test(size_t l) {
		return v >> l & 1;
	}
};

