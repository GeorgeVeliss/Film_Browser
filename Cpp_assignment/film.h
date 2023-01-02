#pragma once
#include <string>
#include <vector>
#include <unordered_map>

const enum genre {
	action, adventure, animation, comedy, crime, drama,
	family, fantasy, film_noir, mystery, romance, sci_fi
};

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

class film
{
public:

	std::string title;
	unsigned short year;
	std::string director;
	std::vector<std::string> protagonists;
	std::vector<genre> genres;
	std::string posterFile;
	//std::string summary;

	film(std::string title, unsigned short year, std::string director, std::vector<std::string> protagonists, 
		std::vector<genre> genres, std::string posterFile) :
		title(title), year(year), director(director), protagonists(protagonists), 
		genres(genres), posterFile(posterFile) {}
};

