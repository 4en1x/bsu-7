 -- 02-a.
 begin
   tax_simple_loop_if;
 end;
 /
 SELECT * FROM salary;
 /
 -- 02-b.
 begin
   tax_loop_cur_case;
 end;
 /
 SELECT * FROM salary;
 /
 -- 02-c.
 begin
   tax_cur_loop_case;
 end;
 /
 SELECT * FROM salary;
 /
 -- 02-d.
 begin
   tax_param(7369);
 end;
 /
 SELECT * FROM salary;
 /

-- 04.
 begin
   tax_param_less(7369, 1, 2, 3);
 end;
 /
 SELECT * FROM salary;
 /

 -- 05.
 SELECT FTAX_PARAM_LESS(EMPNO, 1, 2, 3) FROM SALARY;
 /

 -- 07.
 SELECT * FROM salary WHERE empno = 7369 AND month = 5;
 UPDATE salary SET salvalue = 100 WHERE empno = 7369 AND month = 5;
 SELECT * FROM salary WHERE empno = 7369 AND month = 5;
 UPDATE salary SET salvalue = 10000 WHERE empno = 7369 AND month = 5;
 SELECT * FROM salary WHERE empno = 7369 AND month = 5;
 /

 -- 08.
 SELECT * FROM career WHERE startdate IN ('21-May-1999', '12-Oct-2006');
 DELETE FROM career WHERE startdate = '21-May-1999';
 DELETE FROM career WHERE startdate = '12-Oct-2006';
 SELECT * FROM career WHERE startdate IN ('21-May-1999', '12-Oct-2006');
 /

 -- 09.
 SELECT * FROM EMP WHERE empno in (7369, 7499, 7521);
 UPDATE EMP SET birthdate=NULL WHERE empno = 7369;
 UPDATE EMP SET birthdate='01-Jan-1939' WHERE empno = 7499;
 UPDATE EMP SET birthdate='21-May-1999' WHERE empno = 7521;
 SELECT * FROM EMP WHERE empno in (7369, 7499, 7521);
 /
