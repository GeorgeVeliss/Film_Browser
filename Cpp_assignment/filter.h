#pragma once

#include "widget.h"

class Filter
{
public:
	virtual std::string getFilter() = 0;
	bool activated = false;
	bool isActivated() { return activated; }
	virtual void clearFilter() = 0;
};
