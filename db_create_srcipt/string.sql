SELECT CONCAT(director_name, "->", imdb_score) as "director_name->imdb_score" from movie;
SELECT country, REVERSE(country) as yrtnuoc from movie;
SELECT CONCAT(title, " was released in ", title_year) as title from movie;
SELECT title, CHAR_LENGTH(title) as character_count from movie;
SELECT CONCAT(SUBSTR(title, 1, 8), "...") as short_tile, director_name from movie;