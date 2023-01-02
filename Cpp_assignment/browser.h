#pragma once

#include "Widget.h"
#include "film.h"
#include "graphics.h"
#include "filter.h"

class Browser
{
private:	
	std::vector<Widget*>* widgets;
	std::vector<Filter*>* filters;
	std::vector<film*>* films;
	graphics::Brush br;
	int currentFilmIndex = 0;
	film* currentFilm;
	class browsingButton* forwardButton;
	class browsingButton* backwardButton;
	class filteringButton* actionFilteringButton;
	class filteringButton* adventureFilteringButton;
	class filteringButton* animationFilteringButton;
	class filteringButton* comedyFilteringButton;
	class filteringButton* crimeFilteringButton;
	class filteringButton* dramaFilteringButton;
	class filteringButton* familyFilteringButton;
	class filteringButton* fantasyFilteringButton;
	class filteringButton* film_noirFilteringButton;
	class filteringButton* mysteryFilteringButton;
	class filteringButton* romanceFilteringButton;
	class filteringButton* sci_fiFilteringButton;

	bool filmEligible(std::string filter, film* film);
	bool genreEligible(std::string filter, film* film);
	//bool yearEligible(film*);
	bool noEligibleFilms = false;
	
	
public:
	//bool debug_mode = false;
	//void setDebugMode(bool d) { debug_mode = d; }
	//bool getDebugMode() { return debug_mode; }
	//std::vector<filteringButton*>* getGenreFilters();
	bool updateNeeded = false;
	void update();
	void draw();
	void init();
	//Browser();
	~Browser();
	void clearFilters();
};