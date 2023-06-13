#pragma once 
#include "GrlibEngine/Canvas.h"

// Abstract class for drawing raycasted images
class RaycastDraw {
public:
	// Draw image on display
	virtual void draw() = 0;

	// Create raycast drawer for canvas	`canvas`
	RaycastDraw(Canvas* canvas);

protected:

	// Data image source
	Canvas* _canvas;
};