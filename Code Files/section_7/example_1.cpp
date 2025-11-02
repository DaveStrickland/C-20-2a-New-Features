#include <memory>
#include <thread>
#include <atomic>
#include <iostream>

int main() 
{
    //std::shared_ptr<int> ptr = std::make_shared<int>(4); // DKS: (A) This will trigger thread sanitizer at runtime
    std::atomic<std::shared_ptr<int>> ptr = std::make_shared<int>(4);   // DKS (B)
    std::jthread threadA([&ptr]() mutable
    {
        ptr = std::make_shared<int>(10);
    });
    std::jthread threadB([&ptr]() mutable
    {
        ptr = std::make_shared<int>(20);
    });
    //std::cout << "Value of shared int is " << *ptr << "\n"; // (A) Also, this can cuase a race
    std::shared_ptr<int> local_ptr = ptr.load();
    if (local_ptr)
    {
        std::cout << "Value of shared int is " << *local_ptr << "\n"; 
    }
}
