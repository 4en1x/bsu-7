from math import *
import numpy as np

data = [(21, 1), (20001, 1), (21, 10), (20001, 10), (20001, 1000), (2000001, 1000), (2000001, 10000)]
print("Right answer is something about 2.07959")
for (n, ranges) in data:
    h = (ranges * 2) / (n - 1)
    nodes = [i for i in np.arange(-ranges, ranges + h, h)]
    answer = sum([exp(-(x ** 4)) * ((1 + x ** 2) ** (1 / 2)) for x in nodes]) * (ranges * 2 / n)
    print("Answer: {0}, ranges = (-{1}, {1}), number of nodes = {2}".format(answer, ranges, n))