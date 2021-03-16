SELECT * FROM (SELECT title, rating from movies JOIN ratings on movies.id = ratings.movie_id WHERE year = 2010 ORDER BY title) WHERE rating IS NOT NULL ORDER BY rating DESC;

