import numpy as np
import matplotlib.pyplot as plt
from sympy import *
u = Symbol('u')


ρ0 = 998.2
σ = 0.0728
η = 0.0010005
γ = 1.4
ν = 20000
P_ac = (γ + 1) * ν * ν * ρ0 / 8
P_ac = 2 * 10 ** 6
R0 = 0.000005
P0 = 101325
h = 0.0000000002
P_g = lambda x: (P0 + 2 * σ / R0) * (R0 / x) ** (3 * γ)

x0 = R0
y0 = 0

f_x = lambda y: y
f_y = lambda x, y: (-3 * y * y / 2 + (P_g(x) - P0 - P_ac - 2 * σ / x - 4 * η * y / x) / ρ0) / x

a = []
count = 0
while True:

    k1 = f_y(x0, y0)
    k2 = f_y(x0 + h / 2, y0 + h * k1 / 2)
    k3 = f_y(x0 + h / 2, y0 + h * k2 / 2)
    k4 = f_y(x0 + h, y0 + h * k3)

    y0 += h * (k1 + 2 * k2 + 2 * k3 + k4) / 6

    k1 = f_x(y0)
    k2 = f_x(y0 + h / 2)
    k3 = f_x(y0 + h / 2)
    k4 = f_x(y0 + h)

    x0 += h * (k1 + 2 * k2 + 2 * k3 + k4) / 6
    count += 1
    if count == 100000: break
    print(x0)
    a.append(x0)

plt.plot(a, linestyle='None', marker='.', markersize=1)
plt.show()


