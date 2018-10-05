import random

qualification = ['none', 'BM', 'BMBS', 'BmedSci', 'MBChB']
query = "INSERT ALL\n"
for i in range(1, 30):
    query += "  INTO DOCTOR (person_id, qualification) VALUES "
    query += "(" + str(i) + ", '"
    query += random.choice(qualification) + "')"
    query += "\n"
query += 'SELECT 1 FROM DUAL;'
print(query)
