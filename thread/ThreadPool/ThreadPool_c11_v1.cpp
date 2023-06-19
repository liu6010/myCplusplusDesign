/*** 
 * @Descripttion: 线程池
 * @version: v1.0
 * @Author: lhw
 * @Date: 2023-04-19 16:46:18
 * @FilePath: /ThreadPool/ThreadPool_c11_v1.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-04-19 16:47:45
 */
// #pragma once
#include <iostream>
#include <thread>
#include <memory>
#include <vector>
#include <queue>
#include <functional>
#include <future>  // std::packaged_task
#include <condition_variable>
#include <algorithm>
#include <mutex>
#include <atomic>
using namespace std;
/*

1. 线程队列
2. 生产者消费者模型
3. 任务提交函数
4. stop
*/
const int ThreadMax = std::thread::hardware_concurrency();


class ThreadPool{
public:
    using Ptr = std::shared_ptr<ThreadPool>;
public:
    ThreadPool(const int& thread_num);

    // 单例模式
    ~ThreadPool(){              // RAII，资源获取即初始化
        if(m_running_){         //  没有主动调用stop就析构时，如果有任务在进行，等待所有任务进行完，然后设置为不可联结状态
            wait();
            stop();     // 所有任务都结束后再使所有线程都处于不可联结状态
        }

        
    }
    static Ptr GetInstant(const int& thread_num);


    void wait();

    void stop();
    
    template<typename FuncType, typename... ParamType>
    auto submit(FuncType&& f, ParamType&&... params)
        -> std::future<typename std::result_of<FuncType(ParamType...)>::type> 
    {
        using returnType = typename std::result_of<FuncType(ParamType...)>::type;
        auto task = std::make_shared<std::packaged_task<returnType()>>(
            std::bind(std::forward<FuncType>(f), std::forward<ParamType>(params)...)
        );
        {
            std::unique_lock<mutex> locker(m_task_lock_);
            m_tasks_.emplace([task](){(*task)();});
        }
        // 通知
        m_task_cond_.notify_one();
        return task->get_future();

    }

private:
    void WorkerFunc(const int& id);
    ThreadPool() = delete;
     // 初始化线程数量
    // ThreadPool(const int& thread_num): num_wokers_(thread_num)

    int num_wokers_;
    vector<std::thread> m_workers_;
    std::queue<std::function<void()>> m_tasks_;   // 任务队列
    atomic<bool> m_running_{true};
    atomic<int> m_running_num_{0};
    // atomic_int m_running_ = 11;
    condition_variable m_task_cond_;            // 任务运行条件变量
    condition_variable m_finish_cond_;          // 任务结束条件变量，在用户调用或析构函数调用

    std::mutex m_task_lock_;

};

ThreadPool::ThreadPool(const int& thread_num): num_wokers_(thread_num)
{
    m_workers_.resize(num_wokers_);
    for(int i=0; i< num_wokers_;i++){
        m_workers_[i] = std::thread(&ThreadPool::WorkerFunc, this, i);
    }
}

ThreadPool::Ptr ThreadPool::GetInstant(const int& thread_num){
    static auto t_pool = std::make_shared<ThreadPool>(thread_num);
    // static auto t_pool = std::shared_ptr<ThreadPool>(new ThreadPool(thread_num));
    std::cout<<"shared class ThreadPool num:"<< t_pool.use_count()  <<endl;;
    return t_pool;
}

// 给每个子线程添加任务
void ThreadPool::WorkerFunc(const int& id){
    // std::thread::id thread_id = std::this_thread::get_id();
    // cout << "thread id:"<< thread_id <<endl;
    std::function<void(void)> task;     // 可调用对象
    while(true){
        // 1. 任务队列空了，但是没有线程在运行：等待
        // 2. 任务队列空了，没有其他线程在运行：结束循环
        // 3. 任务队列非空：从任务队列里面取出任务运行
        {
            // 获取任务，只能同时有一个线程同时获取任务操作m_workers_
            unique_lock<mutex> locker(m_task_lock_);
            while(m_running_ && m_tasks_.empty()){       // 等待其他线程结束
                m_task_cond_.wait(locker);                  // 等待其他任务都结束时被唤醒，或有任务添加进来时唤醒
            }
            if((!m_running_) && m_tasks_.empty()) break;     // 只有调用stop的时候才会结束所有线程
            m_running_num_++;
            task = std::move(m_tasks_.front());
            m_tasks_.pop();
        }
        task();     // 执行使用任务包装器包装的任务
        m_running_num_--;   // 任务执行结束
        // 执行结束唤醒因调用wait()的线程
        m_finish_cond_.notify_all();
    }
}

void ThreadPool::stop() {    // 结束所有的线程
    std::unique_lock<mutex> locker(m_task_lock_);
    m_running_ = false;     // 
    locker.unlock();
    m_task_cond_.notify_all();      // 唤醒所有正在等待的线程
    for(int i=0; i < num_wokers_;i++){    // 将所有线程销毁,将线程设置为不可联结状态
        if(m_workers_[i].joinable()){
            m_workers_[i].join();
        }
    }
    m_finish_cond_.notify_all();        // 唤醒所有等待线程
}

void ThreadPool::wait(){
    // 等待所有任务完成finish
    std::unique_lock<mutex> locker(m_task_lock_);
    while(m_running_num_>0 || m_tasks_.size()>0){
        m_finish_cond_.wait(locker);
    }
}



int main(){

    auto threadpool = ThreadPool::GetInstant(2);

    vector<int> nums  = {1, 2, 3,4, 5,6};
    
    auto square = [](int& i)
                    { 
                        i = i*i;

                        cout << "thread id:"<< std::this_thread::get_id() << " i^2="<<i <<endl;
                        return i;
                    };

    for(auto& num:nums){
       auto res = threadpool->submit(square, ref(num));
    //    cout<<"num:"<< res << endl;
    }

    // threadpool->submit(square, nums[2]);

    threadpool->wait();

    for(auto& num:nums){
       cout<<"num:"<< num << endl;
    }

}