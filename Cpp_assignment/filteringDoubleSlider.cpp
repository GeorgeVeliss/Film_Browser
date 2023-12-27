#include "filteringDoubleSlider.h"
#include "config.h"
#include "browser.h"
#include "film.h"

void filteringDoubleSlider::update()
{
	// Get mouse position
	graphics::getMouseState(mouse);
	int cur_pos_x = (int)graphics::windowToCanvasX((float)mouse.cur_pos_x);
	int cur_pos_y = (int)graphics::windowToCanvasY((float)mouse.cur_pos_y);

	// If it presses on the low thumb, activate draggingLo and deactivate draggingHi
	// to avoid moving both thumbs simultaneously
	if (mouse.button_left_pressed && inBoundsLo(cur_pos_x, cur_pos_y)) {
		draggingLo = true;
		draggingHi = false;
	}

	// If the mouse is still dragging and its x position is between the low end of the slider
	// and the position of the hi thumb (minus a small increment, so that they don't collide),
	// make the current x position of the lower thumb equal to mouse x position
	if (mouse.dragging && draggingLo) {		
		if (cur_pos_x >= lo_end && cur_pos_x <= hi_pos-6)
			lo_pos = cur_pos_x;		
	}

	// If the mouse stops dragging while the current low thumb x position is not the 
	// low end of the slider, activate slider and activateUpdate() in browser
	// deactivate draggingLo
	if (draggingLo && mouse.button_left_released) {
		if (lo_pos != lo_end) {
			activated = true;
			browser->activateUpdate();
		}
		else
			activated = false;
				
		draggingLo = false;
	}

	// Same as above but for high thumb
	if (mouse.button_left_pressed && inBoundsHi(cur_pos_x, cur_pos_y)) {
		draggingHi = true;
		draggingLo = false;
	}

	if (mouse.dragging && draggingHi) {
		if (cur_pos_x >= lo_pos+6 && cur_pos_x <= hi_end)
			hi_pos = cur_pos_x;		
	}

	if (draggingHi && mouse.button_left_released) {
		if (hi_pos != hi_end)
			activated = true;
		else
			activated = false;

		browser->activateUpdate();
		draggingHi = false;
	}

	// If mouse is within the bounds of low thumb, activate hoverLo
	if (inBoundsLo(cur_pos_x, cur_pos_y))
		hoverLo = true;
	else
		hoverLo = false;

	// If mouse is within the bounds of high thumb, activate hoverHi
	if (inBoundsHi(cur_pos_x, cur_pos_y))
		hoverHi = true;
	else
		hoverHi = false;

	// If mouse is within the bounds of the slider, activate hover
	if (inBounds(cur_pos_x, cur_pos_y))
		hover = true;
	else
		hover = false;
}

void filteringDoubleSlider::draw()
{
	graphics::setFont(std::string(ASSET_PATH) + "ralewayLight.ttf");
	graphics::setOrientation(0.0f);

	// Display the white slider line
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.gradient = false;

	graphics::drawRect(pos_x, pos_y, width, height, br);

	// Display the two light blue slider thumbs
	br.fill_color[0] = 0.26f;
	br.fill_color[1] = 0.7f;
	br.fill_color[2] = 0.9f;
	br.outline_opacity = 0.0f;

	graphics::drawDisk(lo_pos, pos_y, 8, br);
	graphics::drawDisk(hi_pos, pos_y, 8, br);

	// Display informative text about filter function, current low and high values of thumbs
	// in a white and lighter font, above and below slider
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;

	if (hover) 
		graphics::drawText(170, 420, 15, "filter by release year", br);

	if (hoverLo || draggingLo) {
		graphics::drawText(50, 440, 15, "from: ", br);
		graphics::drawText(lo_pos - 28, 490, 14, std::to_string(getLoValue()), br);
	}

	if (hoverHi || draggingHi) {
		graphics::drawText(400, 440, 15, "up to: ", br);
		graphics::drawText(hi_pos - 4, 490, 14, std::to_string(getHiValue()), br);
	}
}

filteringDoubleSlider::filteringDoubleSlider(Browser* browser, float pos_x, float pos_y, short width, short height, short rangeLo, short rangeHi) :
	doubleSlider(pos_x, pos_y, browser), width(width), height(height), rangeLo(rangeLo), rangeHi(rangeHi)
{
	// compute the low and high ends of the slider using specified slider position and width
	lo_end = pos_x - (width / 2);
	hi_end = pos_x + (width / 2);
	// initialize the thumb positions to each end of the slider
	lo_pos = lo_end;
	hi_pos = hi_end;
}

// Computes and returns the current low thumb value within the range, based on canvas positions
short filteringDoubleSlider::getLoValue()
{
	// Compute the precentage of the slider covered by the section 
	// from the beginning of the slider up to the low thumb position
	float precentageLo = (lo_pos - (pos_x - (width / 2))) / width;
	// Compute the proportional value within the range, linearly
	short currentValueLo = rangeLo + (rangeHi - rangeLo) * precentageLo;
	return currentValueLo;
}
// Computes and returns the current high thumb value within the range, based on canvas positions
short filteringDoubleSlider::getHiValue()
{
	// Compute the precentage of the slider covered by the section 
	// from the low thumb position up to the end of the slider
	float precentageHi = (pos_x + (width / 2) - hi_pos) / width;
	// Compute the proportional value within the range, linearly
	short currentValueHi = rangeHi - (rangeHi - rangeLo) * precentageHi;
	return currentValueHi;
}

// Return whether the release year of the current film lies within the bounds of the slider
bool filteringDoubleSlider::filmEligible()
{	
	unsigned short currentYear = browser->getCurrentFilm()->year;
	return (getLoValue() <= currentYear) && (getHiValue() >= currentYear);
}

// Takes in the current_mouse position and return whether it is on the widget surface
bool filteringDoubleSlider::inBounds(short mouse_pos_x, short mouse_pos_y)
{
	bool in_bounds_x = mouse_pos_x >= pos_x - (width / 2) - 8 && mouse_pos_x <= pos_x + (width / 2) + 8;
	bool in_bounds_y = mouse_pos_y >= pos_y - height - 15  && mouse_pos_y <= pos_y + height + 10;
	return in_bounds_x && in_bounds_y;
}

// Same as above but for lower thumb surface
bool filteringDoubleSlider::inBoundsLo(short mouse_pos_x, short mouse_pos_y)
{ 
	bool in_bounds_x = mouse_pos_x >= lo_pos - 8 && mouse_pos_x <= lo_pos + 8;
	bool in_bounds_y = mouse_pos_y >= pos_y - height - 5 && mouse_pos_y <= pos_y + height + 5;
	return in_bounds_x && in_bounds_y;
}

// Same as above but for higher thumb surface
bool filteringDoubleSlider::inBoundsHi(short mouse_pos_x, short mouse_pos_y)
{ 
	bool in_bounds_x = mouse_pos_x >= hi_pos - 8 && mouse_pos_x <= hi_pos + 8;
	bool in_bounds_y = mouse_pos_y >= pos_y - height - 5 && mouse_pos_y <= pos_y + height + 5;
	return in_bounds_x && in_bounds_y;
}

// Resets thumbs to the ends of the slider
void filteringDoubleSlider::clearFilter()
{
	lo_pos = lo_end;
	hi_pos = hi_end;
}
