/*** 
 * @Descripttion: 设计模式之观察者模式
 * 使用原生指针管理观察者
 * @version: 
 * @Author: lhw
 * @Date: 2023-08-13 11:19:02
 * @FilePath: /myCplusplusDesign/DesignModel/observe_pattern/ObservePattern.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-08-13 11:20:47
 */
#include <iostream>
#include <memory>
#include <list>
using namespace std;
class Subject;      
class Observe;

class Subject{              // 抽象主题对象
public:
    virtual ~Subject()=default;
    virtual void Attach(Observe* sub){
        m_pObserver_list.emplace_back(sub);
    }
    virtual void Detach(Observe* sub){
        m_pObserver_list.remove(sub);
    }
    virtual void NotifyAll() =0;
    virtual const string& GetSubject() const = 0;
    virtual void UpdateSubject(const string& newSubject){};
protected:
    std::list<Observe*> m_pObserver_list;
};

class Observe{
public:
    virtual ~Observe()=default;
    virtual void Update()=0;
    virtual const string& GetName() const{
        return m_ObserveName;
    }
    virtual void GetSubject(){};
protected:
    string m_ObserveName;
    Subject* m_Observe;
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
            if (*it) {
                (*it)->Update();
            }
        }
    }
    const string& GetSubject() const override {
        return m_Subject;
    }
private:
    string m_Subject;
};

class ConcreteObserve:public Observe{
public:
    ConcreteObserve(Subject* observe, string observeName="unknown"){
        m_ObserveName = observeName;
        m_Observe = observe;        // 初始化观察者观察的主题指针
    }
    void Update() override{
        std::cout << GetName() << " get the update.subject is: "
                  << m_Observe->GetSubject() << std::endl;
    }
    void GetSubject() override{
        std::cout << GetName() << " get the subject is: "
                  << m_Observe->GetSubject() << std::endl;
    }
};


int main(){

    Subject* pSub = new ConcreteSubject("first");
    Observe* pObs1 = new ConcreteObserve(pSub, "obs1");
    Observe* pObs2 = new ConcreteObserve(pSub, "obs2");

    pSub->Attach(pObs1);
    pSub->Attach(pObs2);
    pObs1->GetSubject();
    pObs2->GetSubject();
    pSub->UpdateSubject("second");
    pSub->NotifyAll();

    delete pSub;
    delete pObs1;
    delete pObs2;
}