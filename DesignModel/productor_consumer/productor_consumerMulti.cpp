#include <iostream>
#include <memory>
#include <queue>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <functional>
#include <atomic>
#include <chrono>
#include "threadpool.hpp"

using namespace std;


template<typename T>
class SyncQueue{
private:
    queue<T> __que;
    int __capacity;
    mutex __mtx_que;
    condition_variable __cv_prod;
    condition_variable __cv_cons;
public:
    SyncQueue(int QueueSize):__capacity(QueueSize){}
    // ~SyncQueue(){};

    void productor(const T& item){
        // Process time
        // 先生产
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
       //  end
        {
            std::unique_lock<mutex> lock(__mtx_que);
            __cv_prod.wait(lock, [this](){ return !(__que.size() >= __capacity);});
            __que.push(item);
        }
        __cv_cons.notify_one();
        cout << "productor item:"<< item.i << " id:"<< std::this_thread::get_id()<<endl;
    }
    void consumer(){
        // 先消费
        T item;
       {
            std::unique_lock<mutex> lock(__mtx_que);
            __cv_cons.wait(lock, [this](){return !(__que.empty());});
            item = __que.front();__que.pop();
       }
       __cv_prod.notify_one();
       // Process time
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
       //  end
       cout<<"  consumer item:" << item.i << " id:"<< this_thread::get_id()<<endl;
    }
};

struct data
{
    int i=10;
};

void productor(SyncQueue<struct data>* pTask){
    auto pThreads = std::make_shared<ThreadPool>(2);
    int count =0;
    while (count < 20)
    {
        struct data d;
        d.i=count;
        pThreads->submit<void>(&SyncQueue<struct data>::productor, pTask, d);
        count++;
    }
    pThreads->wait();
}

void consumer(SyncQueue<struct data>* pTask){
    auto pThreads = std::make_shared<ThreadPool>(1);
    int count =0;
    while (count < 20)
    {
       
        // pThreads->submit(&SyncQueue<data>::consumer, pTask);
        pThreads->submit<void>(&SyncQueue<struct data>::consumer, pTask);
        count++;
    }
    pThreads->wait();
}

int main(){
    SyncQueue<struct data>* pTask = new SyncQueue<struct data>(30);

    thread t1(productor, pTask);
    thread t2(consumer, pTask);

    t1.join();
    t2.join();
    delete pTask;

}
