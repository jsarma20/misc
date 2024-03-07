#include "ThreadPool.h"

int main()
{   

    ThreadPool<int> myPool;
    myPool.run(3);
    auto printF0 = [](int x) ->int {
        std::cout<<"printF0 "<<std::this_thread::get_id()<<" running f("<<x<<")"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        return 200;
    };
    auto printF1 = [](int x) ->int {
        std::cout<<"printF1 "<<std::this_thread::get_id()<<" running f("<<x<<")"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        return 201;
    };
    std::function<int(void)> f0 = std::bind(printF0,15); 
    std::function<int(void)> f1 = std::bind(printF1,11);
    std::function<int(void)> f2 = std::bind(printF0,25); 
    std::function<int(void)> f3 = std::bind(printF1,45);

    int id = myPool.addTask(f0);
    
    myPool.addTask(f1);
    myPool.addTask(f2);
    
    myPool.addTask(f3);
    myPool.addTask(f0);
    myPool.addTask(f1);
    myPool.addTask(f2);
    myPool.addTask(f0);
    myPool.addTask(f3);
    myPool.addTask(f1);
    myPool.addTask(f2);

    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    std::cout<<"results value = "<<myPool.getResults(id)<<std::endl;
    std::cout<<"results value = "<<myPool.getResults(id+5)<<std::endl;
    
    return 0;
}

