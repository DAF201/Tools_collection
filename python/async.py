import time
import asyncio


async def test_function_1():
    print("1 start")
    n = 0
    while (n < 2):
        n += 1
        print("1's 5 seconds timer")
        await asyncio.sleep(5)
        print("1's 5 seconds timer ends")
    print("1 end")


async def test_function_2():
    start_time = time.time()
    time.sleep(5)
    print("2's 5 seconds timer")


async def test_function_3():
    start_time = time.time()
    time.sleep(10)
    print("3's 10 seconds timer")


loop = asyncio.get_event_loop()
task = [asyncio.ensure_future(x)
        for x in (test_function_1(), test_function_2(), test_function_3())]
loop.run_until_complete(asyncio.wait(task))

'''
1 start
1's 5 seconds timer
2's 5 seconds timer
3's 10 seconds timer
1's 5 seconds timer ends
1's 5 seconds timer
1's 5 seconds timer ends
1 end
'''

'''
task1 -> task1 got hung up at await, remaining parts not executed ->
remaining part of task1 being pushed to the end of the task_queue->
task2 -> task3 -> task1 remaining

I will rather use threading and taskqueue...
'''


import time
import asyncio


async def test_function_1():
    await asyncio.sleep(5)
    print(1)


async def test_function_2():
    await asyncio.sleep(5)
    print(2)


async def test_function_3():
    await asyncio.sleep(5)
    print(3)

start = time.time()
loop = asyncio.get_event_loop()
task = [asyncio.ensure_future(x)
        for x in (test_function_1(), test_function_2(), test_function_3())]
loop.run_until_complete(asyncio.wait(task))
end = time.time()
print(end-start)

'''
1
2
3
5.000494956970215
5s rather than 15s, because they will not block eachother
'''
