import numpy as np
import random
count = 0
all_time = 0
total_time = 28800
m = []
t = 3
while True:
    s = np.random.poisson(95, 1)[0]
    all_time += s
    if total_time < all_time:
        break
    m.append({
        "time_arrival": all_time
    })
    count += 1

for c, e in enumerate(m):
    time_go_to_till = e["time_arrival"]
    n = 0
    if random.random() > 0.35:
        time_go_to_till += (180 + ((random.random() * 2) - 1) * 60)
        n += 1
    if random.random() > 0.15:
        time_go_to_till += (160 + ((random.random() * 2) - 1) * 30)
        n += 1
    if random.random() > 0.30:
        time_go_to_till += (100 + ((random.random() * 2) - 1) * 25)
        n += 1
    if random.random() > 0.10:
        time_go_to_till += (50 + ((random.random() * 2) - 1) * 15)
        n += 1
    m[c]["time_go_to_till"] = time_go_to_till
    m[c]["n"] = n
m = [x for x in m if x["time_go_to_till"] < total_time]
m = sorted(m, key=lambda e: e["time_go_to_till"])

current_time = m[0]["time_go_to_till"]
for c, e in enumerate(m):
    if m[c]["time_go_to_till"] > current_time:
        current_time = m[c]["time_go_to_till"]
    m[c]["time_start_till"] = current_time
    m[c]["time_end_till"] = current_time + m[c]["n"] * t
    current_time += m[c]["n"] * t
m = [x for x in m if x["time_go_to_till"] < total_time]

max_line = 0
for c, e in enumerate(m):
    local_max_line = 0
    local_e = m[c]
    for i in range(c + 1, len(m)):
        if m[c]["time_end_till"] > m[i]["time_go_to_till"]:
            local_max_line += 1
        else:
            break
    if local_max_line > max_line:
        max_line = local_max_line

print("Общее количество всех обслуженных покупателей: {0}".format(len(m)))
print("Среднее время в кассе: {0}".format(sum([x["time_end_till"] - x["time_start_till"] for x in m]) / len(m)))
print("Среднее время в очереди: {0}".format(sum([x["time_start_till"] - x["time_go_to_till"] for x in m]) / len(m)))
print("Максимальное количество людей в очереди: {0}".format(max_line))
