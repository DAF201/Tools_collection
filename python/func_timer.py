from os import name
from signal import signal, alarm, SIGALRM


def func_timer(time=5):
    if name != "posix":
        raise BaseException("this timer is for posix system only")

    def decorator(func):
        def __timeout(signum, frame):
            raise TimeoutError("function timeout: {}\n".format(func))

        def wrapper(*args, **kwargs):
            signal(SIGALRM, __timeout)
            alarm(time)
            re = func(*args, **kwargs)
            return re

        return wrapper

    return decorator
