import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from sympy import *

f = open('test.txt')
u = Symbol('u')
ν = [10000, 20000, 30000, 50000]
colors = ['red', 'blue', 'pink', 'green']

count = 0
axes = plt.gca()
axes.set_ylim([.0499999999975, .0500000000025])

m = .00000005
mi = .00000005

plt.legend(handles=[
    mpatches.Patch(color='red', label='10000'),
    mpatches.Patch(color='blue', label='20000'),
    mpatches.Patch(color='pink', label='30000'),
    mpatches.Patch(color='green', label='50000'),
])

while True:
    line = f.readline()
    if not line:
        break
    if line == '':
        break

    a = [float(x) for x in line.split(' ')[:-1]]
    if a[1] > m:
        m = a[1]
    if a[1] < mi:
        mi = a[1]

    count += 1

    if count % 1 == 0:
        plt.scatter(a[2], a[1], marker='.', c=colors[int(a[0])], linewidths=0.001)
        plt.ylim([float(mi), float(m)])
        plt.xlim([float(0), float(a[2])])
        if count % 100 == 0:
            plt.pause(0.0005)

plt.show()
