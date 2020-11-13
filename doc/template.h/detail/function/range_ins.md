# range\_ins

```c++
tuple<ll, pair<ll, ll>> range_ins(ll lef_l, ll lef_r, ll rig_l, ll rig_r);
```

线段树专用, 求2个闭区间的相交情况.

## parameter

**lef\_l, lef\_r** - 左区间的左右端点.

**rig\_l, rig\_r** - 右区间的左右端点.

## return value

* get\<0\>(), 2个区间相交的长度. 如果为0, 则表示这2个区间不相交.
* get<1>(), 2个区间相交的区间. 如果区间不相交, 则这个返回值无意义.