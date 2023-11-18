#include <barrier>
#include <iostream>
#include <syncstream>
#include <vector>

namespace threads_sync
{
    std::barrier phase(5);

    void f(const char c, const int i)
    {
        std::osyncstream(std::cout) << "Task " << c << i << " is completed" << std::endl;
    }

    void t(const std::vector<std::pair<char, int>> &tasks)
    {
        for (const auto &task : tasks)
        {
            f(task.first, task.second);
            phase.arrive_and_wait();
        }
    
        phase.arrive_and_drop();
    }
}

int main(int argc, char* argv[])
{
    // HARDCODE
    std::vector<std::pair<char, int>> tasks1 {{'a', 1}, {'a', 6}, {'b', 3}, {'c', 3}, {'d', 3}, {'e', 3}, {'f', 3}, {'g', 1}, {'h', 2}, {'i', 3}, {'j', 3}, {'j', 8} };
    std::vector<std::pair<char, int>> tasks2 {{'a', 2}, {'a', 7}, {'b', 4}, {'c', 4}, {'d', 4}, {'e', 4}, {'f', 4}, {'g', 2}, {'h', 3}, {'i', 4}, {'j', 4}, {'j', 9} };
    std::vector<std::pair<char, int>> tasks3 {{'a', 3}, {'a', 8}, {'b', 5}, {'c', 5}, {'d', 5}, {'e', 5}, {'f', 5}, {'g', 3}, {'h', 4}, {'i', 5}, {'j', 5} };
    std::vector<std::pair<char, int>> tasks4 {{'a', 4}, {'b', 1}, {'c', 1}, {'d', 1}, {'e', 1}, {'f', 1}, {'f', 6}, {'g', 4}, {'i', 1}, {'j', 1}, {'j', 6} };
    std::vector<std::pair<char, int>> tasks5 {{'a', 5}, {'b', 2}, {'c', 2}, {'d', 2}, {'e', 2}, {'f', 2}, {'f', 7}, {'h', 1}, {'i', 2}, {'j', 2}, {'j', 7} };
    
    std::cout << "Execution started" << std::endl;
    
    std::jthread t1(threads_sync::t, tasks1);
    std::jthread t2(threads_sync::t, tasks2);
    std::jthread t3(threads_sync::t, tasks3);
    std::jthread t4(threads_sync::t, tasks4);
    std::jthread t5(threads_sync::t, tasks5);

    // Joining manually because it is necessary to display "Execution ended" when threads are done their work
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
    
    std::cout << "Execution ended" << std::endl;
    return 0;
}
