# cube

```c++
template<class pm>
class cube;
```

魔方类, 置换的组合.

本质上是用置换的变换来做状态搜索.

相关前置知识, 请了解魔方的体置换和面置换(在写了).

## typedef, using

| define | origin     |
|--------|------------|
| vpm    | vector<pm> |

## static member function

* [init](), 初始化, 之后准备弃用.

## member function

* [level\_bfs](), 按照一系列置换做bfs复合, 搜索所有的状态.

* [face\_seq](), 在有所有体置换的前提下, 搜索所有面置换.

## todo

把`static void init()`去掉, 感觉使用cube前一定初始化了permutation类.
