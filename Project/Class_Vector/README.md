# Questions:vector
### 迭代器失效
- insert和erase后都不要在访问使用的迭代器了。
- insert如果真的要用就使用返回值更新迭代器使用。
- 不同操作系统对迭代器失效的处理有所不同。
### 深浅拷贝 
### 迭代器类型

### 其他
-匿名对象生命周期只在其所在行，但是 const& 可以延长匿名对象的生命周，直到引用对象域结束