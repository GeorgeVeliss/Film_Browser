#pragma once
#include "widget.h"

class Button : public Widget
{
public:
	Button(float pos_x, float pos_y, Browser* browser) : Widget(pos_x, pos_y, browser) {}
	// A button can be pressed or not
	bool pressed = false;	
	bool isPressed() { return pressed; }
};