class test:
    def __init__(self) -> None:
        print('init')
        # init

    def __enter__(self):
        print('enter')
        # can return self here

    def __exit__(self, type, value, trace):
        print('exit')
        # close file balabala

    def __del__(self):
        print('delete')
        # gc or whatever


with test() as t:
    pass

# output:
# init
# enter
# exit
# delete
