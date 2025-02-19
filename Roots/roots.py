import matplotlib.pyplot as plt
import numpy as np

def y(x, sol=[], dx=pow(10, -7)):
    f = x**2 - 5*x + 6
    
    for i in range(len(sol)):
        if(x == sol[i]):
            f /= ((x + dx) - sol[i])
        else :
            f /= (x-sol[i])

    return f

def dy_dx(x, dx, sol=[]):
    df = y(x + dx, sol) - y(x - dx, sol)
    return df / (2*dx)

def integrate(a, b, dx=pow(10, -7)):
    result = 0
    if(a > b):
        dx = -dx

    while(abs(a - b) > dx):
        result += (y(a) * dx)
        a += dx

    return result
    
def x_intercept(x, sol=[]):
    y1 = y(x, sol)
    dy1 = dy_dx(x, pow(10, -7), sol)

    x2 = x - (y1 / dy1)
    return x2

def f_plot(x, x_to, dx):
    arrx = []
    arry = []

    while(x<=x_to): 
        arrx.append(x)
        arry.append(y(x))
        x += dx

    plt.figure(figsize=(10, 5))
    plt.scatter(arrx, arry, c='b', label="fun")
    plt.legend()
    plt.show()

def df_plot(x, x_to, dx):
    arrx = []
    arry = []

    while(x<=x_to): 
        arrx.append(x)
        arry.append(dy_dx(x, pow(10, -7)))
        x += dx

    plt.figure(figsize=(10, 5))
    plt.scatter(arrx, arry, c='b', label="d_fun")
    plt.legend()
    plt.show()

def roots(n, x=0):
    sol = []
    dx = pow(10, -7)

    while(n):
        while(abs(y(x, sol)) > dx):
            x = x_intercept(x, sol)
        
        if(abs(x - np.floor(x)) < dx):
            sol.append(np.floor(x))
        elif(abs(x - np.ceil(x)) < dx):
            sol.append(np.ceil(x))
        else:
            sol.append(x)
        n -= 1
    
    return sol

x = 0
n = 2
sol = roots(n, x)
integral = integrate(0, 1)

print(f"{integral}\n")
for a in sol:
    print(f"{a}, ")
