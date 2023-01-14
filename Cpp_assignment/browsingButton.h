#pragma once
#include "button.h"
#include "graphics.h"

class browsingButton : public Button
{
	graphics::Brush br;
	graphics::MouseState mouse;
	std::string imageFile;
	std::string userPrompt;
	short size;
	float orientation;
	bool keyboardPressed = false;
	graphics::scancode_t scancode;
	bool inBounds(short pos_x, short pos_y);
public:
	browsingButton(Browser* browser, graphics::scancode_t scancode, std::string imageFile, 
		std::string userPrompt, float orientation, float pos_x, float pos_y, short size);
	void update();
	void draw();	
};