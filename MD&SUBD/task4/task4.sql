 UPDATE job
 SET minsalary = 1000
 WHERE minsalary < 1000;

 UPDATE job
 SET minsalary = 1.1 * minsalary
 WHERE jobname NOT IN ('FINANCIAL DIRECTOR');

 UPDATE job SET minsalary =
 CASE
     WHEN jobname = 'CLERK' THEN 1.1 * minsalary
     WHEN jobname = 'FINANCIAL DIRECTOR' THEN 1.2 * minsalary
     ELSE minsalary
 END;

 UPDATE job
 SET minsalary = 0.9 * (
     SELECT minsalary
     FROM job
     WHERE jobname = 'EXECUTIVE DIRECTOR'
 )
 WHERE jobname = 'FINANCIAL DIRECTOR';

 UPDATE emp
 SET empname = LOWER(empname)
 WHERE SUBSTR(empname, 1, 1) = 'J';

 UPDATE emp
 SET empname = INITCAP(empname)
 WHERE empname LIKE('% %');

 UPDATE emp SET empname = UPPER(empname);

 UPDATE dept
 SET deptaddr = (
     SELECT deptaddr
     FROM dept
     WHERE deptaddr = 'SALES'
 )
 WHERE deptaddr = 'RESEARCH';

 INSERT INTO EMP VALUES (7777, 'KANSTANTSIN STSEFANOVICH', to_date('04-07-1998','dd-mm-yyyy'));

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

 INSERT INTO tmp_emp
 SELECT * FROM emp e
 WHERE e.empno IN (
     SELECT empno FROM career
     WHERE startdate IS NULL
 );

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

 INSERT INTO salary (empno, salvalue, month, year)
 SELECT c.empno, 1.2 * j.minsalary, EXTRACT(MONTH FROM ADD_MONTHS(CURRENT_DATE, -1)), EXTRACT(YEAR FROM ADD_MONTHS(CURRENT_DATE, -1)) - 7
 FROM career c INNER JOIN job j ON c.jobno = j.jobno
 WHERE c.startdate IS NOT NULL AND c.enddate IS NULL;

 DELETE FROM salary WHERE year = EXTRACT(YEAR FROM CURRENT_DATE) - 1;

 DELETE FROM career
 WHERE enddate IS NOT NULL AND enddate < CURRENT_DATE;

 DELETE FROM salary
 WHERE empno = (
     SELECT empno
     FROM career
     WHERE enddate IS NOT NULL AND enddate < CURRENT_DATE
 );

 DELETE FROM emp
 WHERE empno = (
     SELECT empno
     FROM career
     WHERE startdate IS NULL
 );
