select productname,companyname,contactname
from (
	select productname, min(orderdate), companyname,contactname
	from (
	       select id as p_id, productname
	       from product
	       where discontinued != 0
	     )
	inner join orderdetail on productid=p_id
	inner join 'order' on 'order'.id =orderdetail.orderid
	inner join customer on customerid=customer.id
	group by p_id     
     )
order by productname;


