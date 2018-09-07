import math
import random

circle_r = 7 ** (1 / 2)

print("Right answer is something about 7.82449")
for n in [10 ** i for i in range(3, 9)]:
    nodes = []
    for counter in range(n):
        x = y = 0
        while (x ** 2 + y ** 2) < 1:
            alpha = 2 * math.pi * random.random()
            r = circle_r * math.sqrt(random.random())
            x = r * math.cos(alpha)
            y = r * math.sin(alpha)
        if (x ** 2 + y ** 2) > 7:
            print(x ** 2 + y ** 2)
        nodes.append((x, y))

    answer = sum([(x ** 3 + math.exp(y)) / (x ** 2 + 2 * y ** 2) for (x, y) in nodes]) * (6 * math.pi / n)
    print("Answer: {0}, number of nodes = {1}".format(answer, n))