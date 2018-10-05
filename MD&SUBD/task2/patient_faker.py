import random

query = "INSERT ALL\n"
for i in range(31, 101):
    query += "  INTO PATIENT (person_id, personal_doctor_id) VALUES "
    query += "(" + str(i) + ", "
    query += str(random.choice(range(1, 30))) + ")"
    query += "\n"
query += 'SELECT 1 FROM DUAL;'
print(query)