
# build
```bash
mkdir build && cd build
cmake ..
make -j

```


- `MyDesign`:手撕的一些STL或C++11新特性
  - `1_MyAllocate`：手动实现的allocate分配器
  - `2_MySharedPtr`：手动实现的shared_ptr
  - `3_MyVector`：手动实现的vector
  - `4_unique_ptr`：手动实现的unique_ptr
- `thread`：线程类
  - `threadpool`：线程池，包含C++11和C++14版本