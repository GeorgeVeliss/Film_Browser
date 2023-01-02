#pragma once
#include "graphics.h"

class Widget
{
public:
	class Browser* browser;
	float pos_x, pos_y;
	virtual void update() = 0;
	virtual void draw() = 0;
	//virtual void init() = 0;
	Widget(float pos_x, float pos_y, Browser* browser) : pos_x(pos_x), pos_y(pos_y), browser(browser) {}
};