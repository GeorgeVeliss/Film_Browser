#pragma once
#include "widget.h"
#include <string>

class searchBar : public Widget
{
public:
	float pos_x;
	float pos_y;
	float size;
	std::string userQuery;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual void init() = 0;
	virtual void clear() = 0;
};