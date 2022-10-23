select
	id,
	orderdate,
	lag(orderdate,1,orderdate) over (order by orderdate) ,
	round(julianday(orderdate)-
	julianday(lag(orderdate,1,orderdate) over (order by orderdate)) , 2)
from 'order'
where customerid='BLONP'
order by orderdate
limit 10;
