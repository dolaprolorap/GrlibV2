#pragma once
#include <iostream>

#include "GrlibEngine/DrawSystem/RaycastDraw.h"

#include "GrlibExceptions/EngineExceptions/DrawSystem/ConsoleDrawException.h"

// Console draw system
class ConsoleDraw : public RaycastDraw {
public:
	// Create console drawer for canvas `canvas`
	ConsoleDraw(Canvas* canvas, double grad_start, double grad_end);

	// Overrided method for drawing into console
	void draw() override;

	// Set gradient
	void set_grad(double start, double end);
	// Get gradient
	std::pair<double, double> get_grad() const;

	// Symbols of drawing
	std::string symbols = "@&%QWNM0B$#DR8HXKAUbGOV496Pkqwfvsz*r+<>;:. ";
	// Symbol for empty space
	char no_symbol = ' ';

private:
	// Start val of grad
	double _grad_start;
	// End val of grad
	double _grad_end;

	// Calculate which symbol to use
	char _cell_symb(double val);
};