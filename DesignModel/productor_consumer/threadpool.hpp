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
    explicit ThreadPool(const int& threadNum): _thread_num(min(threadNum, (int)std::thread::hardware_concurrency())), _is_run(true), _running_num(0)
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

    template<typename RetT, typename FunT, typename... ParaT>
    auto submit(FunT&& f, ParaT&&... param){
        // using return_type = decltype(f(std::forward<ParaT>(param)...));
        using return_type = RetT;
        auto task = std::make_shared<std::packaged_task<return_type()>>(
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

    int getRunNum() const{
        return _running_num;
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
};
