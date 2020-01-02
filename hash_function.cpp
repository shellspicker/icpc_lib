#include <bits/stdc++.h>

template<typename tp>
void combine(size_t &seed, const tp &x)
{
	seed ^= std::hash<tp>()(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

void hash_val(size_t &seed) {}

template<typename tp, typename ...other>
void hash_val(size_t &seed, tp &val, const other &...args)
{
	combine(seed, val);
	hash_val(seed, args...);
}

template<typename ...tp>
size_t hash_val(const tp &...args)
{
	size_t seed = 0;
	hash_val(seed, args...);
	return seed;
}

template<typename tp>
size_t hash_val(const std::vector<tp> &vec)
{
	size_t seed = 0;
	for (auto x : vec) {
		combine(seed, x);
	}
	return seed;
};

int main()
{
	size_t hs = -1;
	printf("hs: %lu\n", hs);
	std::vector<int> vec = {1, 2, 3, 4, 5};
	printf("hs: %lu\n", hash_val(vec));
	printf("hs: %lu\n", hash_val(1, 2, 3, 4, 5));
	return 0;
}
