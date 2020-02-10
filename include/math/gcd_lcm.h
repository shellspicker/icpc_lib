#ifndef GCD_LCM_H
#define GCD_LCM_H 1

template<typename tp>
tp gcd(tp a, tp b) { while (b) { a %= b; swap(a, b); } return a; }
template<typename tp>
tp lcm(tp a, tp b) { return a / gcd(a, b) * b; }

#endif
