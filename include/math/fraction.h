/*
 * include:
 *   math/gcd_lcm.h
 */
struct fraction {
	ll num, den;
	fraction(ll _1 = 0, ll _2 = 1) : num(_1), den(_2) {
		if (den < 0) {
			num *= -1;
			den *= -1;
		}
		ll gg = gcd(num < 0 ? num * -1 : num, den);
		num /= gg;
		den /= gg;
	}
};

