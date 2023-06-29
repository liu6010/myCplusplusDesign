#include <iostream>
#include <atomic>
#include <mutex>
using namespace std;

class shared_count{
public:
    shared_count():m_count(1){}
    void add_count(){
        ++m_count;
    }
    long long int reduce_count(){
        return --m_count;
    }
    long long int get_count() const{
        return m_count;
    }
private:
    long long int m_count;

};

template<typename T>
class Mshared_ptr{
public:
    using value_type = T;
    Mshared_ptr():_ptr(nullptr), _count_ptr(nullptr){}
    explicit Mshared_ptr(T* ptr): _ptr(ptr){
        if(ptr){
            _count_ptr = new shared_count();
        }
        std::cout << " default constructor ." << std::endl;
    }
    ~Mshared_ptr(){
        if(_ptr && !_count_ptr->reduce_count()){        // 如果在使用期间将归属权给了其他对象，为了防止二次delete所以需要判定是否为nullptr
            delete _count_ptr;
            delete _ptr;
        }
        std::cout << " ~ constructor ." << std::endl;

    }
    Mshared_ptr(Mshared_ptr<T>& obj):_ptr(obj._ptr), _count_ptr(obj._count_ptr){
        _count_ptr->add_count();
        std::cout << " copy constructor ." << std::endl;

    }
    Mshared_ptr(Mshared_ptr<T>&& obj):_ptr(obj._ptr), _count_ptr(obj._count_ptr){
        obj._ptr=nullptr;
        obj._count_ptr=nullptr;
        std::cout << " move constructor ." << std::endl;

    }

    Mshared_ptr& operator=(Mshared_ptr<T>& obj){
        if(&obj == this) return obj;
        if(_ptr && _count_ptr->reduce_count() == 0){
            delete _ptr;
            delete _count_ptr;
        }
        if(obj._ptr){
            _ptr = obj._ptr;
            _count_ptr = obj._count_ptr;
            _count_ptr->add_count();
        }
        std::cout << " copy = constructor ." << std::endl;

        return *this;
    }
    Mshared_ptr& operator=(Mshared_ptr<T>&& obj){
        if(_ptr && _count_ptr->reduce_count()==0){
            delete _ptr;
            delete _count_ptr;
        }
        if(obj._ptr){
            _ptr = obj._ptr;
            _count_ptr = obj._count_ptr;
            obj._ptr = nullptr;
            obj._count_ptr = nullptr;
        }
        std::cout << " move = constructor ." << std::endl;

        return *this;

    }
    T* operator ->(){
        return _ptr;
    }
    T& operator *(){
        return *_ptr;
    }
    T* get(){
        return _ptr;
    }
    bool unique() const{
        if(_ptr && _count_ptr->get_count() == 1) return true;
        return false;
    }
    long long int use_count(){
        if(_ptr){
            return _count_ptr->get_count();
        }
        return 0;
    }
    void swap(Mshared_ptr<T>& obj){
        swap(_ptr, obj._ptr);
        swap(_count_ptr, obj._count_ptr);
    }
    void reset(T* ptr=nullptr){
        if(_ptr){
            _count_ptr->reduce_count();
            _ptr = nullptr;
            _count_ptr = nullptr;
        }
        if(ptr){
            _ptr = ptr;
            _count_ptr = new shared_count();
        }
    }


private:
    T* _ptr;
    shared_count* _count_ptr;
};


// g++ ../MySharedPtr.cpp -o mshared_ptr -g -fsanitize=address
int main(){
    Mshared_ptr<int> test = Mshared_ptr<int>(new int(0));
    {
        // 拷贝构造
        Mshared_ptr<int> test2 = test;
        std::cout << test2.use_count() << std::endl;
    }
    {
        // 移动构造
        Mshared_ptr<int> test2 = std::move(test);
        std::cout << test2.use_count() << std::endl;
    }
    test.reset(new int(1));
    {
        // 拷贝操作符
        Mshared_ptr<int> test3(new int(2));
        Mshared_ptr<int> test2 = test3;
        std::cout <<" before 拷贝操作符:test3.count:"<< test3.use_count() << std::endl;

        test2 = test;
        std::cout <<" after 拷贝操作符:test3.count:"<< test3.use_count() << std::endl;
    }
    {
        // 移动操作符
        Mshared_ptr<int> test3(new int(2));
        test3 = std::move(test);
        std::cout <<" after 拷贝操作符:test3.val:"<< *test3.get() << std::endl;
    }
    std::cout << test.use_count() << std::endl;
}