#include <iostream>
#include <memory>
#include <vector>

template<typename T>
class TrackingAllocator{
    
public:
    using value_type = T;
    T* allocate(size_t n){
        std::cout << "Allocating " << n << " elements of type T." << std::endl;
        return static_cast<T*>(operator new(n*sizeof(T)));
    }

    void deallocate(T* p, size_t n){
        std::cout << "Dealliocate " << n << " elements of type T." << std::endl;
        operator delete(p);
    }
};

int main(){
    std::vector<int, TrackingAllocator<int>> v;
    v.push_back(42);
    v.push_back(72);
}