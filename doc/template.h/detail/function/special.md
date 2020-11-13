# special

```c++
template<typename tp>
tp special(tp val, const tp *arr, int len, int i, int m1 = -1, int m2 = -1); // 1.
template<typename tp>
tp special(tp val, const vector<tp> &v, int i, int m1 = -1, int m2 = -1); // 2.
```

数组下标取值, 并对非法范围的下标设置特殊值.

1. 数组版本.
2. vector版本.

在dp或者前缀和中, 我们可能会对超出数组下标范围的地方设置一个固定的值, 这时候就是用special的绝佳时机.

## parameter

**val** - 自定义的特殊值.

**arr, len, v** - 数组.

**i** - 下标.

**m1, m2** - 下标范围.

## return value

* 下标在合法范围, 返回数组中的值.
* 下标在非法范围, 返回自定义的特殊值.

## todo

改为iterator形式, 符合通用的algorithm.