# 通用的递归转非递归方法

本文将以二叉树的3种(前序, 中序, 后序)遍历为例, 介绍一下通用的递归转非递归的方法.

## 浅谈模拟方法和通用方法

随意在网上搜索一下二叉树非递归遍历的实现, 都是模拟栈的写法, 以下称为**模拟方法**.

我认为模拟的方法, 各种实现千奇百怪, 并且难以记忆.

> 有人可能要开始了, 不是很好记吗?  
> 那么请你半年不看非递归的3种遍历写法, 然后再一次性写出无bug的代码.

我所要介绍的是一种通用方法, 你可以认为也是栈, 但不是模拟树的遍历的进出栈,  
而是模拟计算机对于函数栈的处理, 以下称为**通用方法**.

> 如果有人认为这不算通用方法, 那么我就要问了, 按照计算机的思维来写代码, 不是通用是什么?

对比一下模拟方法和通用方法, 模拟方法的劣势是只针对特定问题的场景.

如果换一个递归的函数让你写出其非递归版本, 那么只会模拟方法的玩家就要重新思考问题了.

因为2个不同的递归函数写成非递归函数, 用模拟方法来实现一定是有相当大的区别的.

通用方法的实现则不同, 只要知道其核心思想和一个固定的写法, 任何递归函数转化为非递归函数的思路都是一样的.

## 结点结构

### 实现

```c++
struct binary_node {
  binary_node() {
      ls = rs = 0;
      vis = 0;
  }
  binary_node *ls, *rs;
  int id;
  bool vis;
};
```

**ls**, **rs** - 左右子结点.

**id** - 标识结点的编号, 是自定义的数字, 用于输出.

**vis** - 访问标记.

---

这个实现只是为了本篇文章使用, 实际上不同的人会写出不同的实现, 不用拘束于代码.

## 递归

### 实现

用pre字眼表示前序, in字眼表示中序, post字眼表示后序.

```c++
void dfs_pre(binary_node *o) {
    if (!o || o->vis)
        return;
    o->vis = 1;
    printf("%d\n", o->id);
    dfs_pre(o->ls);
    dfs_pre(o->rs);
}

void dfs_in(binary_node *o) {
    if (!o || o->vis)
        return;
    o->vis = 1;
    dfs_pre(o->ls);
    printf("%d\n", o->id);
    dfs_pre(o->rs);
}

void dfs_post(binary_node *o) {
    if (!o || o->vis)
        return;
    o->vis = 1;
    dfs_pre(o->ls);
    dfs_pre(o->rs);
    printf("%d\n", o->id);
}
```

这个实现应该没有难度, 写不出来的请去面壁思过.

注意到3个不同的遍历方式, 只有几行代码改变了, 表示访问顺序的不同.

可以感觉到, 这3个函数都是同一种框架.

先预告一下, 非递归版本的也可以写得像这样, 写3个函数如同写1个函数.

## 非递归

### 思考计算机处理函数栈的过程

以下我可能不会提"计算机"这个字眼, 用"程序"来代替.

---

**前置**

函数调用栈, 这个概念应该要了解, 否则请先去了解一下.

---

思考这样几个问题:

1. 程序在从函数A调用到函数B的时候, 做了什么事情?
2. 从上一步回来, 也就是函数B运行完, 回到函数A的时候, 做了什么事情?

问题1, 函数A的上下文会被保存起来, 然后函数B进栈, 初始化B的上下文.

问题2, 函数B出栈, 此时栈顶是刚才的函数A, 恢复A的上下文, 继续A函数的运行.

那么模拟函数栈的**核心思想**就是: 怎么建立一个函数的上下文?

---

考虑这样一个代码片段:

```c++
void func(...) {
    // 代码片段1.
    func(...); // 递归调用.
    // 代码片段2.
}
```

这里是一个递归函数, 不要考虑其参数和边界条件, 只考虑递归调用的过程.

可以看到, 一个函数是可以被切成几个片段的.  
在片段1的末尾, 调用了func产生了递归, 在递归调用func结束后, 这里会去执行片段2.  
不难想到, 我们的上下文就是这样, 在递归调用func之前, 上下文记录着: "等一下调用回来之后, 我要去跑片段2的代码.".

> 把函数代码切成几个片段, 递归调用前, 设置上下文为递归调用之后的片段.

上下文除了记录代码片段, 还有什么其他的重要信息要记录呢?  
那就是函数内的变量了, 不难想到, 递归前和递归后, 函数内的变量是保持不变的.  
用通俗的话来讲, 这叫恢复工作区(熟悉git的玩家可以想到, 这就是stash push和stash pop).

> 上下文还要保存函数的变量.

注意: 如果是在for里面递归, 那么for里面的循环变量, 也算是函数变量.  
只有保存了, 才能每次递归结束之后, 从上一次的for循环位置继续.

关于上下文具体要保存什么东西, 仔细查看代码, 不难想到.

---

考虑单一函数的处理过程.  
没有递归的话, 单一函数栈处理就是取栈顶函数, 处理, 弹出函数栈.

再考虑函数栈的弹入(push)和弹出(pop)的过程, 其只做2件事:

1. 执行本层函数的代码, 执行到函数最后, 就弹出本层函数.
2. 调用其他函数, 弹入一层函数并做一些变量的初始化. 跳转到1.

那么这整个过程就是一个循环, 不难实现.

### 框架

这里给出一个非递归的大致框架:

```c++
// 递归版.
return_type func_name_recursion(arg_type args[]) {
    // 片段1.
    func_name_recursion(...);
    // 片段2.
}

// 非递归版.
return_type func_name_non_recursion(arg_type args[]) {
    // 这个结构体即保存上下文.
    struct context {
      int phase; // 必要变量, 表示代码片段, 我称之为阶段, 英文phase.
      // 自己找函数里出现的所有变量存进去. 如果函数有返回值, 也要存返回值.
    };
    stack<context> reg;
    reg.push({1, ...}); // 初次函数调用的上下文.
    while (!st.empty()) {
        auto &now = reg.top(); // 取得当前层函数的上下文.
        switch (now.phase) {
            case 1:
                // 片段1.
                reg.push({1, ...}); // 准备递归, 初始化递归函数的上下文.
                now.phase = 2; // 递归之后去执行代码片段2.
                continue; // 已经弹入新函数栈, 继续取栈顶. continue一定配合函数栈push用.
            case 2:
                // 片段2.
                now.phase = -1; // 这里随便设置一个没有在任何case里的phase即可, 表示这个函数结束了.
                continue; // 这里让其设置phase, continue之后跳转到default去break或者直接break都行.
            default:
                break;
        }
        reg.pop();
    }
}
```

以上是伪代码, 大概了解一下框架.

我个人觉得这种代码有点像状态机.

直接快进到非递归二叉树3种遍历的实现.

### 实现

```c++
struct context {
    int phase;
    binary_node *o;
};

void dfs_pre(binary_node *o) {
    stack<context> reg;
    reg.push({0, o});
    while (!st.empty()) {
        auto &now = reg.top();
        switch (now.phase) {
            case 0:
                if (!o || o->vis)
                    break;
                o->vis = 1;
                printf("%d\n", o->id);
                reg.push({0, o->ls});
                now.phase = 1;
                continue;
            case 1:
                reg.push({0, o->rs});
                now.phase = -1;
                continue;
            default:
                break;
        }
        reg.pop();
    }
}

void dfs_in(binary_node *o) {
    stack<context> reg;
    reg.push({0, o});
    while (!st.empty()) {
        auto &now = reg.top();
        switch (now.phase) {
            case 0:
                if (!o || o->vis)
                    break;
                o->vis = 1;
                reg.push({0, o->ls});
                now.phase = 1;
                continue;
            case 1:
                printf("%d\n", o->id);
                reg.push({0, o->rs});
                now.phase = -1;
                continue;
            default:
                break;
        }
        reg.pop();
    }
}

void dfs_post(binary_node *o) {
    stack<context> reg;
    reg.push({0, o});
    while (!st.empty()) {
        auto &now = reg.top();
        switch (now.phase) {
            case 0:
                if (!o || o->vis)
                    break;
                o->vis = 1;
                reg.push({0, o->ls});
                now.phase = 1;
                continue;
            case 1:
                reg.push({0, o->rs});
                now.phase = 2;
                continue;
            case 2:
                printf("%d\n", o->id);
                now.phase = -1;
                continue;
            default:
                break;
        }
        reg.pop();
    }
}
```

对比一下, 这几个非递归写法, 只有几行访问顺序的区别, 剩下的都是框架操作.

完结撒花.

## 后记

其实二叉树的递归遍历, 是递归中相当简单的情况, 如果画成一个图, 表示这个函数有自环.

复杂的递归是这样的: A->B->C->D->A, 类似这样, 调用了好多个函数之后再调用回自己, 这种情况我还没有对应的例子.  
递归下降法做表达式解析, 就会遇到这样的调用链, 比较复杂, 有兴趣的读者自行尝试.
