#include <memory>
#include <thread>
#include <atomic>
#include <iostream>

int main()
{
    // Efficient atomix waiting
    std::atomic<bool> lock{false};
    std::jthread threadA([&lock]()
    {
        std::cout << "A+\n";
        lock.wait(false);   // More lightweight than conditiona variable
        std::cout << "A-\n";
    });
    std::jthread threadB([&lock]()
    {
        std::cout << "B+\n";
        lock.wait(false);
        std::cout << "B-\n";
    });

    std::cout << "unlock\n";
    lock = true;
    lock.notify_all();
}
