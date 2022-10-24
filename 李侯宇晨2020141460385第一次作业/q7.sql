select 
	IFNULL(t2.companyName, "MISSING_NAME"),
	t1.customerid,
	round(t1.ssum, 2)
from(
      select 
      	   a.customerid,
      	   sum(b.quantity*b.unitprice) as ssum,
      	   ntile(4) over (
		order by sum(b.quantity*b.unitprice)
		) as n
      from 'order' a
           join
           orderdetail b on a.id=b.orderid
      group by a.customerid
     )t1
      left join customer t2
      on t2.id=t1.customerid
where t1.n=1 ; 
           
  
