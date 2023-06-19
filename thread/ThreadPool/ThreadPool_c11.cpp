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
public:
    static Ptr GetInstance(const int& num_threads=8){
        auto pThread = std::shared_ptr<ThreadPool>(new ThreadPool(num_threads));
        return pThread;
    }

    ~ThreadPool(){
        if(_is_running){
            wait();
            stop();
        }

    }
    void wait(){
        std::unique_lock<mutex> lock(_task_mtx);
        while(_running_task_num > 0 || _task_pool.size()>0){
            _finished_cv.wait(lock);
        }
    }

    void stop(){
        _is_running = false;
        _running_cv.notify_all();
        for(auto& t:_thread_pool){
            if(t.joinable()) t.join();
        }
        // _finished_cv.notify_all();      // ?不需要
    }
    template<typename FuncT, typename... ParamT>
    auto submit(FuncT&& f, ParamT&&... params)->std::future<typename std::result_of<FuncT(ParamT...)>::type>
    {
        using returnType = typename std::result_of<FuncT(ParamT...)>::type;
        auto task = std::make_shared<std::packaged_task<returnType()>>(
            std::bind(std::forward<FuncT>(f), std::forward<ParamT>(params)...)
        );
        {
            std::unique_lock<mutex> lock(_task_mtx);
            _task_pool.emplace([task](){(*task)();});
        }
        _running_cv.notify_one();
        return task->get_future();
    }

private:
    ThreadPool(const int& num_threads)
        :_thread_num(min(num_threads, (int)std::thread::hardware_concurrency())), _is_running(true), _running_task_num(0)
    {
        for(int i=0;i<_thread_num;i++){
            _thread_pool.emplace_back(
                [this](){
                    std::function<void()> task;
                    while(true){
                        {
                            std::unique_lock<mutex> lock(_task_mtx);
                            while(_is_running && _task_pool.empty()) _running_cv.wait(lock);
                            if((!_is_running)  && _task_pool.empty()) break;
                            task = std::move(_task_pool.front());
                            _task_pool.pop();
                            _running_task_num++;
                        }
                        task();
                        _running_task_num--;
                        _finished_cv.notify_all();  // 唤醒一个？
                    }
                }
            );
        }

    }

    int _thread_num;
    vector<std::thread> _thread_pool;
    queue<std::function<void()>> _task_pool;
    atomic<int> _running_task_num;
    atomic<bool> _is_running;
    std::condition_variable _running_cv;
    std::condition_variable _finished_cv;
    std::mutex _task_mtx;

};

// g++ -std=c++11 ThreadPool_c11.cpp -o ThreadPool_c11
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
    auto p = ThreadPool::GetInstance(10);

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
