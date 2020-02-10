#ifndef HASH_H
#define HASH_H 1

/*
 * normal hash.
 */
template<typename tp>
void combine(size_t &seed, const tp &x)
{
	seed ^= hash<tp>()(x) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}
void hash_val(size_t &seed) {}
template<typename tp, typename ...var>
void hash_val(size_t &seed, tp &val, var &&...args)
{
	combine(seed, val);
	hash_val(seed, forward<var>(args)...);
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
	hash_val(seed, forward<var>(args)...);
	return seed;
}
/*
 * bkdr hash.
 */
void bkdr_hash_preprocess(const string &seq, vector<ull> &hash, ull seed, int i = 0)
{
	if (hash.size() < i + seq.size())
		hash.resize(i + seq.size());
	for (auto h : seq)
		hash[i] = presum_point(hash, i - 1) * seed + h;
}
template<typename tp>
void bkdr_hash_preprocess(const vector<tp> &seq, vector<ull> &hash, ull seed, int i = 0)
{
	if (hash.size() < i + seq.size())
		hash.resize(i + seq.size());
	for (auto h : seq)
		hash[i] = presum_point(hash, i - 1) * seed + h;
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
	return hash[r] - presum_point(hash, l - 1) * exp[length(l, r)];
}

#endif
