from sympy import Symbol, S
from sympy.solvers.solveset import solveset, solveset_real
from random import uniform

f = open("CalcTest.txt", "w")
positive_gen=5
negative_gen=5

f.write(str(positive_gen+negative_gen)+"\n")

x = Symbol('x')
for i in range (positive_gen):
    a=round(uniform(0, 1000),0)
    b=round(uniform(0, 1000),0)
    c=round(uniform(0, 1000),0)
    x0=round(uniform(0, 1000),0)
    y0=round(uniform(0, 1000),0)

    unknown = list(solveset((2 * a * x +b) * (a * x**2 + b * x + c- y0) + x - x0, x, domain=S.Reals))
    f.write(str(a)+" "+str(b)+" "+str(c)+" "+str(x0)+" "+str(y0)+" "+str(-100)+" "+str(100)+" "+str(len(unknown)))
    for each in unknown:
        f.write(" "+str(each))
    f.write("\n")

for i in range (negative_gen):
    a=round(uniform(-1000,0),0)
    b=round(uniform(-1000,0),0)
    c=round(uniform(-1000,0),0)
    x0=round(uniform(-1000,0),0)
    y0=round(uniform(-1000, 0),0)

    unknown = list(solveset((2 * a * x +b) * (a * x**2 + b * x + c- y0) + x - x0, x, domain=S.Reals))
    f.write(str(a)+" "+str(b)+" "+str(c)+" "+str(x0)+" "+str(y0)+" "+str(-100)+" "+str(100)+" "+str(len(unknown)))
    for each in unknown:
        f.write(" "+str(each))
    f.write("\n")
f.close()