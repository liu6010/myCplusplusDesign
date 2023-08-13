/*** 
 * @Descripttion: 设计模式之观察者模式
 * 使用weak_ptr实现对观察者的管理
 * @version: 
 * @Author: lhw
 * @Date: 2023-08-13 11:19:02
 * @FilePath: /myCplusplusDesign/DesignModel/observe_pattern/ObservePattern_WeakPtr.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-08-13 13:05:28
 */
#include <iostream>
#include <memory>
#include <list>
using namespace std;

class Subject;      
class Observe;

// 抽象主题对象
class Subject{              
public:
    virtual ~Subject()=default;
    // 添加观察者
    virtual void Attach(std::weak_ptr<Observe> sub){            
        // 检测当前weak_ptr是否为同一个观察者
        // 优化方式：保存观察者的唯一id建立hash表 
        for (auto it = m_pObserver_list.begin(); it != m_pObserver_list.end(); ++it) {
            if (auto shared = it->lock()) {
                if (shared == sub.lock()) return ;
            }
            else{
                // 遇到悬空就删除
                it = m_pObserver_list.erase(it);     
            }
        }
        m_pObserver_list.emplace_back(sub); 
    }
    virtual void Detach(const std::weak_ptr<Observe> sub){
        for (auto it = m_pObserver_list.begin(); it != m_pObserver_list.end();++it) {       // 搜索每个观察者
            if (auto shared = it->lock()) {                                             // 获取shared_ptr，并检测是否空悬
                if (shared == sub.lock()) {                                             // 判断是否与待删除的相等
                    it = m_pObserver_list.erase(it);                                    // 删除该对象，并获取下一个指针
                    // break;   
                } else {
                    ++it; 
                }
            } else {
                it = m_pObserver_list.erase(it);                                        // 删除失效的观察者
            }
        }
    }
    virtual void NotifyAll() =0;
    virtual const string& GetSubject() const = 0;
    virtual void UpdateSubject(const string& newSubject){};
protected:
    std::list<std::weak_ptr<Observe>> m_pObserver_list;
};

class Observe{
public:
    virtual ~Observe()=default;
    virtual const string& GetName() const{
        return m_ObserveName;
    }
    virtual void GetSubject()=0;
protected:
    string m_ObserveName;
    std::shared_ptr<Subject> m_Observe;
};

class ConcreteSubject:public Subject{       // 实体主题，该对象的主题是sring内容
public:
    ConcreteSubject(const string& newSubject=""):m_Subject(newSubject){
        m_pObserver_list.clear();
    }
    void UpdateSubject(const string& newSubject) override{
        m_Subject = newSubject;
        std::cout<<"update.subject is: "<<m_Subject<<std::endl;
    }
    void NotifyAll() override{
        for (auto it = m_pObserver_list.begin(); it != m_pObserver_list.end(); ++it) {
            auto shared = it->lock();
            if (shared) {
                shared->GetSubject();
            }
        }
    }
    const string& GetSubject() const override {
        return m_Subject;
    }
private:
    string m_Subject;       // 主题发布的内容，这里是一个string

};

class ConcreteObserve:public Observe{
public:
    ConcreteObserve(std::shared_ptr<Subject>& observe, string observeName="unknown"){
        m_ObserveName = observeName;
        m_Observe = observe;        // 初始化观察者观察的主题指针
    }
    void GetSubject() override{
        std::cout << GetName() << " get the subject is: "
                  << m_Observe->GetSubject() << std::endl;
    }
};


int main(){

    std::shared_ptr<Subject> pSub = std::shared_ptr<ConcreteSubject>(new ConcreteSubject("first"));
    std::shared_ptr<Observe> pObs1 = std::shared_ptr<ConcreteObserve>(new ConcreteObserve(pSub, "obs1"));
    std::shared_ptr<Observe> pObs2 = std::shared_ptr<ConcreteObserve>(new ConcreteObserve(pSub, "obs2"));

    pSub->Attach(pObs1);
    pSub->Attach(pObs2);
    // std::cout<< pObs1->GetName() << std::endl;
    pObs1->GetSubject();
    pObs2->GetSubject();
    pSub->UpdateSubject("second");
    pSub->NotifyAll();


}