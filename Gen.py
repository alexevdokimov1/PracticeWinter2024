from sympy import solve, Symbol
from random import uniform

f = open("Quadratic Interpolation/Debug/CalcTest.txt", "w")
for i in range (10):
    x = Symbol('x')
    a=uniform(10.5, 75.5)
    b=uniform(10.5, 75.5)
    c=uniform(10.5, 75.5)
    x0=uniform(10.5, 75.5)
    y0=uniform(10.5, 75.5)

    unkonwn = solve((2 * a * x +b) * (a * x**2 + b * x + c- y0) + x - x0, x)[0]
    f.write(str(a)+" "+str(b)+" "+str(c)+" "+str(x0)+" "+str(y0)+" "+str(unkonwn)+"\n")
f.close()