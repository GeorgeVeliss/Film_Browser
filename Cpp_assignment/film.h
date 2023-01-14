#pragma once
#include <string>
#include <vector>
#include <unordered_map>

// Const enum for genres, so that only these values are allowed
// useful for quick declaration of films in loadFilms.hpp
const enum genre {
	action, adventure, animation, comedy, crime, drama,
	family, fantasy, film_noir, mystery, romance, sci_fi
};

// Const unordered_map between genres and their respective strings, 
// useful for displaying genre strings
const std::unordered_map<genre, std::string> allGenres =
{
	{ action, "action" },
	{ adventure, "adventure" },
	{ animation, "animation" },
	{ comedy, "comedy" },
	{ crime, "crime" },
	{ drama, "drama" },
	{ family, "family" },
	{ fantasy, "fantasy" },
	{ film_noir, "film-noir" },
	{ mystery, "mystery" },
	{ romance, "romance" },
	{ sci_fi, "sci-fi" }
};

// Contains all the info related to a film
// contains only public fields for ease of access,
// they cannot be altered as they are declared const in loadFilms.hpp
class film
{
public:
	std::string title;
	unsigned short year;
	std::string director;
	std::vector<std::string> protagonists;
	std::vector<genre> genres;
	std::string posterFile;

	film(std::string title, unsigned short year, std::string director, std::vector<std::string> protagonists, 
		std::vector<genre> genres, std::string posterFile) :
		title(title), year(year), director(director), protagonists(protagonists), 
		genres(genres), posterFile(posterFile) {}
};

