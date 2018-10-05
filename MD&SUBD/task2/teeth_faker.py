import random

query = "INSERT ALL\n"
for i in range(31, 101):
    for j in range(32):
        query += "  INTO TEETH (patient_id, teeth_type_id, teeth_number) VALUES "
        query += "(" + str(i) + ", "
        query += str(random.choice(range(1, 6))) + ", "
        query += str(j + 1) + ")"
        query += "\n"
query += 'SELECT 1 FROM DUAL;'
print(query)