#include "filmDisplayer.h"
#include "graphics.h"
#include "config.h"
#include <iostream>
#include <stdlib.h>


//void filmDisplayer::update() 
//{
//
//}
//
//void filmDisplayer::draw()
//{
//	graphics::setFont(std::string(ASSET_PATH) + "ralewayRegular.ttf");
//	
//	graphics::Brush br;
//	br.texture = "";
//	br.outline_opacity = 0.0f;
//
//	// Display the film title and production year in parentheses
//	graphics::drawText(450, 75, 30, currentFilm->title + " (" + std::to_string(currentFilm->year) + ")", br);
//
//	// Display film genres, each genre next to the previous 
//	std::string genreString = currentFilm->genres[0];
//	for (int i = 1; i < currentFilm->genres.size(); ++i)
//		genreString += ",  " + currentFilm->genres[i];
//	graphics::drawText(450, 125, 18, genreString, br);
//
//	// Display film director
//	graphics::drawText(450, 160, 18, "Directed by: " + currentFilm->director, br);
//
//
//	// Display film protagonists
//	std::string protagonistString = currentFilm->protagonists[0];
//	for (int i = 1; i < currentFilm->protagonists.size(); ++i)
//		protagonistString += ",  " + currentFilm->protagonists[i];
//
//	if (protagonistString.size() < 50)
//		graphics::drawText(450, 190, 18, "Starring: " + protagonistString, br);
//
//
//
//	/*graphics::drawText(500, 175, 18, "Starring: ", br);
//	for (int i = 0; i < currentFilm->protagonists.size(); i++)
//	{
//		std::string currentGenre = std::to_string(currentFilm->genres[i]);
//		pos_x += currentGenre.size();
//
//		graphics::drawText(500, 200 + 25 * i, 18, currentFilm->protagonists[i], br);
//
//	}*/
//
//	br.texture = std::string(ASSET_PATH) + currentFilm->posterFile;
//	graphics::drawRect(250, 175, 265.5, 350, br);
//}
//
//void filmDisplayer::init()
//{
//	
//}
//
//void filmDisplayer::clear() {}
//
//filmDisplayer::filmDisplayer()
//{
//	currentFilm = (*films)[4];
//}
//
//filmDisplayer::~filmDisplayer()
//{
//	films->clear();
//	delete films;
//}