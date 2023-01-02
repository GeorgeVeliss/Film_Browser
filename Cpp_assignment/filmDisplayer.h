#pragma once

#include "widget.h"
#include "loadFilms.hpp"

class filmDisplayer : public Widget
{
	std::vector<film*>* films = loadFilms();
	film* currentFilm;
public:
	void update();
	void draw();
	void init();
	void clear();
	filmDisplayer();
	~filmDisplayer();
};