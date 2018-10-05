from faker import Faker
import random
fake = Faker()

query = "INSERT ALL\n"
for i in range(1000):
    k1, k2, k3 = [0 if random.randint(1, 2) == 1 else 1 for i in range(3)]
    query += "  INTO VISIT (id, visit_datetime, cost, "
    if k1: query += "description, "
    if k2: query += "doctor_id, "
    if k3: query += "card_number, "
    query += "patient_id) VALUES "
    query += "(" + str(i) + ", "
    query += "TO_DATE('" + fake.date(pattern="%Y-%m-%d") + " " + fake.time(pattern="%H:%M:%S") + "', 'YYYY-MM-DD HH24:MI:SS')" + ", "
    query += str(random.randint(0, 99)) + ", "
    if k1: query += "'Some description: " + fake.sentence(nb_words=12) + "', "
    if k2: query += str(random.randint(1, 29)) + ", "
    if k3: query += str(random.randint(10 ** 15, 10 ** 16 - 1)) + ", "
    query += str(random.randint(31, 100)) + ")"
    query += "\n"
query += 'SELECT 1 FROM DUAL;'
print(query)
