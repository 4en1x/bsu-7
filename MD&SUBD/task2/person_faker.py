from faker import Faker
import random
fake = Faker()

qualification = ['none', 'BM', 'BMBS', 'BmedSci', 'MBChB']
query = "INSERT ALL\n"
for i in range(1, 101):
    if random.randint(1, 2) == 1:
        query += "  INTO Person (person_id, first_name, surname, middle_name, address, birth_date) VALUES "
        query += "(" + str(i) + ", '"
        query += fake.first_name() + "', '"
        query += fake.last_name() + "', '"
        query += fake.first_name() + "', '"
        query += fake.address() + "', "
        query += "TO_DATE('" + fake.date(pattern="%Y-%m-%d") + "', 'YYYY-MM-DD'))"
        query += "\n"
    else:
        query += "  INTO Person (person_id, first_name, surname, address, birth_date) VALUES "
        query += "(" + str(i) + ", '"
        query += fake.first_name() + "', '"
        query += fake.last_name() + "', '"
        query += fake.address() + "', "
        query += "TO_DATE('" + fake.date(pattern="%Y-%m-%d") + "', 'YYYY-MM-DD'))"
        query += "\n"
query += 'SELECT 1 FROM DUAL;'
print(query)
