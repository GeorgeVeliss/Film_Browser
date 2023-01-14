#pragma once
#include "button.h"
#include "filter.h"

class filteringButton : public Button, public Filter
{
	graphics::Brush br;
	graphics::MouseState mouse;
	short width, height;
	std::string genreFilter;
	bool inBounds(short pos_x, short pos_y);
public:
	filteringButton(Browser* browser, float pos_x, float pos_y, short width, short height, std::string genreFilter);
	void clearFilter();
	bool filmEligible();
	void update();
	void draw();	
};
