/*** 
 * @Descripttion: https://www.cnblogs.com/xiaolincoding/p/11524376.html#%E5%B7%A5%E5%8E%82%E6%96%B9%E6%B3%95%E6%A8%A1%E5%BC%8F
 * 工厂方法模式的特点：
 *  1. 工厂方法模式抽象出了工厂类，提供创建具体产品的接口，交由子类去实现。
 *  2. 工厂方法模式的应用并不只是为了封装具体产品对象的创建，而是要把具体产品对象的创建放到具体工厂类实现。
 * 缺点：
 *  1. 新增一个产品，就需要增加一个对应的产品的具体工厂类。
 *  2. 一条生产线只能一个产品
 * @version: 
 * @Author: lhw
 * @Date: 2023-05-16 12:04:51
 * @FilePath: /myCplusplusDesign/DesignModel/factory/2_methodFactory.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-06-19 21:22:29
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

class LiNingShoes:public Shoes{
public:
    void show()override{
        std::cout << "LiNing!" << std::endl;
    }
};

class AdidasShoes:public Shoes{
public:
    void show()override{
        std::cout << "Adidias!" << std::endl;
    }
};

// 抽象鞋类工厂类
class ShoesFactory{
public:
    virtual ~ShoesFactory(){};
    virtual Shoes* createShoes()=0;

};

// 产品线类
class NikeProductor: public ShoesFactory{
public:
    Shoes* createShoes() override{
        return new NikeShoes();
    }
};

class LiNingProductor: public ShoesFactory{
public:
    Shoes* createShoes() override{
        return new LiNingShoes();
    }
};

class AdidasProductor: public ShoesFactory{
public:
    Shoes* createShoes() override{
        return new AdidasShoes();
    }
};


// g++ methodFactory.cpp -Wno-invalid-offsetof -o methodFactory 
int main(){
    std::cout << "sizeof(Shoes):"<< sizeof(Shoes) << std::endl;     // 8bytes：vptr
    // std::cout << "sizeof(NikeShoes):"<< sizeof(NikeShoes)<<" offsetof(a):"<< offsetof(NikeShoes, a) << std::endl;     // 16b bytes：8bytes(vptr) + 4byte(int)+4byte(padding)

    ShoesFactory* factory;
    {
        factory = new NikeProductor();
        auto pShoes = std::shared_ptr<Shoes>(factory->createShoes());
        pShoes->show();
    }
    {
        factory = new AdidasProductor();
        auto pShoes = std::shared_ptr<Shoes>(factory->createShoes());
        pShoes->show();
    }
    {
        factory = new LiNingProductor();
        auto pShoes = std::shared_ptr<Shoes>(factory->createShoes());
        pShoes->show();
    }
    
    delete factory;

}