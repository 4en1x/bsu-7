 /*#1*/
 SELECT * FROM pensioner;
 DELETE FROM pensioner WHERE empno = 7369;
 INSERT INTO pensioner (empno, empname, birthdate) VALUES (1235, 'MICHAEL', '17-Dec-1946');
 SELECT * FROM pensioner;
 DELETE FROM pensioner WHERE empno = 1235;
 SELECT * FROM pensioner;

 /*#2*/
 SELECT * FROM dismissed;
 DELETE FROM dismissed WHERE empno = 7369;
 SELECT * FROM dismissed;
 INSERT INTO dismissed (empno, empname, deptname, enddate, jobname) VALUES (7499, 'ALLEN', 'SALES', '25-Oct-2010', 'EXECUTIVE DIRECTOR');
 SELECT * FROM dismissed;

 /*#3*/
 SELECT * FROM kvartal;
 DELETE FROM kvartal WHERE sotrudnik = 'ALLEN';
 SELECT * FROM kvartal;
 INSERT INTO kvartal (sotrudnik, dolzhnost, itogo_3_kv) VALUES ('ALLE', 'EXECUTIVE DIRECTOR', 16100);
 SELECT * FROM kvartal;

 /*#4*/
 SELECT * FROM task_4;
 DELETE FROM task_4 WHERE empno = 7499;
 SELECT * FROM task_4;
 INSERT INTO task_4 (empno, empname, deptname, enddate, jobname, month_and_sum) VALUES (7499, 'ALLEN', 'SALES', '31-Dec-2005', 'EXECUTIVE DIRECTOR', '11, 8050');
 SELECT * FROM task_4;
