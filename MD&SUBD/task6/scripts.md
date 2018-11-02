#Task 6
1. (1) Составьте запрос на выборку данных с использованием рефлексивного соединения для таблицы из задания 5 лабораторной работы №2

 --- ПРОПУСК ---

2. (2) Составьте запрос на выборку данных с использованием простого оператора CASE ();

 ~~~sql
 SELECT p.first_name ||' '|| p.surname || ' ' || 
     CASE 
         WHEN p.middle_name IS NULL THEN ' do not have middle name' 
         ELSE ' have middle name - ' || p.middle_name 
     END AS result 
 FROM patient pa
 INNER JOIN person p USING(person_id);
 ~~~

3. (3) Составьте запрос на выборку данных с использованием поискового оператора CASE();

 ~~~sql
 SELECT person_id AS id,
     CASE qualification
         WHEN 'BM' THEN 'just regular doctor' 
         WHEN 'BMBS' THEN 'this doctor have degree' 
         WHEN 'none' THEN 'this not even a real doctor!' 
         ELSE 'other type of doctor'
     END AS qualification 
 FROM doctor;
 ~~~
 
4. (4, 5)

 Составьте запрос на выборку данных с использованием оператора WITH();
 
 Составьте запрос на выборку данных с использованием встроенного представления();

 ~~~sql
 WITH regular_doctors AS (
     SELECT * FROM doctor d
     INNER JOIN person p USING(person_id)
     WHERE d.qualification = 'BM'
 ) SELECT first_name ||' '|| surname AS name FROM regular_doctors;
 ~~~

5. (6) Составьте запрос на выборку данных с использованием некоррелированного запроса;

 ~~~sql
 SELECT * FROM patient 
 INNER JOIN person USING(person_id) 
 WHERE personal_doctor_id IN (
     SELECT person_id FROM doctor 
     WHERE qualification = 'BMBS'
 );
 ~~~
 
6. (7) Составьте запрос на выборку данных с использованием коррелированного запроса;

 ~~~sql
 SELECT * FROM patient p 
 INNER JOIN person USING(person_id) 
 WHERE personal_doctor_id IN (
     SELECT person_id FROM doctor d
     WHERE qualification = 'BMBS'
     AND p.personal_doctor_id = d.person_id
 );
 ~~~
 
7. (8, 9)

 Составьте запрос на выборку данных с использованием функции NULLIF;
 
 Составьте запрос на выборку данных с использованием функции NVL2;

 ~~~sql
 SELECT p.surname, p.first_name, NVL2(NULLIF(qualification, 'none'),'have qualification', 'do not have qualification') AS qualification
 FROM doctor d 
 INNER JOIN person p USING(person_id);
 ~~~
 
8. (10) Составьте запрос на выборку данных с использованием TOP-N анализа();

 ~~~sql
 SELECT * FROM patient 
 INNER JOIN person USING(person_id) 
 WHERE rownum <= 10;
 ~~~
 
9. (11) Составьте запрос на выборку данных с использованием функции ROLLUP();

 ~~~sql
 SELECT SUM(cost) / COUNT(cost) AS middle_cost, patient_id FROM visit
 GROUP BY ROLLUP(patient_id);
 ~~~
 
10. (12) Составьте запрос на использование оператора MERGE языка манипулирования данными.

 ~~~sql
 CREATE TABLE person_2 AS (
     SELECT person_id + 30 AS person_id, first_name, surname, middle_name, address, birth_date
     FROM person
 );
 
 MERGE INTO person_2 p_2
 USING (SELECT * FROM person) p
 ON (p.person_id = p_2.person_id)
 WHEN MATCHED THEN UPDATE SET p_2.first_name = 'new_' || p.first_name     
 WHEN NOT MATCHED THEN INSERT (p_2.person_id, p_2.first_name, p_2.surname, p_2.middle_name, p_2.address, p_2.birth_date)
 VALUES (p.person_id, p.first_name, p.surname, p.middle_name, p.address, p.birth_date);
 
 SELECT * FROM person_2;
 ~~~

