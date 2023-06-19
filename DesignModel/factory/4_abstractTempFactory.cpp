/*** 
 * @Descripttion: https://www.cnblogs.com/xiaolincoding/p/11524376.html#%E5%B7%A5%E5%8E%82%E6%96%B9%E6%B3%95%E6%A8%A1%E5%BC%8F
 * 抽象模板工厂模式的特点：
 *  1. 提供一个接口，可以创建多个产品族中的产品对象。如创建耐克工厂，则可以创建耐克鞋子产品、衣服产品、裤子产品等。
 * 缺点：
 *  1. 新增一个产品，就需要增加一个对应的产品的具体工厂类。
 * @version: 
 * @Author: lhw
 * @Date: 2023-05-16 12:04:51
 * @FilePath: /C++/DesignModel/factory/4_abstractTempFactory.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-05-16 18:05:18
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

// 抽象工厂类：类型为抽象产品
template<typename AbstractProduct_t>
class AbstractFactory{
public:
    virtual AbstractProduct_t *createProduct() =0;
    virtual ~AbstractFactory(){};

};

// 具象模板工厂类
template<typename AbstractProduct_t, typename ConcreteProduct_t>
class ConcreteFactory: public AbstractFactory<AbstractProduct_t>{
public:
    AbstractProduct_t* createProduct() override{
        return new ConcreteProduct_t();
    }
};



// g++ abstractTempFactory.cpp -o abstractTempFactory 
int main(){

    ConcreteFactory<Shoes, NikeShoes> nikeShoesFactory;
    // ConcreteFactory<Shoes, NikeShoes> nikeShoesFactory;
    Shoes* shoes= nikeShoesFactory.createProduct();
    shoes->show();

    ConcreteFactory<Clothe, NikeClothe> nikeClotheFactory;
    Clothe * clothe = nikeClotheFactory.createProduct();
    clothe->show();

    delete shoes;
    delete clothe;
    
    

}