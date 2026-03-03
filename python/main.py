import scope

def sum(lis):
    if len(lis)==1:
        return lis[0]
    else:
        return lis[0] + sum(lis[1:])

if __name__ == '__main__':
    print(scope.foo(4))

