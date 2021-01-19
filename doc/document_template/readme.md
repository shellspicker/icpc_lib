# 文档规范

这里的文档大部分是参考[cppreference](https://en.cppreference.com/w/)的风格来写的.

主要参考了:

[numerics library](https://en.cppreference.com/w/cpp/numeric)  
作为函数文档的参考.

[vector](https://en.cppreference.com/w/cpp/container/vector)  
作为类文档的参考.

比较经典的范例是`doc/template.h/readme.md`

## 规范

### 函数

函数列表: 一系列函数写好分类. 用表格表示.

函数可以是某个头文件直接写出的函数, 或者是一个类里面的函数.

表格形如:  

| name                | description       |
| ------------------- | ----------------- |
| 链接到另外一个文档. | 简单描述一下就好. |

链接的文档, [格式](doc_function.md).

### 类

类似函数, 表格形式.

加一个synopsis段, 写一下类原型, 参数看情况决定是否要写名称.

链接的文档, [格式](doc_class.md).