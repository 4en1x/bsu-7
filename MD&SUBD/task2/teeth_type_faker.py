from faker import Faker
import random
fake = Faker()

t = ['baby', 'permanent', 'artificial', 'dental crown', 'absent']
query = "INSERT ALL\n"
for i in range(1, 6):
    query += "  INTO Teeth_Type (id, type) VALUES "
    query += "(" + str(i) + ", '"
    query += t[i-1] + "')"
    query += "\n"
query += 'SELECT 1 FROM DUAL;'
print(query)
