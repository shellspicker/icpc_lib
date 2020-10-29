# 二分搜索

论二分搜索的正确姿势.

不管你的编程能力是什么程度, 你应该听过二分搜索是很少人能写对的一个简单算法.

> 其实, 来看本篇文章的人应该多少也搜索过其他的二分相关文章, 大概了解了什么是二分.  
如果没有了解呢? 请先去了解一下.

## 前情提要

首先, 再谈一下二分搜索的定义(背景?):

限定, 一个有序的序列(数组).  
以下, 我都用数组和其相关的字眼.  
简单来说, 二分搜索就是在数组中找数字.  
注意: 数组中的数字可能有重复.  
当然了, 既然是搜索, 肯定有可能找不到所求的数字.

### 基础版

不考虑限定条件, 纯粹搜索.

令要找的数为target.

* 找到一个值, 等于target.

### 进阶版

由于数组中的值可能有重复, 有以下几种需求.

令要找的数为target.

* 找到一个值, 小于target, 且下标是符合条件中的位置里最大的.
* 找到一个值, 大于等于target, 且下标是符合条件中的位置里最小的.
* 找到一个值, 小于等于target, 且下标是符合条件中的位置里最大的.
* 找到一个值, 大于target, 且下标是符合条件中的位置里最小的.

其实, 进阶版的4种情况才是最常见的需求, 如果你只会基础版, 那么请务必接着看.

## 本文目的

本文将带你正确理解二分搜索, 点亮以下几点成就:

* 随手能写出无bug的二分搜索.
* 认识到常见的4种二分搜索之间是有相似性, 即可把4种二分搜索集合于1个函数中.

## 限定

* 代码使用c++语言, 使用其他语言的玩家请自行翻译.
* 数据结构使用vector\<int\>.
* 搜索区间使用左闭右闭的区间.
* 不考虑取中点的实现, 假设你已经有一个可以正确求出中点的函数.

为什么使用左闭右闭区间来搜索?  
因为我要保证每个点都是实点而不是虚点.

为什么不考虑取中点的实现?  
说实话这个不是二分的核心, 虽然是二分必须要使用的一个函数, 但是我们可以交给外部来实现, 二分内部直接调用这个函数.  
我们假设其原型为`int midpoint(int, int)`, 后文都会使用这个函数.

## 基础版实现

### 原型

```c++
int binary_search(vector<int> &data, int lef, int rig, int target);
```

#### 参数

**data** - 排序好的数组, 这里我们默认其为从小到大, 之后会扩展到从大到小的情况.

**lef**, **rig** - 搜索的左右边界, 需要在数组下标范围内.

**target** - 需要搜索的数字.

#### 返回值

target在data中的下标. 如果找不到, 返回-1.

### 可能的实现

```c++
int binary_search(vector<int> &data, int lef, int rig, int target) {
    int pos = -1;
    while (lef <= rig) {
        int mid, now;
        mid = midpoint(lef, rig);
        now = data[mid];
        if (now == target)
            pos = mid;
        if (now < target)
            lef = mid + 1;
        else
            rig = mid - 1;
    }
    return pos;
}
```

相信大家的实现和这里写的差不多, 基础版的二分, 应该没有人会写出很奇怪的写法.

## 进阶版其中之一的实现

由于进阶版有4种情况, 我们以其中第1种为例, 先来个简单的实现.

需求为:  
找到一个值, 小于target, 且下标是符合条件中的位置里最大的.

### 原型

```c++
int binary_search(vector<int> &data, int lef, int rig, int target);
```

#### 参数

**data** - 排序好的数组, 这里我们默认其为从小到大, 之后会扩展到从大到小的情况.

**lef**, **rig** - 搜索的左右边界, 需要在数组下标范围内.

**target** - 需要搜索的数字.

#### 返回值

target在data中的下标. 如果找不到, 返回一个不在[lef, rig]范围的下标.

注意这个返回值, 和基础版有区别.

### 可能的实现

```c++
int binary_search(vector<int> &data, int lef, int rig, int target) {
    int pos;
    while (lef <= rig) {
        int mid, now;
        mid = midpoint(lef, rig);
        now = data[mid];
        if (now < target)
            lef = mid + 1;
        else
            rig = mid - 1;
    }
    pos = rig;
    return pos;
}
```

注意这个代码, 和基础版本, 可以说很类似, 但是又有微妙的差别.

来梳理一下几处核心细节.

### 核心细节

这里讲的是我的写法的几处细节, 请勿把自己的写法代入这里的情景.

#### while的条件

一定是区间长度大于等于1.

这个很好理解, 区间里面每个数都要进行一次查找条件的判断.

#### if...else语句块的顺序, 区间端点的移动

你可能会有疑问, if...else语句块顺序有什么问题吗?

我暂且回答你, 可以把if...else交换, 然后结果也正确, 但是只有正确的语句顺序, 才能助你写出无bug的二分逻辑.

条件里区间端点的移动, `lef = mid + 1;`和`rig = mid - 1;`是固定的.

注意到lef和rig一定会移动到mid +/- 1的地方. 你可能会见过其他写法, 有些情况区间端点移动是直接赋值为mid的, 请先遗忘那些写法.

至于端点怎么移动(即区间往什么方向缩小), 你不应该写反, 否则请去面壁思过.

再回到if...else的顺序, if里面写所求条件为true的条件.

这里的需求所求为: 找小于target的值, 对应了这里的if语句.

#### 返回值

返回else所对应的端点(lef或rig), 这里else对应rig, 最后结果也是rig.

---

#### 正确性

重复一遍以上核心细节(以下称细节为规则):

> 1. while的条件是区间长度大于等于1.
>
> 2. if的条件是具体需求所求的条件为true.
>
> 3. lef = mid + 1; rig = mid - 1; 即端点的移动一定不取mid.
>
> 4. 返回值是else条件下对应的lef或rig.

为什么这样写是对的呢? 这样的细节有什么优点吗?

规则1和2应该大家疑问不大.

规则3  
端点不取mid, 一定可以避免区间端点不缩小.  
而且这样不需要记忆这个端点到底要不要在mid的基础上+1或者-1, 可以做到代码写法统一.

规则4  
这里决定二分的返回值是否正确.  
这里的写法为何是正确的呢?  
首先考虑区间中包含所求的条件, 即最后可以找到答案的情况  
符合所求条件的区间一定是一个前缀或后缀的连续区间, 不符合条件的区间则是剩余的前缀或后缀.   
令, 符合所求条件的区间为T, 不符合条件的区间为F.  
那么T和F有个分界线, 线的一边是T, 另一边则是F.  
中了if条件说明当前搜索区间包含T, 中了else条件说明当前区间包含F.  
不难想到, 中了if条件, 端点会往F区间的方向移动; 中了else条件, 端点会往T区间的方向移动.  
区间端点在移动时, 如果跨越了这个分界线, 那么一定是刚好跨越1个单位长度, 即前面所说的`lef = mid + 1;`和`rig = mid - 1;`,  
那么接下来的搜索过程中, 一定全落在和之前判断条件相反的区间里, 即区间性质变化为(TF)->(T)或(TF)->(F).  
如果最后出循环的时候, 区间是F性质, 那么最后else代码块对应的端点往T方向移动, 即刚好跨越了分界线到达T区间, 符合所求条件.  
相反, 最后出循环的时候, 区间是T性质, 最后lef == rig, 其中if代码块对应的端点往F方向移动, else代码块未执行. 即else代码块对应的端点留在了最后的T性质的区间, 符合所求条件.  
所以, 最后else代码块对应的端点, 即为返回值.  
再来考虑区间中无答案的情况.  
那么整个搜索过程区间性质为(F), 最后中else条件, 无对应T区间, 端点会落在最初的lef, rig区间之外的点.  
所以不难想到, 在得到返回值之后, 判断一下此端点是否在最初传参的区间中, 即可知是否找到了答案.

证明完结.

记住上面引用的4个规则, 你就能写出任意情况的二分,  
并且, 这些规则能用于任何满足二分性质的搜索, 不仅仅是在数组中找数字.

会举一反三的读者应该能写出进阶版的4种需求(这里刚好举例1种情况, 反3, 那刚好4种. 233).

什么? 你不会举一反三? 好, 那我把进阶版的4中需求都写一遍吧.

觉得可以自己写出的读者可以跳过.

## 进阶版本的所有实现

### 原型

```c++
int binary_search_less_last(vector<int> &data, int lef, int rig, int target); // ver.1
int binary_search_greater_equal_first(vector<int> &data, int lef, int rig, int target); // ver.2
int binary_search_less_equal_last(vector<int> &data, int lef, int rig, int target); // ver.3
int binary_search_greater_first(vector<int> &data, int lef, int rig, int target); // ver.4
```

**ver.1** - 数组中小于target的数中的最后一个.

**ver.2** - 数组中大于等于target的数中的最前一个.

**ver.3** - 数组中小于等于target的数中的最后一个.

**ver.4** - 数组中大于target的数中的最前一个.

#### 参数

**data** - 排序好的数组, 这里我们默认其为从小到大, 之后会扩展到从大到小的情况.

**lef**, **rig** - 搜索的左右边界, 需要在数组下标范围内.

**target** - 需要搜索的数字.

#### 返回值

target在data中的下标. 如果找不到, 返回一个不在[lef, rig]范围的下标.

### 可能的实现

```c++
int binary_search_less_last(vector<int> &data, int lef, int rig, int target) {
    int pos;
    while (lef <= rig) {
        int mid, now;
        mid = midpoint(lef, rig);
        now = data[mid];
        if (now < target)
            lef = mid + 1;
        else
            rig = mid - 1;
    }
    pos = rig;
    return pos;
}
int binary_search_greater_equal_first(vector<int> &data, int lef, int rig, int target) {
    int pos;
    while (lef <= rig) {
        int mid, now;
        mid = midpoint(lef, rig);
        now = data[mid];
        if (now >= target)
            rig = mid - 1;
        else
            lef = mid + 1;
    }
    pos = lef;
    return pos;
}
int binary_search_less_equal_last(vector<int> &data, int lef, int rig, int target) {
    int pos;
    while (lef <= rig) {
        int mid, now;
        mid = midpoint(lef, rig);
        now = data[mid];
        if (now <= target)
            lef = mid + 1;
        else
            rig = mid - 1;
    }
    pos = rig;
    return pos;
}
int binary_search_greater_first(vector<int> &data, int lef, int rig, int target) {
    int pos;
    while (lef <= rig) {
        int mid, now;
        mid = midpoint(lef, rig);
        now = data[mid];
        if (now > target)
            rig = mid - 1;
        else
            lef = mid + 1;
    }
    pos = lef;
    return pos;
}
```

### 不同需求的区别

读者自行对比一下以上的4个函数的区别, 会发现, 区别不大, 严格按照前文提到的4条原则来实现.

## 究极版

回顾一下[](#本文目的), 还有数组大小现在是默认从小到大.

这里我们来完成: 把进阶版4个函数, 合并成1个函数.  
并且不会和上文实现一样写4次基本一样的代码, 代码量约等于1.5个进阶版的实现.  
只用1.5倍代码完成4倍代码的事情, 开始.

以下出现的一些参数名, 默认和之前的版本一致.

### 发现不同需求之间的规律

首先我们构造一个数组, 用区间的括号来解释一下进阶版的需求实际上是在求什么.

构造数组`1, 2, 2, 4, 5`.

看数字2的区间, 写成左闭右闭区间是[1, 2], 那么左开右开区间是(0, 3).

再看进阶版的4个需求: 

**ver.1** - 数组中小于target的数中的最后一个. 即为括号`(`对应的下标.

**ver.2** - 数组中大于等于target的数中的最前一个. 即为括号`[`对应的下标.

**ver.3** - 数组中小于等于target的数中的最后一个. 即为括号`]`对应的下标.

**ver.4** - 数组中大于target的数中的最前一个. 即为括号`)`对应的下标.

> 如果了解std的二分的人, 应该知道:  
>
> ver.1 - 对应lower_bound - 1.
>
> ver.2 - 对应lower_bound.
>
> ver.3 - 对应upper_bound - 1.
>
> ver.4 - 对应upper_bound.

那么我们可以用括号来表示你搜索的需求, 括号有2个属性:

1. 括号方向是左或右.
2. 括号包含是开或闭.

如果要把4种情况合成1个函数, 那么需要加上以上2个属性作为函数参数.

由于方向和包含都只有2种取值情况, 我们用0和1表示.

括号方向, 0为左, 1为右.

是否包含, 0为不包含, 1为包含.

另外, 我们还要区别一下括号方向和实际搜索的方向(if...else的区间端点移动方向).

同样, 搜索方向也用0和1表示.

搜索方向, 0为向左搜索, 1为向右搜索.

### 规律

有以上提到的一些属性, 不难列出一个表格:

| 括号方向 | 括号包含 | 括号形态 | 比较条件(now op target) | if的方向(true) | else的方向(false) | reutrn |
| -------- | -------- | -------- | ----------------------- | -------------- | ----------------- | ------ |
| 0        | 0        | `(`      | `<`                     | 1              | 0                 | rig    |
| 0        | 1        | `[`      | `>=`                    | 0              | 1                 | lef    |
| 1        | 1        | `]`      | `<=`                    | 1              | 0                 | rig    |
| 1        | 0        | `)`      | `>`                     | 0              | 1                 | lef    |

由于表格中的关键属性值都是0或1, 我们可以用位运算来得到返回值是lef还是rig.

如果不看表格中"比较条件"这列, 那么这个表格是很有规律的, 而且if...else语句块, 在方向确定的情况下, 代码是固定的.  
不难想到, 可以用宏来精简代码.

### 原型

```c++
int binary_search(vector<int> &data, int lef, int rig, int target, bool dir, bool contain);
```

把目标区间类比成括号形式, 二分搜索.

#### 参数

**data** - 排序好的数组, 这里我们默认其为从小到大, 之后会扩展到从大到小的情况.

**lef**, **rig** - 搜索的左右边界, 需要在数组下标范围内.

**target** - 需要搜索的数字.

**dir** - 括号的方向.

**contain** - 括号的包含.

#### 返回值

搜索目标在数组中的下标,.

如果无符合目标条件的, 则返回[lef, rig]之外的下标.

### 可能的实现

```c++
int binary_search(vector<int> &data, int lef, int rig, int target, bool dir, bool contain) {
#define look(cond) if ((cond)) lef = mid + 1; else rig = mid - 1;
    int pos;
    while (lef <= rig) {
        int mid, now;
        mid = midpoint(lef, rig);
        now = data[mid];
        look((!dir && now < target) || (dir && !(target < now)));
    }
    pos = dir ^ contain ? lef : rig;
    return pos;
#undef look
}
```

其中, 把大小判断的等于号避开了, 代码中之写了小于号, 这样写的好处之后会体会到.

那么我们就完成了用1个函数写完4个函数的功能.

## 完全版

记得我之前说过, 默认数组是从小到大排序的, 我们现在来扩展一下从大到小的情况.

需求为:

**ver.1** - 数组中大于target的数中的最后一个. 即为括号`(`对应的下标.

**ver.2** - 数组中小于等于target的数中的最前一个. 即为括号`[`对应的下标.

**ver.3** - 数组中大于等于target的数中的最后一个. 即为括号`]`对应的下标.

**ver.4** - 数组中小于target的数中的最前一个. 即为括号`)`对应的下标.

### 规律

还是画一个表格找规律:

| 括号方向 | 括号包含 | 括号形态 | 比较条件(now op target) | if的方向(true) | else的方向(false) | reutrn |
| -------- | -------- | -------- | ----------------------- | -------------- | ----------------- | ------ |
| 0        | 0        | `(`      | `>`                     | 1              | 0                 | rig    |
| 0        | 1        | `[`      | `<=`                    | 0              | 1                 | lef    |
| 1        | 1        | `]`      | `>=`                    | 1              | 0                 | rig    |
| 1        | 0        | `)`      | `<`                     | 0              | 1                 | lef    |

对比一下从小到大和从大到小的情况, 发现只有比较条件的`<`变成了`>`.

伏笔来了, 究极版的实现中, 我们把比较条件中的`=`给避开了, 那么从小到大的版本换到从大到小的版本也就是直接把代码中的`<`换成`>`即可.

其实比较的符号, std中有`less<>`和`greater<>`, 那么这里我们就要写成模板函数.

### 原型

```c++
template<class fn_cmp>
int binary_search(vector<int> &data, int lef, int rig, int target, bool dir, bool contain);
```

把目标区间类比成括号形式, 二分搜索.

支持从小到大排序和从大到小排序的数组.

#### 参数

**fn_cmp** - 比较级, 取`less<>`或`greater<>`.

**data** - 排序好的数组, 这里我们默认其为从小到大, 之后会扩展到从大到小的情况.

**lef**, **rig** - 搜索的左右边界, 需要在数组下标范围内.

**target** - 需要搜索的数字.

**dir** - 括号的方向.

**contain** - 括号的包含.

#### 返回值

搜索目标在数组中的下标,.

如果无符合目标条件的, 则返回[lef, rig]之外的下标.

### 可能的实现

```c++
template<class fn_cmp>
int binary_search(vector<int> &data, int lef, int rig, int target, bool dir, bool contain) {
#define look(cond) if ((cond)) lef = mid + 1; else rig = mid - 1;
    int pos;
    fn_cmp cmp = fn_cmp();
    while (lef <= rig) {
        int mid, now;
        mid = midpoint(lef, rig);
        now = data[mid];
        look((!dir && cmp(now, target)) || (dir && !cmp(target, now)));
    }
    pos = dir ^ contain ? lef : rig;
    return pos;
#undef look
}
```

## 结尾的话

关于midpoint, 可能的函数原型其实是`long long midpoint(long long lef, long long rig)`, 可支持64位有/无符号整数任意2个值取中点.  
其实现就请读者自行摸索.

浮点数区间的二分搜索, 也可以套用本文的规则, 只不过把单位从1换成了一个很小的浮点数(如1e-6).

二叉平衡搜索树上的二分也可以把4个二分函数写成1个, 请会实现二叉平衡搜索树的读者自行思考.
