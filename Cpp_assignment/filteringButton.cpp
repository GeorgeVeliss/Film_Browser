#include "filteringButton.h"
#include "graphics.h"
#include "config.h"
#include "browser.h"
#include "film.h"

void filteringButton::update()
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

	// If button is pressed, activateUpdate()
	if (mouse.button_left_pressed && hover) {
		activated = !activated;
		browser->activateUpdate();
	}
}

void filteringButton::draw()
{
	// Set font and orientation
	graphics::setFont(std::string(ASSET_PATH) + "ralewayRegular.ttf");
	graphics::setOrientation(0.0f);

	// Display the genre of the filter in white
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 1.0f;
	br.fill_color[2] = 1.0f;
	br.gradient = false;	

	graphics::drawText(pos_x - (width/2) + 5, pos_y + (height/2) - 5, 18, genreFilter, br);
	
	// set opacity and outline width for button
	br.outline_opacity = 1.0f;
	br.outline_width = 1.6f;
	float glow;

	// Flashing red outline and intense filling
	if (activated) {
		glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 100);
		
		br.fill_color[0] = 0.36f;
		br.fill_color[1] = 0.92f;
		br.fill_color[2] = 0.99f;

		br.outline_color[0] = 1.0f;
		br.outline_color[1] = 0.5f + glow * 0.5f;
		br.outline_color[2] = 0.0f;
	}
	// Static white outline and mild filling
	else {
		br.fill_color[0] = 0.26f;
		br.fill_color[1] = 0.7f;
		br.fill_color[2] = 0.9f;

		br.outline_color[0] = 1.0f;
		br.outline_color[1] = 1.0f;
		br.outline_color[2] = 1.0f;
	}
	// Display button
	graphics::drawRect(pos_x, pos_y, width, height, br);

	// Display informative text above filters in lighter font
	if (hover)
	{
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 1.0f;

		graphics::setFont(std::string(ASSET_PATH) + "ralewayLight.ttf");
		graphics::drawText(580, 350, 15, "filter by genre", br);
	}
	
}

filteringButton::filteringButton(Browser* browser, float pos_x, float pos_y, short width, short height, std::string genreFilter) :
	Button(pos_x, pos_y, browser), width(width), height(height), genreFilter(genreFilter)
	{		
	}

bool filteringButton::filmEligible() {
	for (genre genre : browser->getCurrentFilm()->genres) {
		if (genreFilter == allGenres.at(genre))
			return true;
	}
	return false;
}

void filteringButton::clearFilter() {
	activated = false;
}

bool filteringButton::inBounds(short mouse_pos_x, short mouse_pos_y)
{
	bool in_bounds_x = mouse_pos_x >= pos_x - (width / 2) && mouse_pos_x <= pos_x + (width / 2);
	bool in_bounds_y = mouse_pos_y >= pos_y - (height / 2) && mouse_pos_y <= pos_y + (height / 2);
	return in_bounds_x && in_bounds_y;
}