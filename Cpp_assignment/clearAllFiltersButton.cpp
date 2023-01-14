#include "clearAllFiltersButton.h"
#include "browser.h"
#include "config.h"

void clearAllFiltersButton::update()
{
	// Get current mouse position
	graphics::getMouseState(mouse);
	int cur_pos_x = (int)graphics::windowToCanvasX((float)mouse.cur_pos_x);
	int cur_pos_y = (int)graphics::windowToCanvasY((float)mouse.cur_pos_y);

	// If mouse is within the bounds of the button, activate hover
	if (inBounds(cur_pos_x, cur_pos_y))
		hover = true;
	else
		hover = false;

	if (mouse.button_left_pressed && hover) {
		pressed = true;
		browser->activateUpdate();
	}
	else
		pressed = false;
}

void clearAllFiltersButton::draw()
{	
	// Display button
	graphics::drawRect(pos_x, pos_y, width, height, br);

	// Display informative text in lighter fint above button
	if (hover) {
		graphics::setFont(std::string(ASSET_PATH) + "ralewayLight.ttf");
		graphics::drawText(pos_x - 45, pos_y - 40, 15, "clear all filters", br);
	}
}

clearAllFiltersButton::clearAllFiltersButton(Browser* browser, std::string imageFile, float pos_x, float pos_y, short width, short height) :
	Button(pos_x, pos_y, browser), imageFile(imageFile), width(width), height(height)
{
	br.texture = std::string(ASSET_PATH) + imageFile;
	br.outline_opacity = 0.0f;
}

bool clearAllFiltersButton::inBounds(short mouse_pos_x, short mouse_pos_y)
{
	bool in_bounds_x = mouse_pos_x >= pos_x - (width / 2) && mouse_pos_x <= pos_x + (width / 2);
	bool in_bounds_y = mouse_pos_y >= pos_y - (height / 2) && mouse_pos_y <= pos_y + (height / 2);
	return in_bounds_x && in_bounds_y;
}