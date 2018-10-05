#Task 3_1

### Простейшие запросы

 1. Выдать информацию о местоположении отдела продаж (SALES) компании.

 ~~~sql
 SELECT deptaddr FROM dept WHERE deptname = 'SALES';
 ~~~ 
 
 2. Выдать информацию об отделах, расположенных в Chicago и New York.

 ~~~sql
 SELECT * FROM dept WHERE deptaddr IN ('NEW YORK', 'CHICAGO');
 ~~~ 
 
### Функции
 
 3. Найти минимальную заработную плату, начисленную в 2009 году.

 ~~~sql
 SELECT MIN(salvalue) FROM salary WHERE year = 2009;
 ~~~ 
 
 4. Выдать информацию обо всех работниках, родившихся не позднее 1 января 1960 года.

 ~~~sql
 SELECT * FROM emp WHERE birthdate <= TO_DATE('01-01-1960','dd-mm-yyyy');
 ~~~ 
 
 5. Подсчитать число работников, сведения о которых имеются в базе данных.

 ~~~sql
 SELECT COUNT(*) FROM emp;
 ~~~ 
 
 6. Найти работников, чьё имя состоит из одного слова. Имена выдать на нижнем регистре, с удалением стоящей справа буквы t.

 ~~~sql
 SELECT SUBSTR(
 	      LOWER(empname), 
 	      1, 
 	      CASE WHEN LENGTH(RTRIM(LOWER(empname), 't')) <= LENGTH(empname) - 1 THEN LENGTH(empname) - 1
 	      ELSE LENGTH(empname) 
 	      END  
) AS name_lower_without_t_one_word FROM emp WHERE empname NOT LIKE('% %');
 ~~~ 
 
 7. Выдать информацию о работниках, указав дату рождения в формате день(число), месяц(название), год(название).

 ~~~sql
 SELECT empname, TO_CHAR(birthdate, 'DD-MONTH-YEAR') AS birth_date FROM emp;
 ~~~ 
 То же, но год числом.
 
 ~~~sql
 SELECT empname, TO_CHAR(birthdate, 'DD-MONTH-YYYY') AS birth_date FROM emp;
 ~~~ 
 
 8. Выдать информацию о должностях, изменив названия должности “CLERK” и “DRIVER” на “WORKER”.

 ~~~sql
 SELECT (
 	CASE WHEN jobname IN ('DRIVER', 'CLERK') THEN 'WORKER'
 	ELSE jobname
 	END
 ) AS task_job FROM job;
 ~~~ 
 
### HAVING
 9. Определите среднюю зарплату за годы, в которые были начисления не менее чем за три месяца.

 ~~~sql
 SELECT year, AVG(salvalue)
 FROM salary
 GROUP BY year
 HAVING COUNT(month) >= 3;
 ~~~ 

### СОЕДИНЕНИЕ ПО РАВЕНСТВУ:
10. Выведете ведомость получения зарплаты с указанием имен служащих.

 ~~~sql
 SELECT e.empname, s.month, s.salvalue FROM emp e, salary s WHERE e.empno = s.empno;
 ~~~ 
 
### СОЕДИНЕНИЕ НЕ ПО РАВЕНСТВУ:
11. Укажите сведения о начислении сотрудникам зарплаты, попадающей в вилку:
минимальный оклад по должности - минимальный оклад по должности плюс
пятьсот. Укажите соответствующую вилке должность.

 ~~~sql
 SELECT e.empname, j.jobname, s.salvalue, j.minsalary
 FROM salary s, emp e, career c, job j
 WHERE s.empno = e.empno
 AND c.empno = e.empno
 AND j.jobno = c.jobno
 AND s.salvalue > j.minsalary 
 AND s.salvalue < j.minsalary + 500;
 ~~~ 

### ОБЪЕДИНЕНИЕ ТАБЛИЦ:

###### ВНУТРЕННЕЕ:
12. Укажите сведения о заработной плате, совпадающей с минимальными окладами по должностям (с указанием этих должностей).

 ~~~sql
SELECT e.empname, s.salvalue, j.minsalary, j.jobname 
FROM salary s
      INNER JOIN emp e
          ON (s.empno = e.empno) 
      INNER JOIN career c
          ON (e.empno = c.empno) 
      INNER JOIN job j
          ON (c.jobno = j.jobno) 
WHERE s.salvalue = j.minsalary;
 ~~~ 
 
###### ЕСТЕСТВЕННОЕ:
13. Найдите сведения о карьере сотрудников с указанием вместо номера сотрудника его имени.

 ~~~sql
SELECT e.empname, c.startdate, c.enddate FROM emp e NATURAL JOIN career c;
 ~~~ 
 
###### ПРОСТОЕ ВНУТРЕННЕЕ СОЕДИНЕНИЕ:
14. Найдите сведения о карьере сотрудников с указанием вместо номера сотрудника его имени.

 ~~~sql
SELECT e.empname, c.startdate, c.enddate FROM emp e INNER JOIN career c USING(empno);
 ~~~ 
 
###### ОБЪЕДИНЕНИЕ ТРЁХ И БОЛЬШЕГО ЧИСЛА ТАБЛИЦ:
15. Выдайте сведения о карьере сотрудников с указанием их имён, наименования
должности, и названия отдела.

 ~~~sql
SELECT e.empname, d.deptname, j.jobname, c.startdate, c.enddate
FROM emp e
	NATURAL JOIN career c 
    NATURAL JOIN dept d
    NATURAL JOIN job j
 ~~~ 
 
###### ВНЕШНЕЕ ОБЪЕДИНЕНИЕ:
16. Выдайте сведения о карьере сотрудников с указанием их имён. Какой вид внешнего объединения Вы использовали? Составьте запрос с использованием противоположного вида соединения. Составьте запрос с использованием полного внешнего соединения.

 ###### Right
 ~~~sql
SELECT e.empname, c.startdate, c.enddate
FROM emp e RIGHT OUTER JOIN career c USING(empno)
 ~~~ 
 
 ###### Left
 ~~~sql
SELECT e.empname, c.startdate, c.enddate
FROM emp e LEFT OUTER JOIN career c USING(empno)
 ~~~ 
 
 ###### Full
 ~~~sql
SELECT e.empname, c.startdate, c.enddate
FROM emp e FULL OUTER JOIN career c USING(empno)
 ~~~ 
