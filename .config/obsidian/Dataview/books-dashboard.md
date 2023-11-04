---
cssclass: cards
banner: "https://www.historyassociates.com/wp-content/uploads/2020/01/books_on_shelf-1024x387.jpg"
---

# Self-Improvement

```dataview
TABLE WITHOUT ID
	"![|80](" + cover_url + ")" as Cover,
	link(file.link, title) as Title,
	author as Author
FROM #self-improvement
WHERE !contains(file.path, "Templates")
SORT title ASC
```

# InfoSec
```dataview
TABLE WITHOUT ID
	"![|80](" + cover_url + ")" as Cover,
	link(file.link, title) as Title,
	author as Author
FROM #infosec 
WHERE !contains(file.path, "Templates")
SORT title ASC
```

# All Books
```dataview
TABLE WITHOUT ID
	"![|80](" + cover_url + ")" as Cover,
	link(file.link, title) as Title,
	author as Author
FROM "References/Books"
WHERE !contains(file.path, "Templates")
SORT title ASC
```