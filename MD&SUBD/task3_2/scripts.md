#Task 3_2

##### ПОДЗАПРОСЫ, ВЫБИРАЮЩИЕ ОДНУ СТРОКУ
 1. Найти имена сотрудников, получивших за годы начисления зарплаты
минимальную зарплату.

 ~~~sql
 SELECT e.empname
 FROM emp e
 WHERE (
     SELECT MIN(s.salvalue)
     FROM salary s
     WHERE s.empno = e.empno
 )
 IN (
     SELECT j.minsalary
     FROM job j NATURAL JOIN career c
     WHERE e.empno = c.empno
 );
 ~~~

##### ПОДЗАПРОСЫ, ВОЗВРАЩАЮЩИЕ БОЛЕЕ ОДНОЙ СТРОКИ
 2. Найти имена сотрудников, работавших или работающих в тех же отделах, в которых работал или работает сотрудник с именем RICHARD MARTIN.

 ~~~sql
 SELECT e.empname
 FROM emp e NATURAL JOIN career c
 WHERE c.deptno IN (
     SELECT c.deptno
     FROM career c NATURAL JOIN emp e
     WHERE e.empname = 'RICHARD MARTIN'
 )
 AND e.empname != 'RICHARD MARTIN'
 GROUP BY e.empname;
 ~~~

##### СРАВНЕНИЕ БОЛЕЕ ЧЕМ ПО ОДНОМУ ЗНАЧЕНИЮ
 3. Найти имена сотрудников, работавших или работающих в тех же отделах и должностях, что и сотрудник &#39;RICHARD MARTIN&#39;.

 ~~~sql
 SELECT e.empname
 FROM emp e NATURAL JOIN career c
 WHERE (c.deptno, c.jobno) IN (
     SELECT c.deptno, c.jobno
     FROM career c NATURAL JOIN emp e
     WHERE e.empname = 'RICHARD MARTIN'
 )
 AND e.empname != 'RICHARD MARTIN'
 GROUP BY e.empname;
 ~~~

##### ОПЕРАТОРЫ ANY/ALL
 4. Найти сведения о номерах сотрудников, получивших за какой-либо месяц зарплату большую, чем средняя зарплата за 2007 г. или большую чем средняя зарплата за 2008г.

 
 ~~~sql
 SELECT empno
 FROM salary
 WHERE (
     SELECT AVG(salvalue)
     FROM salary
     WHERE year = 2007
 ) < ANY(salvalue)
 OR (
     SELECT AVG(salvalue)
     FROM salary
     WHERE year = 2008
 ) < ANY(salvalue)
 GROUP BY empno;
 ~~~

 5. Найти сведения о номерах сотрудников, получивших зарплату за какой-либо месяц большую, чем средние зарплаты за все годы начислений.

 ~~~sql
 SELECT empno FROM salary
 WHERE (
     SELECT AVG(salvalue) FROM salary
 ) < ANY(salvalue)
 GROUP BY empno;
 ~~~
 
##### ИСПОЛЬЗОВАНИЕ HAVING С ВЛОЖЕННЫМИ ПОДЗАПРОСАМИ
 6. Определить годы, в которые начисленная средняя зарплата была больше средней зарплаты за все годы начислений.

 ~~~sql
 SELECT year FROM salary
 GROUP BY year HAVING AVG(salvalue) > (
     SELECT AVG(salvalue) FROM salary
 );
 ~~~
 
##### КОРРЕЛИРУЮЩИЕ ПОДЗАПРОСЫ
 7. Определить номера отделов, в которых работали или работают сотрудники, имеющие начисления зарплаты.

 ~~~sql
 SELECT deptno FROM dept d WHERE deptno IN (
     SELECT deptno FROM career c 
     NATURAL JOIN emp e
     NATURAL JOIN salary s
     WHERE s.salvalue IS NOT NULL
 )
 GROUP BY deptno;
 ~~~
 
##### ОПЕРАТОР EXISTS
 8. Определить номера отделов, в которых работали или работают сотрудники, имеющие начисления зарплаты.

 ~~~sql
 SELECT deptno FROM dept d WHERE EXISTS (
     SELECT salvalue FROM career c
     NATURAL JOIN emp e
     NATURAL JOIN salary s
     WHERE d.deptno = c.deptno
 );
 ~~~
 
##### ОПЕРАТОР NOT EXISTS
 9. Определить номера отделов, для сотрудников которых не начислялась зарплата.

 ~~~sql
 SELECT deptno FROM dept d WHERE NOT EXISTS (
     SELECT salvalue FROM career c
     NATURAL JOIN emp e
     NATURAL JOIN salary s
     WHERE d.deptno = c.deptno
 );
 ~~~
  
##### СОСТАВНЫЕ ЗАПРОСЫ
 10. Вывести сведения о карьере сотрудников с указанием названий и адресов отделов вместо номеров отделов.

 ~~~sql
 SELECT e.empname, d.deptname, d.deptaddr, c.startdate, c.enddate
 FROM emp e NATURAL JOIN career c NATURAL JOIN dept d;
 ~~~
 
##### ОПЕРАТОР CAST
 11. Определить целую часть средних зарплат, по годам начисления.

 ~~~sql
 SELECT year, AVG(salvalue) AS salvalue, CAST(AVG(salvalue) AS NUMBER(10)) AS int_part_salvalue
FROM salary GROUP BY year;
 ~~~

##### ОПЕРАТОР CASE
 12. Разделите сотрудников на возрастные группы: A) возраст 20-30 лет; B) 31-40 лет; C) 41-50; D) 51-60 или возраст не определён.

 ~~~sql
 SELECT empno, empname,
    CASE
        WHEN MONTHS_BETWEEN (SYSDATE, birthdate) / 12 >= 20 AND MONTHS_BETWEEN (SYSDATE, birthdate) / 12 <= 30 THEN 'A'
        WHEN MONTHS_BETWEEN (SYSDATE, birthdate) / 12 >= 31 AND MONTHS_BETWEEN (SYSDATE, birthdate) / 12 <= 40 THEN 'B'
        WHEN MONTHS_BETWEEN (SYSDATE, birthdate) / 12 >= 41 AND MONTHS_BETWEEN (SYSDATE, birthdate) / 12 <= 50 THEN 'C'
        WHEN MONTHS_BETWEEN (SYSDATE, birthdate) / 12 >= 51 AND MONTHS_BETWEEN (SYSDATE, birthdate) / 12 <= 60 THEN 'D'
        ELSE NULL
    END
 AS age_group FROM emp;
 ~~~
 
 13. Перекодируйте номера отделов, добавив перед номером отдела буквы BI для номеров &lt;=20, буквы LN для номеров &gt;=30.

 ~~~sql
 SELECT deptno,
 CASE
     WHEN deptno <= 20 THEN CONCAT('BI', CAST(deptno AS VARCHAR(10)))
     WHEN deptno >= 30 THEN CONCAT('LN', CAST(deptno AS VARCHAR(10)))
 END
 AS new_deptno, deptname, deptaddr FROM dept;
 ~~~
 
##### ОПЕРАТОР COALESCE (объединяться)
 14. Выдать информацию о сотрудниках из таблицы EMP, заменив отсутствие данного
о дате рождения датой &#39;01-01-1000&#39;.

 ~~~sql
 SELECT empno, empname,
 COALESCE(birthdate, TO_DATE('01-01-1000', 'dd-mm-yyyy')) AS birthdate
 FROM emp
 ~~~
