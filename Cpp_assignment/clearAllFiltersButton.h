#pragma once
#include "button.h"

class clearAllFiltersButton : public Button
{
	graphics::Brush br;
	graphics::MouseState mouse;
	std::string imageFile;
	short width, height;
	bool inBounds(short pos_x, short pos_y);
public:
	clearAllFiltersButton(Browser* browser, std::string imageFile, float pos_x, float pos_y, short width, short height);
	void update();
	void draw();
};
