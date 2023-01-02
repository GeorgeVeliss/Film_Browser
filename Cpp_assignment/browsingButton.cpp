#include "browsingButton.h"
#include "graphics.h"
#include "config.h"
#include "browser.h"
#include <iostream>

void browsingButton::update()
{
	if (keyboardPressed)
		pressed = false;

	if (!graphics::getKeyState(scancode))
		keyboardPressed = false;

	graphics::getMouseState(mouse);
	
	/*if (in_bounds(graphics::windowToCanvasX(mouse.cur_pos_x), graphics::windowToCanvasY(mouse.cur_pos_y)))
		std::cout << "here";*/

	int cur_pos_x = (int)graphics::windowToCanvasX((float)mouse.cur_pos_x);
	int cur_pos_y = (int)graphics::windowToCanvasY((float)mouse.cur_pos_y);

	if (in_bounds(cur_pos_x, cur_pos_y))
		hover = true;
	else
		hover = false;

	if (mouse.button_left_pressed && in_bounds(cur_pos_x, cur_pos_y)) {
		pressed = true;
		browser->updateNeeded = true;
		/*browser.currentFilmIndex++;
		browser.currentFilm = (*browser.films)[browser.currentFilmIndex % browser.films->size()];*/
	}
	else
		pressed = false;

	if (graphics::getKeyState(scancode) && !keyboardPressed) {
		pressed = true;
		keyboardPressed = true;
		browser->updateNeeded = true;
	}		
}

void browsingButton::draw()
{	
	graphics::setOrientation(orientation);
	graphics::drawRect(pos_x, pos_y, size, size, br);

	if (hover) {
		graphics::setFont(std::string(ASSET_PATH) + "ralewayLight.ttf");
		graphics::setOrientation(0.0f);
		graphics::drawText(pos_x - (size / 2) - userPrompt.size() * 1.2, pos_y + 40, 15, userPrompt, br);
	}
}

browsingButton::browsingButton(Browser* browser, graphics::scancode_t scancode, std::string imageFile, std::string userPrompt, float orientation, float pos_x, float pos_y, short size) :
	Button(pos_x, pos_y, browser), scancode(scancode), imageFile(imageFile), userPrompt(userPrompt), orientation(orientation), size(size)
	{
		keyboardPressed = false;
		hover = false;
		br.texture = std::string(ASSET_PATH) + imageFile;
	}

bool browsingButton::in_bounds(short mouse_pos_x, short mouse_pos_y)
{
	bool in_bounds_x = mouse_pos_x >= pos_x - (size/2) && mouse_pos_x <= pos_x + (size/2);
	bool in_bounds_y = mouse_pos_y >= pos_y - (size/2) && mouse_pos_y <= pos_y + (size/2);
	return in_bounds_x && in_bounds_y;
}