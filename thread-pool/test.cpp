#include "ThreadPool.h"
#include <catch2/catch_test_macros.hpp>


TEST_CASE("Launch multiple-thread and wait 5s to complete")
{   

    ThreadPool<int> myPool;
    myPool.run(3);
    auto printF0 = [](int x) ->int {
        std::cout<<"printF0 "<<std::this_thread::get_id()<<" running f("<<x<<")"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        return 200;
    };
    auto printF1 = [](int x) ->int {
        std::cout<<"printF1 "<<std::this_thread::get_id()<<" running f("<<x<<")"<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
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

    std::this_thread::sleep_for(std::chrono::seconds(5));

    //tasks should be done by now. Any new task should be ready to be picked up the idle threads.

    std::function<int(void)> return15 = [](){return 15;};

    auto idx = myPool.addTask(return15);
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    CHECK(myPool.getResults(idx) == 15);
    

}

