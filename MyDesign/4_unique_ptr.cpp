/*** 
 * @Descripttion: 
 * @version: 
 * @Author: lhw
 * @Date: 2023-06-29 19:39:21
 * @FilePath: /myCplusplusDesign/MyDesign/4_unique_ptr.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-06-29 20:03:45
 */
#include <iostream>
#include <atomic>
#include <mutex>
#include <memory>
using namespace std;
namespace my{

template<typename T, typename Deleter = std::default_delete<T>>
class unique_ptr{
public:
    explicit unique_ptr(T* ptr=nullptr): _ptr(ptr){}
    ~unique_ptr() noexcept{
        if(_ptr){
            Deleter()(_ptr);
        }
    }
    // 拷贝构造和赋值
    unique_ptr(const unique_ptr& ) = delete;
    unique_ptr& operator = (const unique_ptr& ) = delete;
    // 移动构造和赋值
    unique_ptr(unique_ptr&& obj)noexcept : _ptr(obj.release()){}
    unique_ptr& operator = (unique_ptr&& obj) noexcept{
        reset(obj.release());
        return *this;
    }

    T* release(){
        T* temp = _ptr;
        _ptr = nullptr;
        return temp;
    }
    void reset(T* ptr=nullptr){
        if(_ptr){
            Deleter()(_ptr);
        }
        _ptr = ptr;
    }

    T* get(){
        return _ptr;
    }

    T& operator *() const{
        return *_ptr;
    }
    T* operator ->() const{
        return _ptr;
    }
    
    void swap(unique_ptr& obj){
        swap(_ptr, obj._ptr);
    }
    explicit operator bool(){
        return _ptr !=nullptr;
    }
private:
    T* _ptr;
};


};

class test{
public:
    test(){
        p = new int(9);
    }
    ~test(){
        delete p;
        std::cout << " ~ constru" << std::endl;
    }
    void print(){
        std::cout << "class test: *p:"<< *p << std::endl;

    }
    int* p;
};

struct deleter{
    void operator() (test* t) const{
        std::cout << "operator delete" << std::endl;
        delete t;
    }
};

// g++ ../4_uniquePtr.cpp -o 4_uniquePtr -g -fsanitize=address
int main(){
    int *p = new int(1);
    my::unique_ptr<int> my_unique = my::unique_ptr<int>(p);
    std::cout << "*my_unique:"<< *my_unique << std::endl;


    auto my_uniq2 = std::move(my_unique);
    std::cout << "*my_uniq2:"<< *my_uniq2 << std::endl;

    if (my_unique) {
        std::cout << "my_unique is not null" << std::endl;
    } else {
        std::cout << "my_unique is null" << std::endl;
    }
    
    my::unique_ptr<test, deleter> my_uniq3 = my::unique_ptr<test, deleter>(new test());
    my_uniq3->print();

}