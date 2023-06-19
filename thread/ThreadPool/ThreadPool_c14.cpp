// #pragma once
#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <queue>
#include <functional>               // std:;function
#include <future>                   // std::packaged_task
#include <condition_variable>
#include <algorithm>
#include <mutex>
#include <atomic>
using namespace std;


class ThreadPool{
public:
    using Ptr = std::shared_ptr<ThreadPool>;
    using taskType = std::function<void(void)>;
public:
    static Ptr getInstance(const int& threadNum){
        auto p = std::shared_ptr<ThreadPool>(new ThreadPool(threadNum));
        return p;
    }
    ~ThreadPool(){
        if(_is_run){
            wait();
            stop();
        }
    }

    template<typename FunT, typename... ParaT>
    auto submit(FunT&& f, ParaT&&... param){
    // decltype(auto) submit(FunT&& f, ParaT&&... param){
        auto task = std::make_shared<std::packaged_task<decltype(f(param...))()>>(
            std::bind(std::forward<FunT>(f), std::forward<ParaT>(param)...)
        );
        {
            std::unique_lock<mutex> lock(_mtx_task);
            _task_pool.emplace([task](){(*task)();});
        }
        _cvTaskEpy.notify_one();
        return task->get_future();

    }

    void wait(){
        std::unique_lock<mutex> lock(_mtx_task);
        _cvTaskFin.wait(lock, [this](){return !(_running_num>0 || !_task_pool.empty());});
    }
    
    void stop(){
        _is_run = false;
        _cvTaskEpy.notify_all();
        for(auto& t:_thread_pool){
            if(t.joinable()) t.join();
        }
    }

private:
    int _thread_num;
    std::atomic<bool> _is_run;
    std::atomic<int> _running_num;
    vector<std::thread> _thread_pool;
    queue<taskType> _task_pool;
    std::condition_variable _cvTaskEpy;
    std::condition_variable _cvTaskFin;
    std::mutex _mtx_task;

    ThreadPool(const int& threadNum): _thread_num(min(threadNum, (int)std::thread::hardware_concurrency())), _is_run(true), _running_num(0)
    {
        for(int i=0; i< _thread_num; i++) 
            _thread_pool.emplace_back([this](){
                while(true){
                    taskType task;
                    {
                        std::unique_lock<mutex> lock(_mtx_task);
                        _cvTaskEpy.wait(lock, [this](){return !(_is_run && _task_pool.empty());});       // 条件为false为上锁
                        // while(_is_run && _task_pool.empty()) _cvTaskEpy.wait(lock);
                        if(!_is_run && _task_pool.empty()) break;
                        task = std::move(_task_pool.front());
                        _task_pool.pop();
                        _running_num++;
                    }
                    task();
                    _running_num--;
                    _cvTaskFin.notify_one();
                }
            });
    }
};





// g++ -std=c++14 ThreadPool_c14.cpp -o ThreadPool_c14
int main(){
    std::cout <<"std::thread::hardware_concurrency():"<<std::thread::hardware_concurrency() << std::endl;
    int size = 5;
    vector<int> nums(size);
    for(int i=0; i<size; i++){
        nums[i] = i;
    }
    auto func = [](int& i){
        int tmp = i;
        i = i*i;
        std::cout<<"thread id:"<<std::this_thread::get_id() << " " << tmp << "^2: "<< i <<std::endl;
    };
    auto p = ThreadPool::getInstance(10);

    for(auto& n:nums){
        p->submit(func, ref(n));
    }
    p->wait();
    // std::this_thread::sleep_for(std::chrono::seconds(1));
    for(auto& n:nums){
        cout <<"n:" << n<<" ";
    }
    cout <<endl;
}
