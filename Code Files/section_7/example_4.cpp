#include <memory>
#include <thread>
#include <atomic>
#include <chrono>
#include <iostream>
#include <latch>    // DKS: Added

int main()
{
    std::latch latch{2};    // two threads, both threads will block on
                            // arrive_and_wait until the latch is zero
                            // then both get re-awoken 
    std::atomic<int> counter;
    std::jthread threadA([&]()
    {
        for(int i = 0; i < 10; ++i)
        {
            ++counter;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        latch.arrive_and_wait();
        std::cout << "final counter from A: " << counter << std::endl;
    });
    std::jthread threadB([&]()
    {
        for(int i = 0; i < 10; ++i)
        {
            ++counter;
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        latch.arrive_and_wait();
        std::cout << "final counter from B: " << counter << std::endl;
    });
}
