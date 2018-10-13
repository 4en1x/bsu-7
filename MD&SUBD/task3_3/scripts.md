#Task 3_3

##### Рефлексивное соединение. Представление отношений родитель-потомок
При выводе записей потомков требуется включить информацию о родителях. Требуется представить имя каждого сотрудника таблицы EMP а также имя его руководителя:

 ~~~sql
 SELECT x.empname || ' works for ' || y.empname AS emp_manager
 FROM EMP x INNER JOIN EMP y 
 ON x.manager_id = y.empno
 ORDER BY y.empname;
 ~~~

##### Иерархический запрос
Требуется представить имя каждого сотрудника таблицы EMP (даже сотрудника,
которому не назначен руководитель) и имя его руководителя.

 ~~~sql
 SELECT empname || ' reports to ' || PRIOR empname AS manager_emp
 FROM emp
 START WITH manager_id IS NULL
 CONNECT BY PRIOR empno = manager_id;
 ~~~

##### Представление отношений потомок-родитель-прародитель
Требуется показать иерархию от CLARK до JOHN KLINTON

 ~~~sql
 SELECT REVERSE(LTRIM(SYS_CONNECT_BY_PATH(REVERSE(empname), '>--'), '>--')) as Leaf__Branch__Root
 FROM emp
 WHERE empname = 'CLARK'
 START WITH manager_id is null
 CONNECT BY PRIOR empno = manager_id;
 ~~~
  
##### Иерархическое представление таблицы
Требуется получить результирующее множество, описывающее иерархию всей
таблицы

 ~~~sql
 SELECT LTRIM(SYS_CONNECT_BY_PATH(empname, '-->'), '-->') as Emp_Tree
 FROM emp
 START WITH manager_id IS NULL
 CONNECT BY PRIOR empno = manager_id;
 ~~~
 
##### Представление уровня иерархии
Требуется показать уровень иерархии каждого сотрудника

 ~~~sql
 SELECT LPAD(' ', 2 * (level - 1), '-') || empname Org_Chart
 FROM emp
 START WITH manager_id IS NULL
 CONNECT BY PRIOR empno = manager_id;
 ~~~
 
##### Выбор всех дочерних строк для заданной строки
Требуется найти всех служащих, которые явно или неявно подчиняются ALLEN

 ~~~sql
 SELECT empname
 FROM emp
 WHERE empname != 'ALLEN'
 START WITH empname = 'ALLEN'
 CONNECT BY PRIOR empno = manager_id;
 ~~~