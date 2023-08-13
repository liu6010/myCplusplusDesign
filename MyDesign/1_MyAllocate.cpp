#include <iostream>
#include <climits>
// using namespace std;

template<typename T>
class myAllocSimp{
public:
    static T* allocate(size_t n){
        if(n > max_size() ){
            throw std::bad_alloc();
        }
        void* result = malloc(n*sizeof(T));
        if(result==0) throw std::bad_alloc();
        return static_cast<T*>(result);
    }
    static T* reallocate(T*p, size_t new_sz){
         if(new_sz > max_size() ){
            throw std::bad_alloc();
        }
        void* result = realloc((void*)p, new_sz * sizeof(T));
        if(result==0) throw std::bad_alloc();
        return static_cast<T*>(result);
    }

    static void deallocate(T* p){
        free((void*)p);
    }
    static size_t max_size(){
        return static_cast<size_t>(size_t(-1) / sizeof(T));
    }
};
// g++ ../allocate.cpp -o allocate -g -fsanitize=address -fno-omit-frame-pointer
// g++ ../allocate.cpp -o allocate -g -fsanitize=address
void testSimp(){
    using alloc = myAllocSimp<int>;
    size_t size = 5;
    int* arr = alloc::allocate(size);
    for(size_t i=0; i<size; i++){
        arr[i] = i;
    }
    for(size_t i=0; i<size; i++){
        std::cout <<arr[i] << " ";
    }
    alloc::deallocate(arr);
    std::cout << std::endl;
}


int main(){
    testSimp();
}
