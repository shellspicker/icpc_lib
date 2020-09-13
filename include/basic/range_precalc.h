#pragma once

template<typename tp>
tp presum_range(const tp *sum, int len, int l, int r, int m1 = -1, int m2 = -1)
{
	if (!~m1 || !~m2)
		m1 = 0, m2 = len - 1;
	return sum[r] - special(0, sum, len, l - 1, m1, m2);
}
template<typename tp>
tp presum_range(const vector<tp> &sum, int l, int r, int m1 = -1, int m2 = -1)
{
	if (!~m1 || !~m2)
		m1 = 0, m2 = sum.size() - 1;
	return sum[r] - special(0, sum, l - 1, m1, m2);
}
template<typename tp>
void presum_preprocess(
						const tp *src, int l, int r,
						tp *dest, int len, int st, int m1 = -1, int m2 = -1)
{
	if (!~m1 || !~m2)
		m1 = 0, m2 = len - 1;
	for (int di = st, si = l; si <= r; ++si, ++di)
		dest[di] = special(0, dest, len, di - 1, m1, m2) + src[si];
}
template<typename tp>
void presum_preprocess(
						const vector<tp> &src, int l, int r,
						vector<tp> &dest, int st, int m1 = -1, int m2 = -1)
{
	int len = length(l, r);
	if (dest.size() < st + len)
		dest.resize(st + len);
	if (!~m1 || !~m2)
		m1 = 0, m2 = dest.size() - 1;
	for (int di = st, si = l; si <= r; ++si, ++di)
		dest[di] = special(0, dest, di - 1, m1, m2) + src[si];
}
template<typename tp>
tp premul_range(const tp *mul, int len, int l, int r, int m1 = -1, int m2 = -1)
{
	if (!~m1 || !~m2)
		m1 = 0, m2 = len - 1;
	return mul[r] / special(1, mul, len, l - 1, m1, m2);
}
template<typename tp>
tp premul_range(const vector<tp> &mul, int l, int r, int m1 = -1, int m2 = -1)
{
	if (!~m1 || !~m2)
		m1 = 0, m2 = mul.size() - 1;
	return mul[r] / special(1, mul, l - 1, m1, m2);
}
template<typename tp>
void premul_preprocess(
						const tp *src, int l, int r,
						tp *dest, int len, int st, int m1 = -1, int m2 = -1)
{
	if (!~m1 || !~m2)
		m1 = 0, m2 = len - 1;
	for (int di = st, si = l; si <= r; ++si, ++di)
		dest[di] = special(1, dest, len, di - 1, m1, m2) * src[si];
}
template<typename tp>
void premul_preprocess(
						const vector<tp> &src, int l, int r,
						vector<tp> &dest, int st, int m1 = -1, int m2 = -1)
{
	int len = length(l, r);
	if (dest.size() < st + len)
		dest.resize(st + len);
	if (!~m1 || !~m2)
		m1 = 0, m2 = dest.size() - 1;
	for (int di = st, si = l; si <= r; ++si, ++di)
		dest[di] = special(1, dest, di - 1, m1, m2) * src[si];
}
