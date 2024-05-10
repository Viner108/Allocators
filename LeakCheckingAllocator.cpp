#include <iostream>
#include <vector>

template<typename T>
class LeakCheckingAllocator
{
public:
    using value_type = T;
    static size_t count;

    T* allocate(size_t n){
        std::cout << "Allocating " << n << " elements of type T." << std::endl;
        count += n;
        return static_cast<T*>(operator new(n*sizeof(T)));
    }

    void deallocate(T* p, size_t n){
        std::cout << "Deallocating " << n << " elements of type T." << std::endl;
        count -= n;
        operator delete(p);
        if(count == 0){
            std::cout << "No memory leak detected." << std::endl;
        }else{
            std::cout << "Warning:Memory leak detected. " << count << " elements still allocated." << std::endl;
        }
        
    }
};

template<typename T>
size_t LeakCheckingAllocator<T>::count = 0;

int main(){
    std::vector<int,LeakCheckingAllocator<int>> v;
    v.push_back(1);
    v.push_back(10);
}

