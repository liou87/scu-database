select categoryname
	, count(*) as categorycount
	, round(avg(unitprice),2) as avg_price
	,min(unitprice) as min_price
	,max(unitprice) as max_price
	,sum(unitprice) as total_price
from product inner join category on categoryid = category.id
group by categoryid
having categorycount>10
order by categoryid;
