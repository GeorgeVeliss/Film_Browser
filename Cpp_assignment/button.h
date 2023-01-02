#pragma once
#include "widget.h"
#include "graphics.h"

class Button : public Widget
{
public:
	Button(float pos_x, float pos_y) : Widget(pos_x, pos_y) {}
	bool pressed = false;	
	bool isPressed() { return pressed; }
	virtual bool in_bounds(short pos_x, short pos_y) = 0;
};