# template.h

## typedef

| define | origin             |
| ------ | ------------------ |
| uint   | unsigned int       |
| ll     | long long          |
| ull    | unsigned long long |
| ldb    | long double        |

## constants

| name  | value       |
| ----- | ----------- |
| inf32 | 1 << 30     |
| inf64 | 1ll << 60   |
| pi    | acos\(\-1\) |
| eps   | 1e\-6       |

## 函数

### 取无穷大值

| name         | description        |
| ------------ | ------------------ |
| [get\_inf](detail/function/get_inf.md) | 取32/64位的inf值. |

### 二进制位操作

| name         | description                     |
| ------------ | ------------------------------- |
| [bitcount](detail/function/bitcount.md) | 二进制中1的个数.               |
| [clz](detail/function/clz.md)      | 二进制前缀0的个数.             |
| [ctz](detail/function/ctz.md)      | 二进制后缀0的个数.             |
| [clo](detail/function/clo.md)      | 取二进制第一个1对应的整形数.   |
| [cto](detail/function/cto.md)      | 取二进制最后一个1对应的整形数. |

### 二进制运算

| name                                                         | description                               |
| ------------------------------------------------------------ | ----------------------------------------- |
| [roundup\_pow\_of\_2](detail/function/roundup_pow_of_2.md)   | 向上取整为2次幂.                          |
| [rounddown\_pow\_of\_2](detail/function/rounddown_pow_of_2.md) | 向下取整为2次幂.                          |
| [is\_power\_of\_2](detail/function/is_power_of_2.md)         | 判断是否是2次幂.                          |
| [half2xp](detail/function/half2xp.md)                        | rmq专用, 乘以2会大于等于原长度的最小数字. |

### 分块运算

| name                  | description                |
| --------------------- | -------------------------- |
| [div\_roundup](detail/function/div_roundup.md)      | 对齐到分块的右边界的块号. |
| [div\_rounddown](detail/function/div_rounddown.md)    | 对齐到分块的左边界的块号. |
| [div\_last\_offset](detail/function/div_last_offset.md) | 最后一个块号.             |
| [div\_point\_count](detail/function/div_point_count.md) | 区间内的分块起始点的个数. |

### 闭区间端点运算

| name                 | description                          |
| -------------------- | ------------------------------------ |
| [ltor](detail/function/ltor.md)             | 闭区间的左端点移动到右端点.   |
| [rtol](detail/function/rtol.md)             | 闭区间的右端点移动到左端点.             |
| [length](detail/function/length.md)           | 闭区间的长度.             |
| [midpoint](detail/function/midpoint.md)         | 闭区间的中点.                 |
| [range\_normalize](detail/function/range_normalize.md) | 判断闭区间端点是否满足非递减, 并修正. |
| [round\_shift](detail/function/round_shift.md)     | 闭区间内的一个点循环位移.            |
| [inrange](detail/function/inrange.md)          | 判断点在一个闭区间内.                |
| [range\_ins](detail/function/range_ins.md)       | 线段树专用, 求2个闭区间的相交情况.   |

### 一维数组取下标

| name        | description                                  |
| ----------- | -------------------------------------------- |
| [special](detail/function/special.md) | 数组下标取值, 并对非法范围的下标设置特殊值. |

## classes

### 文件io

| name                                             | description |
| ------------------------------------------------ | ----------- |
| [direct\_io](detail/classes/direct_io/readme.md) | 文件io. |

### synopsis

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
    void scan(const string &, const char *, ...);
    void msg(const char *, ...);
};
```