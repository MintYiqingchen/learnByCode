import threading
import time
import random

def worker_func():
        print('worker thread is start at %s'%threading.current_thread())
        random.seed()
        time.sleep(random.random())
        print('worker thread is finished at %s'%threading.current_thread())

gLock=threading.Lock()
def thread_demo():
        # target 表示创建新线程后线程之后调用的函数
        for i in range(10):
                threading.Thread(target=worker_func_lock,args={gLock}).start()
def worker_func_lock(lock):
        lock.acquire()
        worker_func()
        lock.release()        
thread_demo()
