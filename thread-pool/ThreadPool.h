#include<thread>
#include<queue>
#include<iostream>
#include<tuple>
#include<map>
#include<list>

#ifndef THREAD_POOL
#define THREAD_POOL

template<typename TASK_RETURN_TYPE>
class BaseThreadPool
{
    public:
    typedef std::function<TASK_RETURN_TYPE(void)> Fn;
    BaseThreadPool():taskId(0){}
    void run(int nThreads)
    {
        for(int i=0;i<nThreads;i++)
        {
            pool.push_back(std::thread(&BaseThreadPool::spawnWorker, this));
        }
    }

    ~BaseThreadPool()
    {
        for( auto& th : pool)
        {
            th.join();
        }
    }

    virtual int addTask(Fn f) = 0;

    protected:
    int taskId;
    std::mutex mTask, mResults;
    virtual void spawnWorker() = 0;
    std::list<std::thread> pool;

};



template<typename TASK_RETURN_TYPE>
class ThreadPool : public BaseThreadPool<TASK_RETURN_TYPE>
{
    public:
    using typename BaseThreadPool<TASK_RETURN_TYPE>::Fn;
    const int MAX_POOL = 5;
    
    int addTask(Fn f) override
    {
        std::lock_guard<std::mutex> lock(this->mTask);
        if(taskQ.size()>=MAX_POOL)
        {
            std::cout<<"failed to add task to queue"<<std::endl;
            return -1;
        }

        taskQ.push({this->taskId,f});
        results[this->taskId++] = {false,{}};
        return this->taskId-1;
    }

    void stop()
    {
        stopSignal = true;
    }


    TASK_RETURN_TYPE getResults(int id, int waitMs=0)
    {
        int WAIT_STEP_MS=5;
        do
        {
            auto it = results.find(id);
            if(it==results.end()) std::this_thread::sleep_for(std::chrono::milliseconds(WAIT_STEP_MS));
            std::lock_guard<std::mutex> lock(this->mResults);
            auto result = it->second;
            if(std::get<bool>(result))
            {
                results.erase(id);
                return std::get<TASK_RETURN_TYPE>(result);
            }
        waitMs -=WAIT_STEP_MS;
        }while(waitMs>0);
        
        return TASK_RETURN_TYPE{};
    }
    ~ThreadPool()
    {
        stop();
    }

protected:

    void spawnWorker() override
    {
        while(!stopSignal)
        {
            std::tuple<int,Fn> f;
            bool task_available = false;
            {
                std::lock_guard<std::mutex> lock(this->mTask);
                if(!taskQ.empty())
                {
                    f = taskQ.front();
                    taskQ.pop();
                    task_available = true;
                }
            }
            if(task_available)
            {
                TASK_RETURN_TYPE out = std::get<Fn>(f).operator()();
                std::lock_guard<std::mutex> result(this->mResults);
                results[std::get<int>(f)] = {true, out};
            }

        }
    }
    std::atomic<bool> stopSignal = false;
    std::queue<std::tuple<int,Fn>> taskQ;
    std::map<int, std::tuple<bool,TASK_RETURN_TYPE>> results;

};

#endif