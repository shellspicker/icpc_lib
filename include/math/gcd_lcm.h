#ifndef GCD_LCM_H
#define GCD_LCM_H 1

ll gcd(ll a, ll b) { while (b) { a %= b; swap(a, b); } return a; }
ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

#endif
