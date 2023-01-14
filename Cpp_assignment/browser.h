#pragma once

#include "graphics.h"

// The class that handles all the graphical elements, and displays the films
class Browser
{
private:
	graphics::Brush br;
	std::vector<class Widget*>* widgets;
	std::vector<class Filter*>* filters;
	std::vector<const class film*>* films;	
	int currentFilmIndex = 0;
	const film* currentFilm;
	bool updateActive = false;

	class browsingButton* forwardButton;
	browsingButton* backwardButton;
	class filteringButton* actionFilteringButton;
	filteringButton* adventureFilteringButton;
	filteringButton* animationFilteringButton;
	filteringButton* comedyFilteringButton;
	filteringButton* crimeFilteringButton;
	filteringButton* dramaFilteringButton;
	filteringButton* familyFilteringButton;
	filteringButton* fantasyFilteringButton;
	filteringButton* film_noirFilteringButton;
	filteringButton* mysteryFilteringButton;
	filteringButton* romanceFilteringButton;
	filteringButton* sci_fiFilteringButton;
	class filteringDoubleSlider* yearFilteringSlider;
	class clearAllFiltersButton* clearFiltersButton;

	// finds the next eligible film from the film vector, and makes it the current one
	void nextEligibleFilm(int increment);
	// nextEligibleFilm() makes this true when it fails to find any eligible films
	bool noEligibleFilms = false;
		
public:
	// used by widgets that change which films can be diplayed
	void activateUpdate() { updateActive = true; }
	// used by filters to check whether the current film is eligible under them
	const film* getCurrentFilm() { return currentFilm; }
	void update();
	void draw();
	void init();
	~Browser();
};