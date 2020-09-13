#pragma once

/*
 * dir: find in left or right.
 * contain: can be equal or not.
 * whatever, key can be not found, thus return index will flow,
 * be careful to check return point, if must.
 * one way to check the return point is
 * check point in range and compare with key or condition again.
 * a rule is, must return error condition point, it will fix point
 * to last correct range, or it is alrealdy in correct range.
 * consume vecotr sort by less<>, you can find the pattern in the table below.
 * +-----------------------------+
 * |                             |
 * | dir           0   0   1   1 |
 * |                             |
 * | contain       0   1   1   0 |
 * |                             |
 * | compare       <   >=  <=  > |
 * |                             |
 * | shape         (   [   ]   ) |
 * |                             |
 * | aim_dir       1   0   1   0 |
 * |                             |
 * | error_dir     0   1   0   1 |
 * |                             |
 * | dir                         |
 * | xor contain   1   1   1   1 |
 * | xor aim_dir                 |
 * |                             |
 * | dir                         |
 * | xor contain   0   0   0   0 |
 * | xor error_dir               |
 * |                             |
 * +-----------------------------+
 * for sort by greater<>, just use cmp function instead of <.
 * return: (found, index, value).
 */
#if 201103L <= __cplusplus
template<typename tp, class func_cmp = less<tp>>
tuple<bool, pair<ll, tp>> binary_search(
		const vector<tp> &v, ll lo, ll hi, tp key, bool dir, bool contain)
{
#define look(cond) if ((cond)) lo = mid + 1; else hi = mid - 1;
	assert(lo <= hi);
	func_cmp cmp = func_cmp();
	ll locp = lo, hicp = hi, fd_index = -1;
	tp fd_value;
	bool found = 0;
	while (lo <= hi) {
		int mid = midpoint(lo, hi), now = v[mid];
		look((!dir && cmp(now, key)) || (dir && !cmp(key, now)));
	}
	int pos = dir ^ contain ? lo : hi;
	if (inrange(pos, locp, hicp)) {
		found = 1;
		fd_value = v[fd_index = pos];
	}
	return make_tuple(found, make_pair(fd_index, fd_value));
#undef look
}
#endif
