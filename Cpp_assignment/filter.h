#pragma once
#include "widget.h"

class Filter
{
public:
	// A filter can be activated or not
	bool activated = false;
	bool isActivated() { return activated; }
	// Deactivates filter
	virtual void clearFilter() = 0;
	// Checks whether the current film of the browser is eligible under the filter
	virtual bool filmEligible() = 0;
};
