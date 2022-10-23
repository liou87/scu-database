select companyname, round(delaycnt*100.0 / cnt , 2) as percentage
from (
	select shipvia, count(*) as cnt
	from 'order'
	group by shipvia
     )as totalcnt 
inner join (
		select shipvia, count(*) as delaycnt
		from 'order'
		where shippeddate > requireddate
		group by shipvia
	   )as delaycnt on totalcnt.shipvia=delaycnt.shipvia
inner join shipper on totalcnt.shipvia=shipper.id	   
order by percentage;	   
	   
	   	
