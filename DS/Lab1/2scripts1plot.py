import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from sympy import *

f1 = open('test_1.txt')
f2 = open('test_2.txt')

u = Symbol('u')
ν = [10000, 20000, 30000, 50000]

count = 0

plt.legend(handles=[
    mpatches.Patch(color='red', label='script1'),
    mpatches.Patch(color='blue', label='script2'),
])

x1 = []
x2 = []
y1 = []
y2 = []

while True:
    line1 = f1.readline()
    line2 = f1.readline()

    if not line1 or not line2:
        break
    if line1 == '' or line2 == '':
        break

    a = [float(x) for x in line1.split(' ')[:-1]]
    b = [float(x) for x in line2.split(' ')[:-1]]

    if count == 1000:
        break
    if count % 4 == 0:
        x1.append(a[2])
        y1.append(a[1])

    if count % 4 == 0:
        x2.append(b[2])
        y2.append(b[1])

    count += 1

plt.plot(x1, y1, c='blue')
plt.plot(x2, y2, c='red')

plt.show()
