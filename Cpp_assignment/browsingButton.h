#pragma once

#include "button.h"
#include <string>
#include "graphics.h"

class browsingButton : public Button
{
	//class Browser& browser;
	graphics::Brush br;
	graphics::MouseState mouse;
	std::string imageFile;
	std::string userPrompt;
	short size;
	bool keyboardPressed;
	bool hover;
	float orientation;
	graphics::scancode_t scancode;
	bool in_bounds(short pos_x, short pos_y);
public:
	browsingButton(Browser* browser, graphics::scancode_t scancode, std::string imageFile, std::string userPrompt, float orientation, float pos_x, float pos_y, short size);
	void update();
	void draw();	
};