import matplotlib.pyplot as plt
from sympy import *
import math
u = Symbol('u')
f = open('test.txt', 'w')
ν = [10000, 20000, 30000, 50000]
colors = ['red', 'blue', 'pink', 'green']

ρ0 = 998.2
σ = 0.0728
η = 0.0010005
γ = 1.4
P0 = 101325
P_ac = lambda t, j: -1.28 * P0 * sin(2 * 3.1415926535897932 * ν[j] * t)
R0 = 0.000005
h =  0.000001
P_g = lambda x: (P0 + 2 * σ / R0 ) * ((R0 / x) ** (3 * γ))

x0 = [R0] * len(ν)
y0 = [0] * len(ν)

f_x = lambda y: y
f_y = lambda x, y, t, j: (-3 * y * y / 2 + (P_g(x) - P0 - P_ac(t, j) - 2 * σ / x - 4 * η * y / x) / ρ0) / x


count = 0
t = 0
axes = plt.gca()
axes.set_ylim([.0499999999975, .0500000000025])

m = R0
mi = R0


def fu(h, x0, y0, t, j):
    y = y0 + h * f_y(x0, y0, t, j)
    x = x0 + h * f_x(y)
    return x


e = 4 * 10 ** -8

while True:
    h = h * 2
    min_h = 10
    print(count)
    for j in range(len(ν)):
        r = 10
        while r > e:
            r = math.fabs(fu(h, x0[j], y0[j], t, j) - fu(h / 2, x0[j], y0[j], t, j))
            h = h / 1.1
        if min_h > h:
            min_h = h
    h = min_h

    for j in range(len(ν)):
        y0[j] += h * f_y(x0[j], y0[j], t, j)
        x0[j] += h * f_x(y0[j])

    count += 1
    t = t + h
    if count == 30000000: break

    if count % 10 == 0:
        for j in range(len(ν)):
            f.write(str(j) + " " + str(x0[j]) + " " +str(t) + " " + str(y0[j]) + " \n")
            if count % 100 == 0:
                f.flush()
