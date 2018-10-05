from faker import Faker
import random
fake = Faker()

query = "INSERT ALL\n"
for i in range(2000):
    query += "  INTO PRESCRIPTION (visit_id, medicine_id, prescription_date) VALUES "
    query += "(" + str(random.randint(0, 999)) + ", "
    query += str(random.randint(1, 99)) + ", "
    query += "TO_DATE('" + fake.date(pattern="%Y-%m-%d") + "', 'YYYY-MM-DD'))"
    query += "\n"
query += 'SELECT 1 FROM DUAL;'
print(query)
