#include "browser.h"
#include "graphics.h"
//#include "filmDisplayer.h"
#include "loadFilms.hpp"
#include "config.h"
#include "browsingButton.h"
#include "filteringButton.h"
#include <iostream>

void Browser::update() 
{
	for (Widget* w : *widgets)
		w->update();

	if (updateNeeded) {

		size_t filmCount = 0;
		size_t filtersPassed;
		bool filmPasses = false;
		while (filmCount < films->size() && !filmPasses) {
			filtersPassed = 0;
			for (auto filter : *filters) {
				if (!filter->isActivated() || (filter->isActivated() && filmEligible(filter->getFilter(), currentFilm))) {
					filtersPassed++;
					continue;
				}
				else if (filter->isActivated() && !filmEligible(filter->getFilter(), currentFilm)) {
					currentFilmIndex++;
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

		if (filmCount == films->size())
			noEligibleFilms = true;
		else
			noEligibleFilms = false;


		/*		if (filter->isActivated()) {
					while (!filmEligible(filter->getFilter(), currentFilm) && filmCount < films->size()) {
						currentFilmIndex++;
						while (currentFilmIndex < 0)
							currentFilmIndex += films->size();
						currentFilm = (*films)[currentFilmIndex % films->size()];
						filmCount++;
					}
				if (filmCount == films->size())
					noEligibleFilms = true;
				else
					noEligibleFilms = false;
			}
		}*/

		if (noEligibleFilms)
			return;

		if (forwardButton->isPressed()) {

			currentFilmIndex++;
			while (currentFilmIndex < 0)
				currentFilmIndex += films->size();
			currentFilm = (*films)[currentFilmIndex % films->size()];

			filmCount = 0;
			size_t filtersPassed;
			filmPasses = false;
			while (filmCount < films->size() && !filmPasses) {
				filtersPassed = 0;
				for (auto filter : *filters) {
					if (!filter->isActivated() || (filter->isActivated() && filmEligible(filter->getFilter(), currentFilm))) {
						filtersPassed++;
						continue;
					}
					else {
						currentFilmIndex++;
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

			/*for (auto filter : *filters) {
				filmCount = 0;
				if (filter->isActivated()) {
					while (!filmEligible(filter->getFilter(), currentFilm) && filmCount < films->size()) {
						currentFilmIndex++;
						while (currentFilmIndex < 0)
							currentFilmIndex += films->size();
						currentFilm = (*films)[currentFilmIndex % films->size()];
						filmCount++;
					}
					if (filmCount == films->size())
						noEligibleFilms = true;
				}
			}*/
		}


		if (backwardButton->isPressed()) {

			currentFilmIndex--;
			while (currentFilmIndex < 0)
				currentFilmIndex += films->size();
			currentFilm = (*films)[currentFilmIndex % films->size()];

			filmCount = 0;
			size_t filtersPassed;
			filmPasses = false;
			while (filmCount < films->size() && !filmPasses) {
				filtersPassed = 0;
				for (auto filter : *filters) {
					if (!filter->isActivated() || (filter->isActivated() && filmEligible(filter->getFilter(), currentFilm))) {
						filtersPassed++;
						continue;
					}
					else {
						currentFilmIndex--;
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

			/*for (auto filter : *filters) {
				filmCount = 0;
				if (filter->isActivated()) {
					while (!filmEligible(filter->getFilter(), currentFilm) && filmCount < films->size()) {
						currentFilmIndex--;
						while (currentFilmIndex < 0)
							currentFilmIndex += films->size();
						currentFilm = (*films)[currentFilmIndex % films->size()];
						filmCount++;
					}
					if (filmCount == films->size())
						noEligibleFilms = true;
				}
			}*/
		}
	}

	updateNeeded = false;

	/*for (auto filter : *genreFilters) {
		if (filter->get_state()) {
			short ind = 0;
			filmEligible = false;
			while (!filmEligible && ind < films->size()) {
				for (auto genre : currentFilm->genres) {
					if (filter->getFilter() == genre) {
						filmEligible = true;
						break;
					}
				}
				if (filmEligible == true)
					break;
				currentFilmIndex++;
				currentFilm = (*films)[currentFilmIndex % films->size()];
				ind++;
			}
			if (ind == films->size())
				currentFilm = nullptr;
		}			
	}*/
}

void Browser::draw() 
{	
	graphics::setFont(std::string(ASSET_PATH) + "ralewayRegular.ttf");

	// Check if the currently active filters don't allow any films to be displayed, 
	// and if so, display a warning message to the user instead
	if (noEligibleFilms) {
		graphics::drawText(150, 250, 20, "No film exists that satisfies the given requirements. Please clear some or all filters.", br);
	}
	
	else {

		br.outline_opacity = 0.0f;

		// Display the film title and production year in parentheses
		//
		if (currentFilm->title.find("%%") == std::string::npos)
			graphics::drawText(450, 70, 30, currentFilm->title + " (" + std::to_string(currentFilm->year) + ")", br);
		else {
			std::string firstLine = currentFilm->title.substr(0, currentFilm->title.find("%%"));
			std::string secondLine = currentFilm->title.substr(currentFilm->title.find("%%") + 3, currentFilm->title.size() - 1);
			graphics::drawText(450, 55, 30, firstLine, br);
			graphics::drawText(450, 90, 30, secondLine + " (" + std::to_string(currentFilm->year) + ")", br);
		}

		// Display film genres, each genre next to the previous 
		/*std::string genreString = currentFilm->genres[0];
		for (int i = 1; i < currentFilm->genres.size(); ++i)
			genreString += ",  " + currentFilm->genres[i];
		graphics::drawText(450, 125, 18, genreString, br);*/

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
		// becomes too large.
		// Then start filling the secondary protagonist string
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

		return;
	}

	for (auto f : *filters)
		dynamic_cast<Widget*>(f) -> draw();
}

void Browser::init() 
{
	widgets = new std::vector<Widget*>;
	filters = new std::vector<Filter*>;

	films = loadFilms();
	currentFilm = (*films)[currentFilmIndex];

	/*for (auto f : *films)
		std::cout << f->genres;*/

	//br.texture = "";
	//br.outline_opacity = 0.0f;

	forwardButton = new browsingButton(this, graphics::SCANCODE_RIGHT, "browsingButton.png", "next film", 0.0f, 800, 275, 40);
	widgets->push_back(forwardButton);

	backwardButton = new browsingButton(this, graphics::SCANCODE_LEFT, "browsingButton.png", "previous film", 180.0f, 500, 275, 40);
	widgets->push_back(backwardButton);

	actionFilteringButton = new filteringButton(this, 500, 400, 60, 20, "action");
	widgets->push_back(actionFilteringButton);
	filters->push_back(actionFilteringButton);

	adventureFilteringButton = new filteringButton(this, 590, 400, 92, 20, "adventure");
	widgets->push_back(adventureFilteringButton);
	filters->push_back(adventureFilteringButton);	

	animationFilteringButton = new filteringButton(this, 692, 400, 86, 20, "animation");
	widgets->push_back(animationFilteringButton);
	filters->push_back(animationFilteringButton);

	comedyFilteringButton = new filteringButton(this, 500, 430, 77, 20, "comedy");
	widgets->push_back(comedyFilteringButton);	
	filters->push_back(comedyFilteringButton);

	crimeFilteringButton = new filteringButton(this, 580, 430, 55, 20, "crime");
	widgets->push_back(crimeFilteringButton);
	filters->push_back(crimeFilteringButton);

	dramaFilteringButton = new filteringButton(this, 652, 430, 62, 20, "drama");
	widgets->push_back(dramaFilteringButton);
	filters->push_back(dramaFilteringButton);

	familyFilteringButton = new filteringButton(this, 726, 430, 60, 20, "family");
	widgets->push_back(familyFilteringButton);
	filters->push_back(familyFilteringButton);

	fantasyFilteringButton = new filteringButton(this, 500, 460, 72, 20, "fantasy");
	widgets->push_back(fantasyFilteringButton);
	filters->push_back(fantasyFilteringButton);

	film_noirFilteringButton = new filteringButton(this, 588, 460, 75, 20, "film-noir");
	widgets->push_back(film_noirFilteringButton);
	filters->push_back(film_noirFilteringButton);

	mysteryFilteringButton = new filteringButton(this, 678, 460, 78, 20, "mystery");
	widgets->push_back(mysteryFilteringButton);
	filters->push_back(mysteryFilteringButton);

	fantasyFilteringButton = new filteringButton(this, 500, 460, 72, 20, "fantasy");
	widgets->push_back(fantasyFilteringButton);
	filters->push_back(fantasyFilteringButton);

	romanceFilteringButton = new filteringButton(this, 500, 490, 80, 20, "romance");
	widgets->push_back(romanceFilteringButton);
	filters->push_back(romanceFilteringButton);

	sci_fiFilteringButton = new filteringButton(this, 580, 490, 50, 20, "sci-fi");
	widgets->push_back(sci_fiFilteringButton);
	filters->push_back(sci_fiFilteringButton);
	
}

bool Browser::filmEligible(std::string filter, film* film)
{
	return genreEligible(filter, film); //&& correctYear(film*);
}

bool Browser::genreEligible(std::string filter, film* film)
{
	for (genre genre : film->genres)
		if (filter == allGenres.at(genre))
			return true;
	return false;
}

//Browser::Browser() 
//{
//	widgets = new std::vector<Widget*>;
//	films = loadFilms();
//}

Browser::~Browser() 
{
	if (films) {
		films->clear();
		delete films;
	}

	if (widgets) {
		widgets->clear();
		delete widgets;
	}

	if (filters) {
		filters->clear();
		delete filters;
	}

		
}

void Browser::clearFilters()
{
}

