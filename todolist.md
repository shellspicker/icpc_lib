# todolist

## template

- [ ] 一些数学函数, 几何相关?
- [ ] 二维, 三维数组的遍历方向数组. 二维的4向, 8向; 三维的6向, 26向(可能不需要)...
- [x] 快速读入, istream.rdbuf->sgetn(buf, sizeof(buf)), 配合readint...
- [ ] 开栈.
- [x] efg_cvt, 浮点数截断, 暂时弃了.
- [ ] 整理一份全局符号表.
- [ ] div_t, round之类的math.h或stdlib.h的好东西.
- [ ] direct_io和debug类合并, debug保留换行符输出选项.
- [ ] direct_io是什么时候绑定io的? 现在会了交互题, 再看看普通io快速读入的题, 不要生成全局对象, 另外加一个交互类(很简单).
- [ ] direct_io.msg, 要和bug输出一起使用, 才能在assert之前输出东西. 测试的话使用一个无限递归函数, 每层输出函数名, assert固定层数, 如果不用bug输出, 那么fio.msg不会显示, 最后只有assert的显示.
原因是ios::sync_with_stdio(0)之后, cout不能在assert前输出, 但是cerr可以.
- [x] 前缀预处理完善一下(1d), 配合的zip需要可以导出一个迭代器, 方便一行的操作(一般用在二维数组的情况). 顺便可以看看valarray怎么实现隔离块的拼接.

## basic

- [ ] 各种随机数据生成器, 参考cyaron. 或者不写, 直接用cyaron.
- [ ] 时间or日期类, 用作debug或计算.

## data structure

- [x] 各种平衡树.
- [x] 笛卡尔树.
- [x] 平衡树把ls和rs的引用去掉, 这个会占很多空间.
- [x] 自顶向下搜索树操作.
- [ ] lct.
- [ ] 线段树以及类似的带push和pull的区间结构, 文本编辑器, 数列维修.
- [ ] 分块. 以及延申的xx分治. 再就是块状链表.
- [ ] pbds头文件, 好像win上编译不了? 各种数据结构都要测试一下.
- [ ] 堆.

## math

- [ ] 大浮点数, 大整数已经有了, 稍微改一下, poj1001.
- [ ] 分数类, uva12558.
- [ ] 模运算类, 已经有一个了, 但是可以改进一下.
- [ ] 牛顿插值(对比拉格朗日插值).

## graph theory

- [ ] 已经有有向图和无向图的结构, 还差网络流的结构.
- [ ] lca的5种写法, 倍增, rmq, tarjan, 树链剖分, lct.
- [ ] 树的非递归, 加上命令行参数选择递归或非递归模式.

## string

- [ ] 后缀自动机, 后缀树.
- [ ] hash表.
- [ ] hash的可变参数计算函数重写一下.

## trick

- [ ] 搜索专题, 从初级到高级, 应该有个范式, 写md.
- [ ] dfs可以带goto.
- [ ] 尺取法, 尝试各种题, 写md. 写法用当前点为搜索点的形式.
- [ ] 二叉树的非递归morris遍历. 也可以知道无父结点怎么找中序遍历的前后结点.
- [x] 基数排序, 计数排序.

## other

- [x] ~~自实现allocator, 可用于vector的那种. 参考cppreference里的vector::reserve.~~
- [x] 可变参数模板, 用initializer_list一行展开.
- [ ] 各种比较级函数(min, max, 大于, 小于之类的), 传入lambda, 用function接收, 比如rmq里面用到.
- [ ] cppreference里面能用到的函数都列一遍, 做个lib整理, 模板里面有using了.
- [ ] github上的3份很好的模板都合并过来.
- [ ] 魔方模板把2个类合并到一起.

