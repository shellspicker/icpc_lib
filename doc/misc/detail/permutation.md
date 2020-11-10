# permutation

```c++
template<size_t dn>
class permutation;
```

包含dn个状态的置换, 下标起始0.

状态是(静态)数组表示, 可求其对应的hash值和循环节表示.

置换的理论详见其他文章, 这里只是封装了基本的变换.

## static member function

* [init](), 初始化横等置换.

## member function

* [constructor](), 根据[1, 2]个状态表示置换.

* [assign](), 根据[1, 2]个状态表示置换.

* [compos](), 做正或逆置换.

* [inv](), 求逆.

* [cycle](), 求循环节表示法.

* [diff](), 求对比横等置换的不同状态数.

## member variable

`int mat[dn]`, 状态.

`ull hs`, hash值.

## todo

加一个`int operator []()`.
