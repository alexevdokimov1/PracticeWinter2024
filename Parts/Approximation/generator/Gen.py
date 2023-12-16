from math import *
def main():
    task = input("Enter the function like a*x**2+b*x+c\n")

    f = lambda x: float(eval(task))

    file = open("vector.txt", "w")

    n = int(input("Enter n\n"))

    x_start = float(input("Enter x start\n"))

    step=float(input("Enter step\n"))

    file.write(str(n)+"\n")

    for i in range(n):
        x_cur=x_start+step*i
        f_cur=f(x_cur)
        file.write(str(x_cur)+"\t"+str(f_cur)+"\n")

    file.close()

if __name__=="__main__":
        main()