#include <iostream>
#include <mutex>
#include <memory>
#include <thread>
using namespace std;

class Singleton{

public:
    ~Singleton(){};
    static Singleton& GetInstance(){
        return instance;
    }
    void print() const{
        std::cout << "data:"<< data<<std::endl;
    }
    void set(int val){                                  // 成员写线程安全
        std::unique_lock<mutex> lock(mtx);
        data = val;
    }
private:
    explicit Singleton(int data):data(data){};
    int data;
    static Singleton instance;
    static std::mutex mtx;
};
std::mutex Singleton::mtx;
Singleton Singleton::instance(10);

// g++ -Wall -g singletonEager.cpp  -fsanitize=address -fno-omit-frame-pointer -o singletonEager
int main(){
    Singleton inst = Singleton::GetInstance();
    inst.print();
    inst.set(6);
    inst.print();
}