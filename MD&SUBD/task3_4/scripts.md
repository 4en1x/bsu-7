#Task 3_4

##### 1. Добавление, вычитание дней, месяцев, лет.
Требуется используя значения столбца START_DATE получить дату за десять дней до и после приема на работу, пол года до и после приема на работу, год до и после приема на работу сотрудника JOHN KLINTON.

 ~~~sql
 SELECT 
  startdate + 10 AS "+10 days",
  startdate - 10 AS "-10 days",
  ADD_MONTHS(startdate, 6) AS "+half of the year",
  ADD_MONTHS(startdate, -6) AS "-half of the year",
  ADD_MONTHS(startdate, 12) AS "+year",
  ADD_MONTHS(startdate, -12) AS "-year"
 FROM EMP e INNER JOIN CAREER c
 ON e.empno = c.empno
 WHERE e.empname = 'JOHN KLINTON';
 ~~~
 
##### 2. Определение количества дней между двумя датами.
Требуется найти разность между двумя датами и представить результат в днях. Вычислите разницу в днях между датами приема на работу сотрудников JOHN MARTIN и ALEX BOUSH.

 ~~~sql
 SELECT john_startdate - alex_startdate
 FROM (
   SELECT startdate AS john_startdate  
   FROM EMP e INNER JOIN CAREER c
   ON e.empno = c.empno
   WHERE e.empname = 'JOHN KLINTON'
 ),
 (
   SELECT startdate AS alex_startdate
   FROM EMP e INNER JOIN CAREER c
   ON e.empno = c.empno
   WHERE e.empname = 'ALEX BOUSH'
 );
 ~~~
 
##### 3. Определение количества месяцев или лет между датам.
Требуется найти разность между двумя датами в месяцах и в годах.

 ~~~sql
 SELECT MONTHS_BETWEEN(john_startdate, alex_startdate) AS diff_month, MONTHS_BETWEEN(john_startdate, alex_startdate) / 12 AS diff_years
 FROM (
   SELECT startdate AS john_startdate  
   FROM EMP e INNER JOIN CAREER c
   ON e.empno = c.empno
   WHERE e.empname = 'JOHN KLINTON'
 ),
 (
   SELECT startdate AS alex_startdate
   FROM EMP e INNER JOIN CAREER c
   ON e.empno = c.empno
   WHERE e.empname = 'ALEX BOUSH'
 );
 ~~~
 
##### 4. Определение интервала времени между текущей и следующей записями
Требуется определить интервал времени в днях между двумя датами. Для каждого сотрудника 20-го отделе найти сколько дней прошло между датой его приема на работу и датой приема на работу следующего сотрудника.

 ~~~sql
 SELECT empname, startdate, next_startdate - startdate AS diff FROM (
    SELECT startdate, empname, LEAD(startdate) OVER (ORDER BY startdate) AS next_startdate
    FROM dept d 
    INNER JOIN career c ON c.deptno = d.deptno
    INNER JOIN emp e ON c.empno = e.empno
    WHERE d.deptno = 20
 );
 ~~~
 
##### 5. Определение количества дней в году
Требуется подсчитать количество дней в году по столбцу START_DATE.

 ~~~sql
 SELECT startdate, ADD_MONTHS(TRUNC(startdate, 'y'), 12) - TRUNC(startdate, 'y') AS how_many_days
 FROM career; 
 ~~~
 
##### 6. Извлечение единиц времени из даты
Требуется разложить текущую дату на день, месяц, год, секунды, минуты, часы.
Результаты вернуть в численном виде.

 ~~~sql
 SELECT
   TO_NUMBER(TO_CHAR(SYSDATE, 'hh24')) hour,
   TO_NUMBER(TO_CHAR(SYSDATE, 'mi')) min,
   TO_NUMBER(TO_CHAR(SYSDATE, 'ss')) sec,
   TO_NUMBER(TO_CHAR(SYSDATE, 'dd')) day,
   TO_NUMBER(TO_CHAR(SYSDATE, 'mm')) mth,
   TO_NUMBER(TO_CHAR(SYSDATE, 'yyyy')) year
 FROM DUAL;
 ~~~
 
##### 7. Определение первого и последнего дней месяца
Требуется получить первый и последний дни текущего месяца.

 ~~~sql
 SELECT TRUNC(SYSDATE, 'mm') firstday, LAST_DAY(SYSDATE) lastday FROM DUAL;
 ~~~
 
##### 8. Выбор всех дат года, выпадающих на определенный день недели
Требуется возвратить даты начала и конца каждого из четырех кварталов данного года.

 ~~~sql
 SELECT 
  rownum AS quartal, 
  ADD_MONTHS(TRUNC(SYSDATE, 'y'), (rownum - 1) * 3) AS start_date,
  ADD_MONTHS(TRUNC(SYSDATE, 'y'), rownum * 3) - 1 AS end_date
 FROM DUAL
 CONNECT BY level <= 4;
 ~~~
 
##### 9. Выбор всех дат года, выпадающих на определенный день недели
Требуется найти все даты года, соответствующие заданному дню недели. Сформируйте список понедельников текущего года.

 ~~~sql
 SELECT * FROM (
   SELECT TRUNC(SYSDATE, 'y') + level - 1 dy
   FROM DUAL
   CONNECT BY level <= ADD_MONTHS(TRUNC(SYSDATE, 'y'), 12) - TRUNC(SYSDATE, 'y')
 )
 WHERE TO_CHAR(dy, 'dy') = 'mon';
 ~~~
 
##### 10. Создание календаря
Требуется создать календарь на текущий месяц. Календарь должен иметь семь столбцов в ширину и пять строк вниз.

 ~~~sql
 SELECT 
  MAX(CASE dw WHEN 2 THEN dm END) Mo,
  MAX(CASE dw WHEN 3 THEN dm END) Tu,
  MAX(CASE dw WHEN 4 THEN dm END) We,
  MAX(CASE dw WHEN 5 THEN dm END) Th,
  MAX(CASE dw WHEN 6 THEN dm END) Fr,
  MAX(CASE dw WHEN 7 THEN dm END) Sa,
  MAX(CASE dw WHEN 1 THEN dm END) Su
 FROM (
   SELECT * FROM (
     SELECT
       TO_CHAR(TRUNC(SYSDATE, 'mm') + level - 1, 'iw') wk,
       TO_CHAR(TRUNC(SYSDATE, 'mm') + level - 1, 'dd') dm,
       TO_NUMBER(TO_CHAR(TRUNC(SYSDATE, 'mm') + level - 1, 'd')) dw,
       TO_CHAR(TRUNC(SYSDATE, 'mm') + level - 1, 'mm') curr_mth,
       TO_CHAR(SYSDATE, 'mm') mth
     FROM DUAL
     CONNECT BY LEVEL <=31
   )
   WHERE curr_mth = mth
 )
 GROUP BY wk ORDER BY wk;
 ~~~