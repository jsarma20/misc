This is a mini thread-pool library to run tasks on available threads.


Usage:
auto threadPool = ThreadPool(thread=10,priority=Priority:FIFO)

auto task = threadPool.add_task(fn(my_task_fn,arg1,arg2,arg3))

task.getOrWait()


extra feature: can have a waiting queue.


each thread wait on idle while loop until a task is issued.