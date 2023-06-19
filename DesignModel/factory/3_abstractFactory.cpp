/*** 
 * @Descripttion: https://www.cnblogs.com/xiaolincoding/p/11524376.html#%E5%B7%A5%E5%8E%82%E6%96%B9%E6%B3%95%E6%A8%A1%E5%BC%8F
 * 抽象工厂模式的特点：
 *  1. 提供一个接口，可以创建多个产品族中的产品对象。如创建耐克工厂，则可以创建耐克鞋子产品、衣服产品、裤子产品等。
 * 缺点：
 *  1. 新增一个产品，就需要增加一个对应的产品的具体工厂类。
 * @version: 
 * @Author: lhw
 * @Date: 2023-05-16 12:04:51
 * @FilePath: /C++/DesignModel/factory/abstractFactory.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-05-16 17:07:45
 */
#include <iostream>
#include <memory>
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

// 抽象鞋类工厂类
class ShoesFactory{
public:
    virtual ~ShoesFactory(){};
    virtual Shoes* createShoes()=0;
    virtual Clothe* createClothe()=0;

};

// 产品线类
class NikeProductor: public ShoesFactory{
public:
    Shoes* createShoes() override{
        return new NikeShoes();
    }
    Clothe* createClothe() override{
        return new NikeClothe();
    }
};



// g++ abstractFactory.cpp -Wno-invalid-offsetof -o abstractFactory 
int main(){

    ShoesFactory* factory;
    {
        factory = new NikeProductor();
        auto pShoes = std::shared_ptr<Shoes>(factory->createShoes());
        pShoes->show();
        auto pClothe = std::shared_ptr<Clothe>(factory->createClothe());
        pClothe->show();
    }
    
    
    delete factory;

}