SELECT x.empname || ' works for ' || y.empname AS emp_manager
FROM EMP x INNER JOIN EMP y 
ON x.manager_id = y.empno
ORDER BY y.empname;

SELECT empname || ' reports to ' || PRIOR empname AS manager_emp
FROM emp
START WITH manager_id IS NULL
CONNECT BY PRIOR empno = manager_id;

SELECT REVERSE(LTRIM(SYS_CONNECT_BY_PATH(REVERSE(empname), '>--'), '>--')) as Leaf__Branch__Root
FROM emp
WHERE empname = 'CLARK'
START WITH manager_id is null
CONNECT BY PRIOR empno = manager_id;

SELECT LTRIM(SYS_CONNECT_BY_PATH(empname, '-->'), '-->') as Emp_Tree
FROM emp
START WITH manager_id IS NULL
CONNECT BY PRIOR empno = manager_id;

SELECT LPAD(' ', 2 * (level - 1), '-') || empname Org_Chart
FROM emp
START WITH manager_id IS NULL
CONNECT BY PRIOR empno = manager_id;

SELECT empname
FROM emp
WHERE empname != 'ALLEN'
START WITH empname = 'ALLEN'
CONNECT BY PRIOR empno = manager_id;