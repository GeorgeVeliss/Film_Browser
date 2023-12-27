#include "graphics.h"
#include "browser.h"
#include "config.h"
#include "loadFilms.hpp"
#include "browsingButton.h"
#include "filteringButton.h"
#include "filteringDoubleSlider.h"
#include "clearAllFiltersButton.h"

void Browser::update() 
{
	// Update all widgets
	for (Widget* w : *widgets)
		w->update();

	// If the current state of some widget changes which films are to be displayed
	// then that widget has also made updateActive == true, so we enter this code block
	// and make the necessary changes
	if (updateActive) {

		// If the button that clears all filters is pressed, clear the filters away!
		if (clearFiltersButton->isPressed())
			for (auto filter : *filters)
				filter->clearFilter();

		// Search through every film, starting with the currently displayed film,
		// find the next eligible one by moving forward by one film at each step,
		// and make it the currently displayed film
		nextEligibleFilm(1);

		// If you found no eligible films in the above search,
		// activate noEligibleFilms and stop running update()
		if (noEligibleFilms)
			return;

		// If the forward button is pressed, move one film ahead in the film vector.
		// Then, do the same search as before until you find an eligible film
		// (it is guaranteed to exist, since otherwise the above check for noEligibleFilms
		// would have have ended the running of update() )
		if (forwardButton->isPressed()) {

			// increment the current film index by one and check whether it has become negative,
			// which causes problems with the modulo operation, so make sure it's positive
			currentFilmIndex++;
			while (currentFilmIndex < 0)
				currentFilmIndex += films->size();
			currentFilm = (*films)[currentFilmIndex % films->size()];

			nextEligibleFilm(1);
		}

		// Same as before, but for backward button
		if (backwardButton->isPressed()) {

			currentFilmIndex--;
			while (currentFilmIndex < 0)
				currentFilmIndex += films->size();
			currentFilm = (*films)[currentFilmIndex % films->size()];

			nextEligibleFilm(-1);
		}
	}
	// make updateActive false again, so that all the above code doesn't run 
	// until it has to change which films are to be displayed
	updateActive = false;
}

void Browser::draw() 
{	
	graphics::setFont(std::string(ASSET_PATH) + "ralewayRegular.ttf");

	// Check if the currently active filters don't allow any films to be displayed, 
	// and if so, display a warning message to the user instead and display only the filters
	if (noEligibleFilms) {
		graphics::drawText(240, 250, 20, "No film satisfies the chosen filters. Please clear some or all filters.", br);
		for (Filter* f : *filters)
			dynamic_cast<Widget*>(f)->draw();

		clearFiltersButton->draw();
	}
	
	// but if there is at least one eligible current film, then display it
	else {

		br.outline_opacity = 0.0f;

		// Display the film title and release year in parentheses
		// If the title is very long, display the film in two lines
		// by looking for "%%" and splitting the title into two strings,
		// one for each displayed line
		if (currentFilm->title.find("%%") == std::string::npos)
			graphics::drawText(450, 70, 30, currentFilm->title + " (" + std::to_string(currentFilm->year) + ")", br);
		else {
			std::string firstLine = currentFilm->title.substr(0, currentFilm->title.find("%%"));
			std::string secondLine = currentFilm->title.substr(currentFilm->title.find("%%") + 3, currentFilm->title.size() - 1);
			graphics::drawText(450, 55, 30, firstLine, br);
			graphics::drawText(450, 90, 30, secondLine + " (" + std::to_string(currentFilm->year) + ")", br);
		}

		// Display film genres, each genre next to the previous 
		std::string genreString = allGenres.at(currentFilm->genres[0]);
		for (int i = 1; i < currentFilm->genres.size(); ++i)
			genreString += ",  " + allGenres.at(currentFilm->genres[i]);
		graphics::drawText(450, 125, 18, genreString, br);

		// Display film director
		graphics::drawText(450, 160, 18, "Directed by: " + currentFilm->director, br);

		// Display film protagonists
		std::string protagonistString = currentFilm->protagonists[0];
		std::string secondLineProtagonistString = "";

		// Fill the protagonist string with the protagonists of the current film, 
		// until the protagonists are all in the string or the size of the string 
		// becomes too large, in which case start filling the secondary protagonist string
		for (int i = 1; i < currentFilm->protagonists.size(); ++i) {
			if (protagonistString.size() < 40)
				protagonistString += ",  " + currentFilm->protagonists[i];
			else {
				if (secondLineProtagonistString == "") {
					protagonistString += ",";
					secondLineProtagonistString += currentFilm->protagonists[i];
				}
				else
					secondLineProtagonistString += ",  " + currentFilm->protagonists[i];
			}
		}
		// Display protagonists
		graphics::drawText(450, 190, 18, "Starring: " + protagonistString, br);
		graphics::drawText(516, 220, 18, secondLineProtagonistString, br);

		// Display film poster
		br.texture = std::string(ASSET_PATH) + currentFilm->posterFile;
		graphics::drawRect(250, 190, 265.5, 350, br);

		// Draw all widgets
		for (Widget* w : *widgets)
			w->draw();
	}	
}

// Search through every film, starting with the currently displayed film,
// and for each film, go through every active filter.
// If a filter is activated and the current film does not pass through it,
// go to the next film in the film vector by moving the current film index 
// by the specified increment and check if that one passes all the filters.
// Continue until a film passes all filters or you go through all films.
void Browser::nextEligibleFilm(int increment) {
	size_t filmCount = 0;
	size_t filtersPassed;
	bool filmPasses = false;
	while (filmCount < films->size() && !filmPasses) {
		filtersPassed = 0;
		for (Filter* filter : *filters) {
			if (!filter->isActivated() || (filter->isActivated() && filter->filmEligible())) {
				filtersPassed++;
				continue;
			}
			else { 
				currentFilmIndex += increment;
				while (currentFilmIndex < 0)
					currentFilmIndex += films->size();
				currentFilm = (*films)[currentFilmIndex % films->size()];

				filmCount++;
				break;
			}
		}
		if (filtersPassed == filters->size())
			filmPasses = true;
	}
	// If no film passes all filters, activate noEligibleFilms
	// and stop running update ()
	if (filmCount == films->size())
		noEligibleFilms = true;
	else
		noEligibleFilms = false;
}

// Initialize widgets, filters and clear button
void Browser::init() 
{	
	widgets = new std::vector<Widget*>;
	filters = new std::vector<Filter*>;

	films = loadFilms();
	currentFilm = (*films)[currentFilmIndex];

	forwardButton = new browsingButton(this, graphics::SCANCODE_RIGHT, "browsingButton.png", "next film", 0.0f, 800, 275, 40);
	widgets->push_back(forwardButton);

	backwardButton = new browsingButton(this, graphics::SCANCODE_LEFT, "browsingButton.png", "previous film", 180.0f, 500, 275, 40);
	widgets->push_back(backwardButton);

	actionFilteringButton = new filteringButton(this, 530, 380, 60, 20, "action");
	widgets->push_back(actionFilteringButton);
	filters->push_back(actionFilteringButton);

	adventureFilteringButton = new filteringButton(this, 620, 380, 92, 20, "adventure");
	widgets->push_back(adventureFilteringButton);
	filters->push_back(adventureFilteringButton);	

	animationFilteringButton = new filteringButton(this, 722, 380, 86, 20, "animation");
	widgets->push_back(animationFilteringButton);
	filters->push_back(animationFilteringButton);

	comedyFilteringButton = new filteringButton(this, 530, 410, 77, 20, "comedy");
	widgets->push_back(comedyFilteringButton);	
	filters->push_back(comedyFilteringButton);

	crimeFilteringButton = new filteringButton(this, 610, 410, 55, 20, "crime");
	widgets->push_back(crimeFilteringButton);
	filters->push_back(crimeFilteringButton);

	dramaFilteringButton = new filteringButton(this, 682, 410, 62, 20, "drama");
	widgets->push_back(dramaFilteringButton);
	filters->push_back(dramaFilteringButton);

	familyFilteringButton = new filteringButton(this, 756, 410, 60, 20, "family");
	widgets->push_back(familyFilteringButton);
	filters->push_back(familyFilteringButton);

	fantasyFilteringButton = new filteringButton(this, 530, 440, 72, 20, "fantasy");
	widgets->push_back(fantasyFilteringButton);
	filters->push_back(fantasyFilteringButton);

	film_noirFilteringButton = new filteringButton(this, 618, 440, 75, 20, "film-noir");
	widgets->push_back(film_noirFilteringButton);
	filters->push_back(film_noirFilteringButton);

	mysteryFilteringButton = new filteringButton(this, 708, 440, 78, 20, "mystery");
	widgets->push_back(mysteryFilteringButton);
	filters->push_back(mysteryFilteringButton);

	romanceFilteringButton = new filteringButton(this, 530, 470, 80, 20, "romance");
	widgets->push_back(romanceFilteringButton);
	filters->push_back(romanceFilteringButton);

	sci_fiFilteringButton = new filteringButton(this, 610, 470, 50, 20, "sci-fi");
	widgets->push_back(sci_fiFilteringButton);
	filters->push_back(sci_fiFilteringButton);

	// Compute the earliest and latest release years of the films
	// to pass into the slider
	short yearLo = 2200, yearHi = 1800;
	for (const film* f : *films) {
		if (f->year < yearLo)
			yearLo = f->year;
		else if (f->year > yearHi)
			yearHi = f->year;
	}

	yearFilteringSlider = new filteringDoubleSlider(this, 240, 460, 400, 3, yearLo, yearHi);
	widgets->push_back(yearFilteringSlider);
	filters->push_back(yearFilteringSlider);

	clearFiltersButton = new clearAllFiltersButton(this, "clearAllFiltersButton.png", 900, 450, 110, 50);
	widgets->push_back(clearFiltersButton);
}

Browser::~Browser() 
{
	// Delete all films in the films vector, then the films vector itself
	if (films) {
		for (const film* f : *films)
			delete f;
		delete films;
	}

	// Delete all widgets(browsing and filtering buttons, slider and clearFilters button, 
	// then the widgets vector
	if (widgets) {
		for (Widget* w : *widgets)
			delete w;
		delete widgets;
	}

	// Delete the now empty vector filters (all filters also belonged to the widgets vector,
	// so they were deleted before)
	if (filters)
		delete filters;
}
