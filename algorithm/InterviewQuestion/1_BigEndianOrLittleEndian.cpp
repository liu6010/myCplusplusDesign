#include <iostream>
#include <bitset>

using namespace std;

int main(){

    int a = 0x12;

    char* b = (char*)&a;
    std::cout<<"a:" << std::bitset<sizeof(int)*8>(a)<< std::endl;
    std::cout<<"b:" << std::bitset<sizeof(int)*8>(*b)<< std::endl;
    if(*b & a){
        std::cout<<"little endian. " <<std::bitset<sizeof(int)*8>( (*b)&a )<< std::endl;
    }
    else{
        std::cout<<"big endian. "<< std::endl;

    }



    union endian{
        int a;
        char b;
    };
    endian value;
    value.a=1;
    if(value.b==1){
        std::cout<<"little endian. "<< std::endl;
    }
    else{
        std::cout<<"big endian. "<< std::endl;
    }

}

