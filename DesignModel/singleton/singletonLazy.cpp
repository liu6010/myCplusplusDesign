/*** 
 * @Descripttion: 创建线程安全，但是数据成员不是线程安全
 * @version: 
 * @Author: lhw
 * @Date: 2023-05-16 09:43:48
 * @FilePath: myCplusplusDesign/DesignModel/singleton/singletonLazy.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-06-30 10:32:22
 */
#include <iostream>
#include <mutex>
#include <memory>
#include <thread>
using namespace std;



// ----     静态局部变量     ----//
class SingletonB{
public:
    using Ptr = std::shared_ptr<SingletonB>;
public:
    SingletonB() = delete;
    SingletonB(const SingletonB&) = delete;
    SingletonB& operator= (const SingletonB&) = delete;
    static Ptr GetInstance(int val){
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
// ----     静态局部变量     ----//

// ----     双重锁定     ----//
class SingletonC{
public:
    using Ptr = std::shared_ptr<SingletonC>;
public:
    SingletonC() = delete;
    SingletonC(const SingletonC&) = delete;
    SingletonC& operator= (const SingletonC&) = delete;
    static Ptr GetInstance(int val){
        if(ptr==nullptr){
            std::lock_guard<mutex> lk(_mtx);
            if(ptr == nullptr){
                ptr = std::shared_ptr<SingletonC>(new SingletonC(val));
            }
        }
        return ptr;
    }
    void print() const{
        std::cout << "data:"<< data<<std::endl;
    }
    void set(int val){      // 线程不安全
        data = val;
    }
private:
    SingletonC(int val):data(val){};
    int data;
    static std::mutex _mtx;
    static Ptr ptr;
};
SingletonC::Ptr SingletonC::ptr = std::shared_ptr<SingletonC>();
std::mutex SingletonC::_mtx;
// ----     双重锁定     ----//



void getInstance(std::shared_ptr<SingletonC> instance){
    std::cout << "count: " << instance.use_count() << std::endl;
    instance->set(6);
    instance->print();

}

// g++ -Wall -g ./singletonLazy.cpp  -fsanitize=address -fno-omit-frame-pointer -o singletonLazy
int main(){
    int data = 10;
    auto ptr = SingletonC::GetInstance(data);
    ptr->print();
    // int* q = new int(10);
    std::cout << "count: " << ptr.use_count() << std::endl;

    getInstance(ptr);
    ptr->print();
}