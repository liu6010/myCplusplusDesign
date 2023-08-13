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


class SyncQueue{
private:
    queue<int> __que;
    int __capacity;
    mutex __mtx_que;
    condition_variable __cv_prod;
    condition_variable __cv_cons;
public:
    SyncQueue(int QueueSize):__capacity(QueueSize){}
    // ~SyncQueue(){};

    void productor(const int& item){
        // Process time
        // 先生产
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
       //  end
        {
            std::unique_lock<mutex> lock(__mtx_que);
            __cv_prod.wait(lock, [this](){ return !(__que.size() >= (uint64_t)__capacity);});
            __que.push(item);
        }
        __cv_cons.notify_one();
        cout << "productor item:"<< item << " id:"<< std::this_thread::get_id()<<endl;
    }
    void consumer(){
        // 先消费
        int item;
       {
            std::unique_lock<mutex> lock(__mtx_que);
            __cv_cons.wait(lock, [this](){return !(__que.empty());});
            item = __que.front();__que.pop();
       }
       __cv_prod.notify_one();
       // Process time
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
       //  end
       cout<<"  consumer item:" << item << " id:"<< this_thread::get_id()<<endl;
    }
};


int main(){
    SyncQueue pTask(50);
    auto productor = std::bind(&SyncQueue::productor, &pTask, placeholders::_1);
    auto consumer = std::bind(&SyncQueue::consumer, &pTask);
    thread t1[3];
    thread t2[3];
    for(int i=0; i<3; i++){
        t1[i] = thread(productor, i+100);
        t2[i] = thread(consumer);
    }

    for(int i=0; i<3;i++)
    {
        t1[i].join();
        t2[i].join();
    }

}