#include <iostream>
#include <algorithm>
template<typename T>
class myVec{
protected:
    T* pdata;
    int _capacity;
    int _size;
public:
    using value_type = T;
    myVec():_capacity(1), _size(0){
        pdata = new T[_capacity];
        std::cout << "default construction"<<std::endl;

    }
    ~myVec(){
        delete [] pdata;
        std::cout << "~ construction"<<std::endl;

    }
    myVec(const myVec& obj){
        std::cout << "copy construction"<<std::endl;
        _capacity = obj._capacity;
        _size = obj._size;
        pdata = new T[obj._capacity];       // 第一次构造，不需要先delete
        std::copy_n(obj.pdata, obj._size, pdata);
    }
    myVec& operator=(const myVec& obj){
        if(&obj == this) return *this;
        std::cout << "copy = construction"<<std::endl;
        if(pdata!=nullptr){
            delete [] pdata;
        }
        _capacity = obj._capacity;
        _size = obj._size;
        pdata = new T[obj._capacity];
        std::copy_n(obj.pdata, obj._size, pdata);
        return *this;
    }
    myVec(myVec&& obj): pdata(obj.pdata), _capacity(obj._capacity), _size(obj._size){
        std::cout << "move construction"<<std::endl;
        obj.pdata = nullptr;
        obj._size = 0;
        obj._capacity = 0;
    }

    void push_back(const T& val){
        if(_size == _capacity){
            T* newpdata = new T[_capacity*2];
            std::copy_n(pdata, _size, newpdata);
            delete[] pdata;
            pdata = newpdata;
            pdata[_size++] = val;
            _capacity *= 2;
            return ;
        }
        pdata[_size++] = val;
        return ;
    }
    void pop_back(){
        if(_size > 0){
            --_size;
        }
        return;
    }
    T& operator[](int index){
        return pdata[index];
    }
    int size() const{
        return _size;
    }
    int capacity() const{
        return _capacity;
    }
    void printdata(std::ostream& out = std::cout) {
        for(int i=0; i< _size; ++i){
            out << pdata[i] << " ";
        }
        out<<std::endl;
    }
};


int main(){
    myVec<int> q;
    for(int i=0; i< 10; i++){
        q.push_back(i);
        std::cout << "i:" << q[i] << " size:"<<q.size() << " cap:"<< q.capacity()<< std::endl;
    }
    std::cout << std::endl;

    myVec<int> p(q);
    p.printdata();


    std::cout << std::endl;
    myVec<int> m ;
    m = p;
    m.printdata();

    
    std::cout << std::endl;
    myVec<int> n(std::move(m));
    n.printdata();

}


