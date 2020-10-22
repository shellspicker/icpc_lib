# transformer

## include

```c++
#include "math/gcd_lcm.h"
#include "string/hash.h"
```

## synopsis

```c++
template<size_t dn>
class permutation {
public:
    static void init();
    permutation();
    permutation(const vector<int>);
    permutation(const vector<int>, const vector<int>);
    void assign(const vector<int>);
    void assign(const vector<int>, const vector<int>);
    void compos(permutation<dn> &, int);
    int mat[2][dn];
    ull hs[2];
    vector<int> cycle[2][dn];
private:
    static int origin[dn];
    void gall();
    void ghs();
    void ginv();
    void gcyc();
};
```

```c++
template<size_t dn>
class cube {
public:
    using pm = permutation<dn>;
    using vpm = vector<permutation<dn>>;
    static void init();
    static void face_seq(vpm<dn> &, vpm<dn> &, vpm<dn> &);
    static void level_bfs(vpm<dn> &, vpm<dn> &, int limit);
private:
    static pm<dn> origin;
};
```

## description

置换类, 作为置换的基本类型使用, 下标起始0, 包含dn个状态的置换(逆), 其对应的hash值和循环节.
置换的理论详见其他文章, 这里只是封装了基本的变换.

魔方类, 置换的组合.
本质上是用置换的变换来做状态搜索.
