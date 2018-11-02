 SELECT p.first_name ||' '|| p.surname || ' ' ||
     CASE
         WHEN p.middle_name IS NULL THEN ' do not have middle name'
         ELSE ' have middle name - ' || p.middle_name
     END AS result
 FROM patient pa
 INNER JOIN person p USING(person_id);

 SELECT person_id AS id,
     CASE qualification
         WHEN 'BM' THEN 'just regular doctor'
         WHEN 'BMBS' THEN 'this doctor have degree'
         WHEN 'none' THEN 'this not even a real doctor!'
         ELSE 'other type of doctor'
     END AS qualification
 FROM doctor;

 WITH regular_doctors AS (
     SELECT * FROM doctor d
     INNER JOIN person p USING(person_id)
     WHERE d.qualification = 'BM'
 ) SELECT first_name ||' '|| surname AS name FROM regular_doctors;

 SELECT * FROM patient
 INNER JOIN person USING(person_id)
 WHERE personal_doctor_id IN (
     SELECT person_id FROM doctor
     WHERE qualification = 'BMBS'
 );

 SELECT * FROM patient p
 INNER JOIN person USING(person_id)
 WHERE personal_doctor_id IN (
     SELECT person_id FROM doctor d
     WHERE qualification = 'BMBS'
     AND p.personal_doctor_id = d.person_id
 );

 SELECT p.surname, p.first_name, NVL2(NULLIF(qualification, 'none'),'have qualification', 'do not have qualification') AS qualification
 FROM doctor d
 INNER JOIN person p USING(person_id);

 SELECT * FROM patient
 INNER JOIN person USING(person_id)
 WHERE rownum <= 10;

 SELECT SUM(cost) / COUNT(cost) AS middle_cost, patient_id FROM visit
 GROUP BY ROLLUP(patient_id);

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





