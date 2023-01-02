#pragma once
#include "button.h"
#include "filter.h"

class filteringButton : public Button, public Filter
{
	graphics::Brush br;
	graphics::MouseState mouse;
	short width, height;
	std::string genreFilter;
	bool hover;
	bool in_bounds(short pos_x, short pos_y);
public:
	filteringButton(Browser* browser, float pos_x, float pos_y, short width, short height, std::string genreFilter);
	void update();
	void draw();
	std::string getFilter();
	void clearFilter();
};
