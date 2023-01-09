# __getattribute__ will be called when a property of class is used no matter how, __getattr__ will be called only when a undefined property is used

class test_class:
    test = 1

    def __init__(self, value) -> None:
        self.value = value

    def __getattribute__(self, __name: str):
        return None

t = test_class(1)
print(t.test)
print(t.value)
print(t.undefined)

# None
# None
# None

##################################################
class test_class:
    test = 1

    def __init__(self, value) -> None:
        self.value = value

    def __getattr__(self, name):
        return None

t = test_class(1)
print(t.test)
print(t.value)
print(t.undefined)

# 1
# 1
# None
