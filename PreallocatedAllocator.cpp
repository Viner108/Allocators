#include <iostream>
#include <memory>
#include <vector>

template<typename T>
class PreallocatedAllocator{
    
private:
    T* pool;
    std::size_t capacity;
    std::size_t used;
    bool is_owner;

public:
    using value_type = T;

    PreallocatedAllocator(size_t max_elements): capacity(max_elements), used(0), is_owner(true){
        pool = static_cast<T*>(malloc(capacity * sizeof(T)));
        std::cout << "Preallocated pool for " << max_elements << " elements of type T." << std::endl;
    }

    PreallocatedAllocator(const PreallocatedAllocator& other) noexcept
    : pool(other.pool), capacity(other.capacity), used(other.used), is_owner(false){
    }

    PreallocatedAllocator& operator=(const PreallocatedAllocator& other) noexcept{
        if(this != &other){
            pool = other.pool;
            capacity = other.capacity;
            used = other.used;
            is_owner = false;
        }
        return *this;
    }

    ~PreallocatedAllocator(){
        if(is_owner){
        free(pool);
        std::cout << "Freed preallocated pool." << std::endl;
        }
    }

    T* allocate(size_t n){
        if(used + n > capacity) throw std::bad_alloc();
        T* result = pool + used;
        used += n;
        std::cout << "Allocating " << n << " elements; " << (capacity - used) << " elemets remaining." << std::endl;
        return result;
    }

    void deallocate(T* p, size_t n) noexcept{
        std::cout << "Deallocation called for " << n << " elements, but memory is not freed until allocator destruction." << std::endl;
    }
};

int main(){
    PreallocatedAllocator<int> allocator(100);
    std::vector<int, PreallocatedAllocator<int>> v(allocator);
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
}