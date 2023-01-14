#pragma once
#include "graphics.h"

// Base class of every graphical element
class Widget
{
public:
	// Pointer to the browser that instantiated this widget 
	// used to call activateUpdate() and getCurrentFilm()
	class Browser* browser;

	// Widget position
	float pos_x, pos_y;

	// Constructor called by derived classes
	Widget(float pos_x, float pos_y, Browser* browser) : 
		pos_x(pos_x), pos_y(pos_y), browser(browser) {}

	// Takes in the current_mouse position and return whether it is on the widget surface
	virtual bool inBounds(short mouse_pos_x, short mouse_pos_y) = 0;
	bool hover = false;

	virtual void update() = 0;
	virtual void draw() = 0;
};