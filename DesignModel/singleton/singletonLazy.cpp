#include <iostream>
#include <mutex>
#include <memory>
#include <thread>
using namespace std;

class Singleton{
public:
    using Ptr = std::shared_ptr<Singleton>;
public:
    explicit Singleton(int data):data(data){};
    ~Singleton(){};
    static Ptr GetInstance(int data){
        static Ptr ptr  = std::make_shared<Singleton>(data);        // C++11规定了local static在多线程条件下的初始化行为，要求编译器保证了内部静态变量的线程安全性。
        return ptr;
    }
    void print() const{
        std::cout << "data:"<< data<<std::endl;
    }
    void set(int val){                                  // 成员写线程安全
        std::unique_lock<mutex> lock(mtx);
        data = val;
    }
private:
    int data;
    std::mutex mtx;
};

// 成员变量线程不安全，实例创建线程安全
class SingletonB{
public: 
    using Ptr = std::shared_ptr<SingletonB>;
public:
    static Ptr getInstance(int val){
        static Ptr ptr = std::shared_ptr<SingletonB>(new SingletonB(val));
        return ptr;
    }
    void print() const{
        std::cout << "data:"<< data<<std::endl;
    }
    void set(int val){      // 线程不安全
        data = val;
    }
private:
    SingletonB(int val):data(val){};

    int data;

};

void getInstac(std::shared_ptr<Singleton>& instance){
    std::cout << "count: " << instance.use_count() << std::endl;
    instance->set(6);
    instance->print();

}

// g++ -Wall -g singletonLazy.cpp  -fsanitize=address -fno-omit-frame-pointer -o singleetonLazy
int main(){
    int data = 10;
    auto ptr = Singleton::GetInstance(data);
    ptr->print();
    // int* q = new int(10);
    std::cout << "count: " << ptr.use_count() << std::endl;

    getInstac(ptr);
    ptr->print();
}