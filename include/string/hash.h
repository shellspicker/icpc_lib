#pragma once

/*
 * normal hash.
 */
template<typename tp>
void combine(size_t &seed, const tp &x)
{
	seed ^= hash<tp>()(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
template<typename tp>
size_t hash_val(vector<tp> &&vec)
{
	size_t seed = 0;
	for (auto x : vec)
		combine(seed, x);
	return seed;
}
template<typename ...var>
size_t hash_val(var &&...args)
{
	size_t seed = 0;
	initializer_list<int>{(combine(seed, forward<var>(args)), 0)...};
	return seed;
}
/*
 * bkdr hash.
 */
void bkdr_hash_preprocess(const string &seq, vector<ull> &hash, ull seed, int i = 0)
{
	if (hash.size() < i + seq.size())
		hash.resize(i + seq.size());
	for (auto h : seq) {
		hash[i] = special(0llu, hash, i - 1, 0, hash.size() - 1) * seed + h;
		i++;
	}
}
template<typename tp>
void bkdr_hash_preprocess(const vector<tp> &seq, vector<ull> &hash, ull seed, int i = 0)
{
	if (hash.size() < i + seq.size())
		hash.resize(i + seq.size());
	for (auto h : seq) {
		hash[i] = special(0llu, hash, i - 1, 0, hash.size() - 1) * seed + h;
		i++;
	}
}
ull bkdr_hash_once(const string &seq, ull seed)
{
	ull hash = 0;
	for (auto h : seq)
		hash = hash * seed + h;
	return hash;
}
template<typename tp>
ull bkdr_hash_once(const vector<tp> &seq, ull seed)
{
	ull hash = 0;
	for (auto h : seq)
		hash = hash * seed + h;
	return hash;
}
ull bkdr_hash_range(const vector<ull> &hash, const vector<ull> &exp, int l, int r)
{
	return hash[r] - special(0llu, hash, l - 1, 0, hash.size() - 1) * exp[length(l, r)];
}
