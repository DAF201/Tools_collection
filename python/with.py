class Sample:
    def __enter__(self):
        print("In __enter__()")
        return "Foo"

    def __exit__(self, type, value, trace):
        print("In __exit__()")
        print(type, value, trace)


def get_sample():
    return Sample()


with get_sample() as sample:
    print("sample:", sample)

with Sample() as sample:#this work the same
    print("sample:", sample)    
    
# output
# In __enter__()
#sample: Foo
# In __exit__()
# None None None

# so basically it will run __enter__ when this object created, run __exit__ when leaving this block of code
# The type, value, and trace are for exception handling
