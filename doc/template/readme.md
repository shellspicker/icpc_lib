# readme

## typedef

* `uint`: `unsigned int`
* `ll`: `long lnog`
* `ull`: `unsigned long long`
* `ldb`: `long double`

## 常量

* `inf32`: `1 << 30`
* `inf64`: `1ll << 60`
* `pi`: `acos(-1)`
* `eps`: `1e-6`

## 函数

### 取无穷大值

```c++
template<typename tp>
tp get_inf();
```

对应长度的整形inf值.

### 二进制位操作

```c++
template<typename tp>
int bitcount(tp); // 1.
template<typename tp>
tp clz(tp); // 2.
template<typename tp>
tp ctz(tp); // 3.
template<typename tp>
tp clo(tp); // 4.
template<typename tp>
tp cto(tp); // 5.
```

1. 二进制中1的个数.
2. 二进制前缀0的个数.
3. 二进制后缀0的个数.
4. 取二进制第一个1对应的整形数.
5. 取二进制最后一个1对应的整形数.

> 2, 3, 当参数是0的时候, 会产生unknown behavior.

### 二进制运算

```c++
template<typename tp>
tp roundup_pow_of_2(tp); // 1.
template<typename tp>
tp rounddown_pow_of_2(tp); // 2.
bool is_power_of_2(ll); // 3.
int half2xp(int); // 4.
```

1. 向上取整为2次幂.
2. 向下取整为2次幂.
3. 判断是否是2次幂.
4. rmq专用, 乘以2会大于等于原长度的最小数字.

### 分块运算

```c++
ull div_roundup(ull, ull); // 1.
ull div_rounddown(ull, ull); // 2.
ull div_last_offset(ull, ull); // 3.
```

1. 对齐到分块的右边界的块号.
2. 对齐到分块的左边界的块号.
3. 最后一个块号.

### 区间端点运算

```c++
ll ltor(ll, ll); // 1.
ll rtol(ll, ll); // 2.
ll length(ll, ll); // 3.
template<tp>
tp midpoint(tp, tp); // 4.
template<tp>
range_normalize(tp &, tp &); // 5.
ll round_shift(ll, ll, ll, ll); // 6.
bool inrange(ll, ll, ll); // 7.
tuple<ll, pair<ll, ll>> range_ins(ll, ll, ll, ll); // 8.
```

1. 左端点移动到右端点.
2. 右端点移动到左端点.
3. 左闭右闭区间的长度.
4. 左闭右闭区间的中点.
5. 判断区间端点是否满足非递减, 并修正.
6. 区间内的一个点循环位移.
7. 判断点在一个区间内.
8. 线段树专用, 求2个区间的相交情况.

### 一维数组取下标

```c++
template<typename tp>
tp special(tp, tp *, int, int, int, int); // 1.
template<typename tp>
tp special(tp, const vector<tp> &, int, int, int); // 2.
```

1. 数组版本.
2. vector版本.

#### todo

改为iterator形式.

### 文件io类

```c++
class direct_io {
public:
    direct_io();
    ~direct_io();
    bool ok();
    void set_output_float_digit(int);
    void set_bufsize(int);
    template<typename ...var>
    bool in(var &&...);
    bool readline(string &, char);
    bool readline_noblank(string &, char);
    template<typename ...var>
    void out(var &&...);
    void msg(const char *, ...);
};
```

一个文件 buffer io 类, faster than 1b.