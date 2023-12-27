#pragma once
#include "doubleSlider.h"
#include "filter.h"

class filteringDoubleSlider : public doubleSlider, public Filter
{
	graphics::Brush br;
	graphics::MouseState mouse;
	// Slider dimensions
	short width, height;
	// Low and high ends of slider
	short lo_end, hi_end;
	// Position of slider thumbs
	short lo_pos, hi_pos;	
	// Low and high of range
	short rangeLo, rangeHi;
	bool draggingLo = false, draggingHi = false;
	bool hoverLo = false, hoverHi = false;
	// Takes in the current_mouse position and return whether it is on the widget surface
	bool inBounds(short pos_x, short pos_y);
	// Same as above but for lower thumb surface
	bool inBoundsLo(short pos_x, short pos_y);
	// Same as above but for higher thumb surface
	bool inBoundsHi(short pos_x, short pos_y);
	// Computes and returns the current low thumb value within the range, based on canvas positions
	short getLoValue();
	// Same as above but for high thumb value
	short getHiValue();
public:
	// Constructor
	filteringDoubleSlider(Browser* browser, float pos_x, float pos_y, 
		short width, short height, short rangeLo, short rangeHi);

	// Resets thumbs to the ends of the slider
	void clearFilter();
	bool filmEligible();
	void update();
	void draw();
};
