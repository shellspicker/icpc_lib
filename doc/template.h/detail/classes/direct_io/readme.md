# direct\_io

```c++
class direct_io;
```

一个文件io类, faster than 1b.

使用streambuf实现.

至于这个类名, 是叫buffer\_io还是direct\_io, 我也不清楚, 习惯性取名direct\_io.

## member function

| name                          | description                |
| ----------------------------- | -------------------------- |
| [\(constructor\)]()           | 构造.                     |
| [\(destructor\)]()            | 析构.                     |
| [ok]()                        | 输入调用后的状态.         |
| [set\_output\_float\_digit]() | 浮点数输出: 小数点后位数. |
| [set\_bufsize]()              | 输入输出缓冲区大小.       |
| [in]()                        | 输入.                     |
| [readline]()                  | 输入一行.                 |
| [readline\_noblank]()         | 输入一行, 无视空行.       |
| [out]()                       | 输出.                     |
| [scan]() | 兼容scanf格式的输入. |
| [msg]()                       | 兼容printf格式的输出.     |

## todo

现在只支持`stdin`和`stdout`, `stderr`待支持.
