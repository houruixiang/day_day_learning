
registry = {1}
registry.pop()
def register(active  = True):
    def decorate(func):
        print("register function:(%s)" %func)
        if acive:
            registry.add(func)
        else:
            registry.discard(func)
        return func
    return decorate
    
@registry(active = False)
def f1():
    print('running f1()')
    
@registry()
def f2():
    print('running f2()')