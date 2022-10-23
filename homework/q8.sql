select a.regiondescription, b.firstname,b.lastname,max(b.birthdate)
from
	(
	select a.employeeid, e.regiondescription,e.id
	from(
		select c.employeeid,d.id,d.regionid
		from
		    employeeterritory c
		    join
		    territory d
		    on c.territoryid=d.id
	    )a
	join
	region e
	on a.regionid=e.id
	)a
	join 
	employee b
	on a.employeeid=b.id
group by a.id
order by a.id;
