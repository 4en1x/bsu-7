#Task 4

1. Поднимите нижнюю границу минимальной заработной платы в таблице JOB до 1000$.

 ~~~sql
 UPDATE job
 SET minsalary = 1000
 WHERE minsalary < 1000;
 ~~~
 
2. Поднимите минимальную зарплату в таблице JOB на 10% для всех специальностей, кроме финансового директора.

 ~~~sql
 UPDATE job
 SET minsalary = 1.1 * minsalary
 WHERE jobname NOT IN ('FINANCIAL DIRECTOR');
 ~~~
 
3. Поднимите минимальную зарплату в таблице JOB на 10% для клерков и на 20% для финансового директора (одним оператором).

 ~~~sql
 UPDATE job SET minsalary =
 CASE
     WHEN jobname = 'CLERK' THEN 1.1 * minsalary
     WHEN jobname = 'FINANCIAL DIRECTOR' THEN 1.2 * minsalary
     ELSE minsalary
 END;
 ~~~
 
4. Установите минимальную зарплату финансового директора равной 90% от зарплаты исполнительного директора.

 ~~~sql
 UPDATE job
 SET minsalary = 0.9 * (
     SELECT minsalary 
     FROM job
     WHERE jobname = 'EXECUTIVE DIRECTOR'
 )
 WHERE jobname = 'FINANCIAL DIRECTOR';
 ~~~
 
5. Приведите в таблице EMP имена служащих, начинающиеся на букву ‘J’, к нижнему регистру.

 ~~~sql
 UPDATE emp
 SET empname = LOWER(empname)
 WHERE SUBSTR(empname, 1, 1) = 'J';
 ~~~
 
6. Измените в таблице EMP имена служащих, состоящие из двух слов, так, чтобы оба слова в имени начинались с заглавной буквы, а продолжались прописными. 

 ~~~sql
 UPDATE emp
 SET empname = INITCAP(empname)
 WHERE empname LIKE('% %');
 ~~~
 
7. Приведите в таблице EMP имена служащих к верхнему регистру.

 ~~~sql
 UPDATE emp SET empname = UPPER(empname);
 ~~~
 
8. Перенесите отдел исследований (RESEARCH) в тот же город, в котором расположен отдел продаж (SALES).

 ~~~sql
 UPDATE dept
 SET deptaddr = (
     SELECT deptaddr
     FROM dept
     WHERE deptaddr = 'SALES'
 )
 WHERE deptaddr = 'RESEARCH';
 ~~~
 
9. Добавьте нового сотрудника в таблицу EMP. Его имя и фамилия должны совпадать с Вашими, записанными латинскими буквами согласно паспорту, дата рождения также совпадает с Вашей.

 ~~~sql
 INSERT INTO EMP VALUES (7777, 'KANSTANTSIN STSEFANOVICH', to_date('04-07-1998','dd-mm-yyyy'));
 ~~~

10. Определите нового сотрудника (см. предыдущее задание) на работу в бухгалтерию (отдел ACCOUNTING) начиная с текущей даты.

 ~~~sql
 INSERT INTO career VALUES (1004, 7777, 10, CURRENT_DATE, NULL); 
 ~~~
 
11. Удалите все записи из таблицы TMP_EMP. Добавьте в нее информацию о сотрудниках, которые работают клерками в настоящий момент.

 ~~~sql
 CREATE TABLE tmp_emp(
     empno NUMBER(4) PRIMARY KEY,
     empname VARCHAR2(30) NOT NULL, 
     birthdate DATE
 );
 DELETE FROM tmp_emp;
 INSERT INTO tmp_emp
      SELECT *
      FROM emp e
      WHERE e.empno IN (
          SELECT empno
          FROM career c INNER JOIN job j
          ON c.jobno = j.jobno
          WHERE j.jobname = 'CLERK'
          AND startdate IS NOT NULL
          AND enddate IS NULL  
      );
 ~~~
 
12. Добавьте в таблицу TMP_EMP информацию о тех сотрудниках, которые уже не работают на предприятии, а в период работы занимали только одну должность.

 ~~~sql
 INSERT INTO tmp_emp
 SELECT em.* FROM emp em
 INNER JOIN career ca ON em.empno = ca.empno
 WHERE ca.enddate IS NOT NULL
 AND em.empno IN (
     SELECT e.empno
     FROM emp e INNER JOIN career c ON e.empno = c.empno
     GROUP BY e.empno
     HAVING COUNT(c.jobno) = 1
 );
 ~~~
 
13. Выполните тот же запрос для тех сотрудников, которые никогда не приступали к работе на предприятии.

 ~~~sql
 INSERT INTO tmp_emp
 SELECT * FROM emp e
 WHERE e.empno IN (
     SELECT empno FROM career
     WHERE startdate IS NULL
 );
 ~~~
 
14. Удалите все записи из таблицы TMP_JOB и добавьте в нее информацию по тем специальностям, которые не используются в настоящий момент на предприятии.

 ~~~sql
 CREATE TABLE tmp_job (
     jobno NUMBER(4) PRIMARY KEY,
     jobname VARCHAR2(30) NOT NULL,
     minsalary NUMBER(6)
 );
 DELETE FROM tmp_job;
 INSERT INTO tmp_job
 SELECT * FROM job j
 WHERE NOT EXISTS (
     SELECT * FROM career c
     WHERE c.jobno = j.jobno
 );
 ~~~
 
15. Начислите зарплату в размере 120% минимального должностного оклада всем сотрудникам, работающим на предприятии. Зарплату начислять по должности, занимаемой сотрудником в настоящий момент и отнести ее на прошлый месяц относительно текущей даты.

 ~~~sql
 INSERT INTO salary (empno, salvalue, month, year)
 SELECT c.empno, 1.2 * j.minsalary, EXTRACT(MONTH FROM ADD_MONTHS(CURRENT_DATE, -1)), EXTRACT(YEAR FROM ADD_MONTHS(CURRENT_DATE, -1)) - 7
 FROM career c INNER JOIN job j ON c.jobno = j.jobno
 WHERE c.startdate IS NOT NULL AND c.enddate IS NULL;
 ~~~
 
16. Удалите данные о зарплате за прошлый год.

 ~~~sql
 DELETE FROM salary WHERE year = EXTRACT(YEAR FROM CURRENT_DATE) - 1;
 ~~~
 
17. Удалите информацию о карьере сотрудников, которые в настоящий момент уже не работают на предприятии, но когда-то работали.

 ~~~sql
 DELETE FROM career
 WHERE enddate IS NOT NULL AND enddate < CURRENT_DATE;
 ~~~
 
18. Удалите информацию о начисленной зарплате сотрудников, которые в настоящий момент уже не работают на предприятии (можно использовать результаты работы предыдущего запроса)

 ~~~sql
 DELETE FROM salary
 WHERE empno = (
     SELECT empno
     FROM career
     WHERE enddate IS NOT NULL AND enddate < CURRENT_DATE
 );
 ~~~
 
19. Удалите записи из таблицы EMP для тех сотрудников, которые никогда не приступали к работе на предприятии.

 ~~~sql
 DELETE FROM emp
 WHERE empno = (
     SELECT empno
     FROM career
     WHERE startdate IS NULL
 );
 ~~~
