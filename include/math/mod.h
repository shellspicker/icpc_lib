ull mul_mod(ull a, ull b, ull mod)
{
	ull res = (a * b - (ll)(a / (ldb)mod * b + 1e-3) * mod + mod) % mod;
	return res;
}
ll pow_mod(ll x, ll n, ll mod)
{
	if (mod == 1)
		return 0;
	ll res = 1;
	while (n > 0) {
		if (n & 1)
			res = mul_mod(res, x, mod);
		x = mul_mod(x, x, mod);
		n >>= 1;
	}
	return res;
}
class modulo {
	ll x;
public:
	static ll mod;
	modulo() : x(0) {}
	modulo(ll v) : x(v) {
		if (mod <= llabs(x))
			x %= mod;
		if (x < 0)
			x += mod;
	}
	operator ll() const { return x; }
	modulo operator +(const modulo &y) const { return x + y; }
	modulo operator -(const modulo &y) const { return x - y; }
	modulo operator *(const modulo &y) const { return mul_mod(x, y, mod); }
	modulo operator /(const modulo &y) const { return *this * y.inverse(); }
	modulo operator ^(const modulo &y) const { return pow_mod(x, y, mod); }
	modulo operator +=(const modulo &y) { *this = *this + y; return *this; }
	modulo operator -=(const modulo &y) { *this = *this - y; return *this; }
	modulo operator *=(const modulo &y) { *this = *this * y; return *this; }
	modulo operator /=(const modulo &y) { *this = *this / y; return *this; }
	modulo operator -() const { return -x; }
	modulo operator =(const ll &y) { x = y; return *this; }
	modulo operator ++() { return ++x; }
	modulo operator ++(int) { return x++; }
	modulo operator --() { return --x; }
	modulo operator --(int) { return x--; }
	modulo inverse() const { return mod_inv(x, mod); }
	bool operator ==(const modulo &y) const { return x == y; }
	bool operator !=(const modulo &y) const { return x != y; }
	bool operator <(const modulo &y) const { return x < y; }
	bool operator <=(const modulo &y) const { return x <= y; }
	bool operator >(const modulo &y) const { return x > y; }
	bool operator >=(const modulo &y) const { return x >= y; }
};
ll modulo::mod;

