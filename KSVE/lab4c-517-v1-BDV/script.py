f = open('lab4с517v1_task5_2.txt')
f2 = open('task8.txt', 'w')
s = [float(i) for i in f.read()
    .replace('\n', '')
    .replace('{', '}')
    .replace(',', '}')
    .split('}')
if i != '' and i != ' ']

print(s)
print(s[0])

i = 0
j = 0
while i + 4 < len(s):
    f2.write(str(int(s[i])) + ' ' + str(1 + (j % 41)) + ' '+ str(s[i + 2]) + ' ' + str(s[i + 3]) + ' ' + str(s[i + 4]) + '\n')
    i += 5
    j += 1

f.close()
f2.close()