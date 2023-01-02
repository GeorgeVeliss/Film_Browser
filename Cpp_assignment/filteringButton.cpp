#include "filteringButton.h"
#include "graphics.h"
#include "config.h"
#include "browser.h"
#include <iostream>

void filteringButton::update()
{
	graphics::getMouseState(mouse);

	/*if (in_bounds(graphics::windowToCanvasX(mouse.cur_pos_x), graphics::windowToCanvasY(mouse.cur_pos_y)))
		std::cout << "here";*/

	int cur_pos_x = (int)graphics::windowToCanvasX((float)mouse.cur_pos_x);
	int cur_pos_y = (int)graphics::windowToCanvasY((float)mouse.cur_pos_y);

	if (mouse.button_left_pressed && in_bounds(cur_pos_x, cur_pos_y))
		activated = !activated;

}

void filteringButton::draw()
{
	graphics::setFont(std::string(ASSET_PATH) + "ralewayRegular.ttf");

	graphics::resetPose();

	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.gradient = false;	

	graphics::drawText(pos_x - (width/2) + 5, pos_y + (height/2) - 5, 18, genreFilter, br);

	br.texture = "";	
	br.outline_opacity = 1.0f;
	br.outline_width = 1.6f;

	float glow;

	if (activated) {
		glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 100);
		
		br.fill_color[0] = 0.36f;
		br.fill_color[1] = 0.92f;
		br.fill_color[2] = 0.99f;

		br.outline_color[0] = 1.0f;
		br.outline_color[1] = 0.5f + glow * 0.5f;
		br.outline_color[2] = 0.0f;
	}
	else {
		br.fill_color[0] = 0.26f;
		br.fill_color[1] = 0.7f;
		br.fill_color[2] = 0.9f;

		br.outline_color[0] = 1.0f;
		br.outline_color[1] = 1.0f;
		br.outline_color[2] = 1.0f;
	}

	graphics::drawRect(pos_x, pos_y, width, height, br);
	
}

filteringButton::filteringButton(float pos_x, float pos_y, short width, short height, std::string genreFilter) :
	Button(pos_x, pos_y), width(width), height(height), genreFilter(genreFilter)
	{
	}

std::string filteringButton::getFilter() {
	return genreFilter;
}

void filteringButton::clearFilter() {
	activated = false;
}

bool filteringButton::in_bounds(short mouse_pos_x, short mouse_pos_y)
{
	bool in_bounds_x = mouse_pos_x >= pos_x - (width / 2) && mouse_pos_x <= pos_x + (width / 2);
	bool in_bounds_y = mouse_pos_y >= pos_y - (height / 2) && mouse_pos_y <= pos_x + (height / 2);
	return in_bounds_x && in_bounds_y;
}