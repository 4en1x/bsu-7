from itertools import islice
import scipy.stats as stats

f = open("numbers.txt", "r")
n = 1000

d1 = [float(x.strip()) for x in islice(f, n)]
d3 = [float(x.strip()) for x in islice(f, n)]
m1 = []
m3 = []
for j in range(10):
    m1.append(len([i for i in d1 if i < float(j + 1) / 10.0 and i >= float(j) / 10.0]))
    m3.append(len([i for i in d3 if i < float(j + 1) / 10.0 and i >= float(j) / 10.0]))


print("Critical: {0}".format(stats.chi2.ppf(q=0.95, df=9)))
print(stats.chisquare(f_obs=m1, f_exp=[int(n / 10)] * 10).statistic)
print(stats.chisquare(f_obs=m3, f_exp=[int(n / 10)] * 10).statistic)

print("Critical: {0}".format(1.35810 / (n ** (1 / 2))))
print(stats.kstest(d1, 'uniform').statistic)
print(stats.kstest(d3, 'uniform').statistic)