/*** 
 * @Descripttion: 
 * 简单工厂模式的特点：工厂类封装了创建具体产品对象的函数。
 *      缺点：扩展性非常差，新增产品的时候，需要去修改工厂类。
 * @version: 
 * @Author: lhw
 * @Date: 2023-05-16 12:04:51
 * @FilePath: /C++/DesignModel/factory/simpleFactory.cpp
 * @LastEditors: lhw
 * @LastEditTime: 2023-05-16 15:19:58
 */
#include <iostream>
using namespace std;


// 抽象鞋类
class Shoes{
public:
    virtual ~Shoes(){};
    virtual void show()=0;
};

class Nike:public Shoes{
public:
    void show(){
        std::cout << "Nike!" << std::endl;
    }
};

class LiNing:public Shoes{
public:
    void show(){
        std::cout << "LiNing!" << std::endl;
    }
};

class Adidias:public Shoes{
public:
    void show(){
        std::cout << "Adidias!" << std::endl;
    }
};

enum class SHOES_TYPE{
    NIKE, LINING, ADIDIAS
};

class ShoesFactory{
public:

    Shoes* creadShoes(SHOES_TYPE type){
        switch (type)
        {
        case SHOES_TYPE::NIKE:
            return new Nike();
            break;
        case SHOES_TYPE::LINING:
            return new LiNing();
            break;
        case SHOES_TYPE::ADIDIAS:
            return new Adidias();
            break;
        default:
            return nullptr;
            break;
        }
    }

};

int main(){

    ShoesFactory facrory;
    Shoes* shoes;
    {
        shoes = facrory.creadShoes(SHOES_TYPE::NIKE);
        if(shoes)
            shoes->show();
    }
    {
        shoes = facrory.creadShoes(SHOES_TYPE::LINING);
        if(shoes)
            shoes->show();
    }
    {
        shoes = facrory.creadShoes(SHOES_TYPE::ADIDIAS);
        if(shoes)
            shoes->show();
    }
    delete shoes;

}