#pragma once
#include "widget.h"
#include "graphics.h"

class doubleSlider : public Widget
{
public:
	// Constructor 
	doubleSlider(float pos_x, float pos_y, Browser* browser) : Widget(pos_x, pos_y, browser) {}
	// inBounds function for each slider thumb
	virtual bool inBoundsLo(short pos_x, short pos_y) = 0;
	virtual bool inBoundsHi(short pos_x, short pos_y) = 0;
};