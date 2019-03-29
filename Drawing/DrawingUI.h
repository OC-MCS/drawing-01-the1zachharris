#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
#include "ShapeMgr.h"

// stores and handles all the logic for the drawingArea UX
class DrawingUI
{
private:

	RectangleShape drawingArea;
	RectangleShape realArea;

public:
	DrawingUI(Vector2f p)
	{

		RectangleShape r3(Vector2f(597.0f, 594.0f));
		drawingArea = r3;

		RectangleShape r4(Vector2f(557.0f, 554.0f));
		realArea = r4;

	}

	void draw(RenderWindow& win, ShapeMgr *mgr)
	{

		// Draws the big drawing background
		drawingArea.setPosition(Vector2f(200.0f, 3.0f));
		drawingArea.setOutlineColor(Color::Black);
		drawingArea.setFillColor(Color::White);
		drawingArea.setOutlineThickness(3);
		win.draw(drawingArea);

		// Draws the smaller drawing background
		realArea.setPosition(Vector2f(200.0f, 3.0f));
		realArea.setOutlineColor(Color::Transparent);
		realArea.setOutlineThickness(3);
		win.draw(realArea);

		for (int ndx = 0; ndx < mgr->getPtr()->size(); ndx++)
		{
			mgr->getPtr()->operator[](ndx)->draw(win);
		}

	}
	
	bool isMouseInCanvas(Vector2f mousePos)
	{

		if (realArea.getGlobalBounds().contains(mousePos)) {
			return true;
		}
		else {
			return false;
		}

	}

};

