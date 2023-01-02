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

	short filmCount = 0;

	for (auto filter : *filters) {
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
			else
				noEligibleFilms = false;
		}
	}

	if (noEligibleFilms)
		return;

	if (forwardButton->isPressed()) {

		currentFilmIndex++;
		while (currentFilmIndex < 0)
			currentFilmIndex += films->size();
		currentFilm = (*films)[currentFilmIndex % films->size()];
		
		for (auto filter : *filters) {
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
		}
	}

	if (backwardButton->isPressed()) {
						
		currentFilmIndex--;
		while (currentFilmIndex < 0)
			currentFilmIndex += films->size();
		currentFilm = (*films)[currentFilmIndex % films->size()];

		for (auto filter : *filters) {
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
		}
	}

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

	forwardButton = new browsingButton(graphics::SCANCODE_RIGHT, "browsingButton.png", "next film", 0.0f, 800, 275, 40);
	backwardButton = new browsingButton(graphics::SCANCODE_LEFT, "browsingButton.png", "previous film", 180.0f, 500, 275, 40);

	widgets->push_back(forwardButton);
	widgets->push_back(backwardButton);

	actionfilteringButton = new filteringButton(500, 400, 60, 20, "action");
	adventurefilteringButton = new filteringButton(590, 400, 90, 20, "adventure");
	//animationfilteringButton = new filteringButton(686, 430, 90, 20, "animation");
	comedyfilteringButton = new filteringButton(686, 400, 75, 20, "comedy");

	widgets->push_back(actionfilteringButton);
	widgets->push_back(adventurefilteringButton);
	//widgets->push_back(animationfilteringButton);
	widgets->push_back(comedyfilteringButton);

	filters->push_back(actionfilteringButton);
	filters->push_back(adventurefilteringButton);
	//genreFilters->push_back(animationfilteringButton);
	filters->push_back(comedyfilteringButton);
	
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

