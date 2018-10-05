from faker import Faker

fake = Faker()

query = "INSERT ALL\n"
for i in range(1, 100):
    query += "  INTO MEDICINE (id, description, name) VALUES "
    query += "(" + str(i) + ", '"
    query += "Some description: " + fake.sentence(nb_words=6) + "', '"
    query += "Medicine with name: " + fake.word() + "')"
    query += "\n"
query += 'SELECT 1 FROM DUAL;'
print(query)