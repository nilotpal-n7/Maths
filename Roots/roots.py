import matplotlib.pyplot as plt
import numpy as np

def y(x):
    f = np.tan(x)
    return f

def dy_dx(x):
    df = (1 / np.cos(x))**2
    return df

def x_intercept(x):
    y1 = y(x)
    dy1 = dy_dx(x)

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

x = 5
x1 = x
dx = 0.001 
y_desired = 0
f_plot(-5, 5, dx)

while(abs(y(x) - y_desired) > dx):
    x = x_intercept(x)
    if(abs(x - x1) < dx):
        break

print(x, y(x))
