
# build
```bash
mkdir build && cd build
cmake ..
make -j

```

- `algorithm`：一些算法
  - `graph`：图
     - `1_1_MinSpanTree_Prim`：最小生成树的`prim`算法
     - `1_2_MinSpanTree_Kruskal`：最小生成树的`Kruskal`算法
     - `2_1_MinPath_Dijkstra`：无向图/有向图的`Dijkstra`算法
  - `lru`：LeetCode的LRU算法
  - `sort`：十大排序
  - `InterviewQuestion`：面试中遇到的一些算法题
     1. 判断大小端
     2. 两个数取较大值，不能用if、< 等判断条件，[面试题 16.07. 最大数值](https://leetcode.cn/problems/maximum-lcci/description/)
     3. 实现双向链表+翻转双向链表
  - `Trie`：前缀树
- `DesignModel`：一些设计模式
  - `工厂模式`
  - `生产消费者模式`
  - `单例模式`
  - `observer_pattern`：观察者模式：原生指针和weak_ptr两个版本
- `MyDesign`:手撕的一些STL或C++11新特性
  - `1_MyAllocate`：手动实现的allocate分配器
  - `2_MySharedPtr`：手动实现的shared_ptr
  - `3_MyVector`：手动实现的vector
  - `4_unique_ptr`：手动实现的unique_ptr
  - `5_Mystring`：手动实现的string
  - `6_MyIteratorSList`：手动实现了单链表+迭代器
- `thread`：线程类
  - `threadpool`：线程池，包含C++11和C++14版本
    - `ThreadPool.cpp`：支持类成员函数和普通函数
  - 