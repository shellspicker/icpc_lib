#include <bits/stdc++.h>
using namespace std;

const int lm = 1;
const int rm = 5;

map<int, pair<int, int>> mmp;

int id1(int l, int r) {
	//return l + r | l != r;
	//return l + r + (l ^ r && (l ^ r ^ 1) & 1);
	return l + r + (l != r && (r - l + 1) & 1);
}

int id2(int l, int r) {
	//return l + r - (l ^ r && (l ^ r ^ 1) & 1);
	return l + r - (l != r && (r - l + 1) & 1);
}

int mid1(int l, int r) {
	return (l + r) / 2;
}

int mid2(int l, int r) {
	return l + (r - l + 1) / 2;
}

void dfs1(int l, int r) {
	int idx = id1(l, r);
	printf("[%d, %d]: %d\n", l, r, idx);
	mmp[idx] = {l, r};
	if (l == r)
		return;
	int m = mid1(l, r);
	dfs1(l, m);
	dfs1(m + 1, r);
}

void dfs2(int l, int r) {
	int idx = id2(l, r);
	printf("[%d, %d]: %d\n", l, r, idx);
	mmp[idx] = {l, r};
	if (l == r)
		return;
	int m = mid2(l, r);
	dfs2(l, m - 1);
	dfs2(m, r);
}

void test1(int lef, int rig) {
	int st, ed;
	mmp.clear();
	dfs1(lef, rig);
	st = id1(lef, lef);
	ed = id1(rig, rig);
	for (int i = st; i <= ed; ++i)
		printf("%d: [%d, %d]\n", i, mmp[i].first, mmp[i].second);
}

void test2(int lef, int rig) {
	int st, ed;
	mmp.clear();
	dfs2(lef, rig);
	st = id2(lef, lef);
	ed = id2(rig, rig);
	for (int i = st; i <= ed; ++i)
		printf("%d: [%d, %d]\n", i, mmp[i].first, mmp[i].second);
}

int main()
{
	test1(lm, rm);
	test2(lm, rm);
	return 0;
}
