import numpy as np

x = y = 0
A = [
    [0.8, -0.3],
    [-0.3, 0.2]
]
f = [2, 3]
h = [1, 0]
pi = [0.5, 0.5]

p = [
    [0.5, 0.5],
    [0.5, 0.5]
]

N = 100000
m = 10

i = [0] * N
Q = [0] * N

ξ = [0] * m

for j in range(m):
    mca = np.random.uniform(0.0, 1.0, N + 1)
    i[0] = 0 if mca[0] < pi[0] else 1

    for k in range(1, N):
        i[k] = 0 if mca[k] < 0.5 else 1

    Q[0] = h[i[0]] / pi[i[0]] if pi[i[0]] > 0 else 0

    for k in range(1, N):
        if p[i[k - 1]][i[k]] > 0:
            Q[k] = (Q[k - 1] * A[i[k - 1]][i[k]]) / p[i[k - 1]][i[k]]
        else:
            Q[k] = 0

    for k in range(N):
        ξ[j] += Q[k] * f[i[k]]

print(sum(ξ) / m)

