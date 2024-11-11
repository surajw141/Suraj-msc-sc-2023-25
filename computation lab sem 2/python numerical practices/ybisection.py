def bisection_method(func, a, b, error_accept):
    def f(x):
        f = eval(func)
        return f
    error = abs(b - a)
    while error > error_accept:
        c = (b + a) / 2
        
        if (a) * (b) >= 0:
            print("Root is not bracketed, the bisection methon wont work")
            quit()
        elif f(c) * f(a) < 0:
            b = c
            error = abs(b - a)
            return c
        elif f(c) * f(b) < 0:
            a = c
            error = abs(b - a)
            
        else:
            print("Something went wrong")
            quit()
    print(f"The error is {error}")
    print(f"the lower boundary, a , is {a} and the upper boundary, b, is {b} ")
    
bisection_method("(4*x ** 3) + 3*x -3", 0, 1, 0.05)
bisection_method("(3*x ** 2) - 4", -2, 0, 0.05)
    