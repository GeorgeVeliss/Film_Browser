#include "browsingButton.h"
#include "graphics.h"
#include "config.h"
#include "browser.h"

void browsingButton::update()
{
	// If the keyboard key that corresponds to this button isn't pressed,
	// deactivate keyboardPressed
	if (!graphics::getKeyState(scancode))
		keyboardPressed = false;

	// Get current mouse position
	graphics::getMouseState(mouse);
	int cur_pos_x = (int)graphics::windowToCanvasX((float)mouse.cur_pos_x);
	int cur_pos_y = (int)graphics::windowToCanvasY((float)mouse.cur_pos_y);

	// If mouse is within the bounds of the button, activate hover
	if (inBounds(cur_pos_x, cur_pos_y))
		hover = true;
	else
		hover = false;

	// If button is pressed, activateUpdate() so that the displayed film changes in browser
	if (mouse.button_left_pressed && hover) {
		pressed = true;
		browser->activateUpdate();
	}
	else
		pressed = false;

	// If the keyboard key that corresponds to this button is pressed, 
	// and it wasn't pressed before, make keyboardPressed = true and activateUpdate()
	if (graphics::getKeyState(scancode) && !keyboardPressed) {
		pressed = true;
		keyboardPressed = true;
		browser->activateUpdate();
	}		
}

void browsingButton::draw()
{	
	// Display button in chosen orientation
	graphics::setOrientation(orientation);
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, size, size, br);

	// Display informative text below button
	if (hover) {
		graphics::setFont(std::string(ASSET_PATH) + "ralewayLight.ttf");
		graphics::setOrientation(0.0f);
		graphics::drawText(pos_x - (size / 2) - userPrompt.size() * 1.2, pos_y + 40, 15, userPrompt, br);
	}
}

browsingButton::browsingButton(Browser* browser, graphics::scancode_t scancode, std::string imageFile, 
						std::string userPrompt, float orientation, float pos_x, float pos_y, short size) :
	Button(pos_x, pos_y, browser), scancode(scancode), imageFile(imageFile), userPrompt(userPrompt), orientation(orientation), size(size)
	{
		br.texture = std::string(ASSET_PATH) + imageFile;
	}

// Takes in the current_mouse position and return whether it is on the widget surface
bool browsingButton::inBounds(short mouse_pos_x, short mouse_pos_y)
{
	bool in_bounds_x = mouse_pos_x >= pos_x - (size/2) && mouse_pos_x <= pos_x + (size/2);
	bool in_bounds_y = mouse_pos_y >= pos_y - (size/2) && mouse_pos_y <= pos_y + (size/2);
	return in_bounds_x && in_bounds_y;
}