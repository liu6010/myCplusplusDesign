/*** 
 * @Descripttion: https://www.cnblogs.com/xiaolincoding/p/11524376.html
 * 产品注册模板类+单例工厂模板类的特点：
 *  1. 只有一个工厂，通过产品牌注册接口来生产特点的产品
 * 缺点：
 *  
 * @version: 
 * @Author: lhw
 * @Date: 2023-05-16 12:04:51
 * @FilePath: /C++/DesignModel/factory/5_abstractTempSingleFactory.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-05-16 20:44:15
 */
#include <iostream>
#include <memory>
#include <map>
using namespace std;


// 抽象鞋类
class Shoes{
public:
    virtual ~Shoes(){};
    virtual void show()=0;
};

class NikeShoes:public Shoes{
public:
    void show()override{
        std::cout << "Nike!" << std::endl;
    }
    int a=0;
};

class Clothe{
public:
    virtual ~Clothe(){};
    virtual void show()=0;
};

class NikeClothe:public Clothe{
public:
    void show() override{
        std::cout << "Nike clothe!" << std::endl;
    }
};

// 抽象工厂类：类型为抽象产品
template<typename AbstractProduct_t>
class AbstractFactory{
public:
    virtual AbstractProduct_t *createProduct() =0;
    virtual ~AbstractFactory(){};

};

template<typename AbstractProduct_t>
class IPProductRegister{
public:
    virtual ~IPProductRegister(){};
    virtual AbstractProduct_t* CreateProduct()=0;    // 返回注册的类型
    
};

// 具象模板工厂类
template<typename AbstractProduct_t>
class ConcreteFactory{
public:
    static ConcreteFactory& GetInstance(){
        static ConcreteFactory<AbstractProduct_t> instance;
        return instance;
    }
    // 产品注册
   void RegisterProduct(IPProductRegister<AbstractProduct_t> *registrar, std::string name)
   {
      IpMap[name] = registrar;
   }
   AbstractProduct_t* GetProduct(std::string name){
        if(IpMap.find(name) != IpMap.end()){
            return IpMap[name]->CreateProduct();
        }
        std::cout << "No product found for " << name << std::endl;
        return nullptr;
   }

private:
    std::map<std::string, IPProductRegister<AbstractProduct_t>*> IpMap;
};

template<typename AbstractProduct_t, typename ConcreteProduct_t>
class ProductRegister:public IPProductRegister<AbstractProduct_t>{
public:
    explicit ProductRegister(std::string name){
        ConcreteFactory<AbstractProduct_t>::GetInstance().RegisterProduct(this, name);
    }
    AbstractProduct_t* CreateProduct() override{
        return new ConcreteProduct_t();
    }
    
};

// g++ 5_abstractTempSingleFactory.cpp -o abstractTempSingleFactory  -Wall -g -fsanitize=address -fno-omit-frame-pointer 
int main(){

    ProductRegister<Shoes, NikeShoes> nikeShoes("nikeShoes");
    Shoes* pNikeShoes = ConcreteFactory<Shoes>::GetInstance().GetProduct("nikeShoes");
    std::cout << "nike shoes factory static address:"<< &ConcreteFactory<Shoes>::GetInstance() << std::endl;
    if(pNikeShoes)
        pNikeShoes->show();

    delete pNikeShoes;

    ProductRegister<Clothe, NikeClothe> nikeClothe("nikeClothe");
    Clothe* pNikeClothe = ConcreteFactory<Clothe>::GetInstance().GetProduct("nikeClothe");
    std::cout << "nike clothe factory static address:"<< &ConcreteFactory<Shoes>::GetInstance() << std::endl;
    
    if(pNikeClothe)
        pNikeClothe->show();

    delete pNikeClothe;
}