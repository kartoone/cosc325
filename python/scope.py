def foo(a):
    return a+3

def fmt(c):
    return c

def method1():
    a = 5
    def fmt(b):
        c = 5
        return b+c
    fmt(a)
    print(c)

if __name__ == '__main__':
    print(foo(3))
    method1()
    fmt(3)

