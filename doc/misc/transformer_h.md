# misc/transformer.h

## includes

* math/gcd\_lcm.h

* string/hash.h

## classes

* [permutation](detail/permutation.md), 置换基本操作.

* [cube](detail/cube.md), 魔方基本操作.

## synopsis

### class template [permutation](detail/permutation.md)

```c++
template<size_t dn>
class permutation {
public:
	static void init();
	permutation();
	permutation(const vector<int> &p);
	permutation(const vector<int> &pre, const vector<int> &nxt);
	void assign(const vector<int> &p);
	void assign(const vector<int> &pre, const vector<int> &nxt);
	void compos(permutation<dn> &rhs, int tp);
	permutation<dn> inv();
	tuple<vector<vector<int>>, int> cycle();
	int diff();
	int diff(permutation<dn> &rhs);
	int mat[dn];
	ull hs;
};
```

### class template [cube](detail/cube.md)

```c++
template<class pm>
class cube {
public:
	using vpm = vector<permutation<dn>>;
	static void init();
	static void level_bfs(vpm<dn> &comb, vpm<dn> &misc, int limit);
	static void face_seq(vpm<dn> &comb, vpm<dn> &body, vpm<dn> &face);
};
```
