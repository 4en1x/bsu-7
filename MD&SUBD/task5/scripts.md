#Task 5

1. Создайте представление, содержащее данные о сотрудниках пенсионного возраста.

 ~~~sql
 CREATE VIEW pensioner AS
 SELECT * FROM emp
 WHERE MONTHS_BETWEEN(SYSDATE, birthdate) / 12 >= 60;
 ~~~

2. Создайте представление, содержащее данные об уволенных сотрудниках: имя сотрудника, дата увольнения, отдел, должность.

 ~~~sql
 CREATE VIEW dismissed (empname, enddate, deptname, jobname, empno) AS
 SELECT e.empname, c.enddate, d.deptname, j.jobname, e.empno
 FROM emp e 
     INNER JOIN career c ON e.empno = c.empno
     INNER JOIN dept d ON d.deptno = c.deptno
     INNER JOIN job j ON j.jobno = c.jobno
 WHERE c.enddate IS NOT NULL;
 ~~~
 
3. Создайте представление, содержащее имя сотрудника, должность, занимаемую сотрудником в данный момент, суммарную заработную плату сотрудника за третий квартал 2010 года. Первый столбец назвать Sotrudnik, второй – Dolzhnost, третий – Itogo_3_kv.

 ~~~sql
 CREATE VIEW kvartal (sotrudnik, dolzhnost, itogo_3_kv) AS
 SELECT e.empname, j.jobname, SUM(s.salvalue)
 FROM job j
     INNER JOIN career c ON j.jobno = c.jobno
     INNER JOIN emp e ON e.empno = c.empno
     INNER JOIN salary s ON s.empno = e.empno
 WHERE s.year = 2010 
     AND s.month BETWEEN 7 AND 9
     AND c.enddate IS NULL
 GROUP BY e.empname, j.jobname;
 ~~~
 
4. На основе представления из задания 2 и таблицы SALARY создайте представление, содержащее данные об уволенных сотрудниках, которым зарплата начислялась более 2 раз. В созданном представлении месяц начисления зарплаты и сумма зарплаты вывести в одном столбце, в качестве разделителя использовать запятую.

 ~~~sql
 CREATE VIEW task_4 AS
 SELECT d.*, s.month || ', ' || s.salvalue AS month_and_sum
 FROM dismissed d INNER JOIN salary s ON s.empno = d.empno
 WHERE s.empno IN (
     SELECT empno
     FROM dismissed NATURAL JOIN salary
     GROUP BY empno
     HAVING COUNT(salvalue) > 2
 );
 ~~~
