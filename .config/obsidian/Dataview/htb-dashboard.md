---
banner: "https://www.crest-approved.org/wp-content/uploads/2022/11/htb-header.png"
banner_y: 0.485
---

# Machines
```dataview
TABLE WITHOUT ID
	"![|55](" + card_url +")" as Card,
	link(file.link, name) as Name,
	"![|48]("+ os +")" as OS,
	difficulty as Difficulty,
	release_date as Release,
	ip as IP,
	status as Status
FROM #htb-machines 
WHERE !contains(file.path,"_Templates")
SORT status DESC
```