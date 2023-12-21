from math import *

def f(coefs, x):
    summ=0
    for i in range(len(coefs)):
        summ+=coefs[i]*x**(len(coefs)-1-i)
    return summ

def main():
    order = int(input("Enter order\n"))
    count = int(input("Enter count\n"))
    
    coefs = [0]*order
    for i in range(order):
        coefs[i]=float(input(f'Enter coef {chr(97+i)}\n'))

    file = open("vector.txt", "w")

    x_start = float(input("Enter x start\n"))

    step=float(input("Enter step\n"))

    file.write(str(order) + " " + str(count)+"\n")

    for i in range(count):
        x_cur=x_start+step*i
        f_cur=f(coefs, x_cur)
        file.write(str(x_cur)+"\t"+str(f_cur)+"\n")

    file.close()

if __name__=="__main__":
        main()