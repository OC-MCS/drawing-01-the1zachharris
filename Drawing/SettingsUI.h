#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;
#include "SettingsMgr.h"

void die(string msg)
{
	cout << msg << endl;
	exit(400);
}

// stores and handles all the logic for the settings UX
class SettingsUI
{
private:

	SettingsMgr* Mgr;
	RectangleShape btnArea;
	Color color;
	ShapeEnum shape;
	CircleShape blueBtn;
	CircleShape redBtn;
	CircleShape greenBtn;
	CircleShape circleBtn;
	RectangleShape squareBtn;
	

public:
	SettingsUI(SettingsMgr *mgr)
	{
		Mgr = mgr;

		CircleShape c1(25, 30);
		CircleShape c2(20, 30);

		RectangleShape r(Vector2f(40.0f, 40.0f));
		RectangleShape r2(Vector2f(194.0f, 594.0f));
		
		circleBtn = c2;
		squareBtn = r;
		redBtn = c1;
		greenBtn = c1;
		blueBtn = c1;
		btnArea = r2;

		color = mgr->getCurColor();
		shape = mgr->getCurShape();
	}

	// checks and handles if the user just clicked on one of the settings "buttons"
	void handleMouseUp(Vector2f mouse)
	{
		
		if (redBtn.getGlobalBounds().contains(mouse))
		{
			color = Color::Red;
			Mgr->setCurColor(Color::Red);
		}
		if (greenBtn.getGlobalBounds().contains(mouse))
		{
			color = Color::Green;
			Mgr->setCurColor(Color::Green);
		}
		if (blueBtn.getGlobalBounds().contains(mouse))
		{
			color = Color::Blue;
			Mgr->setCurColor(Color::Blue);
		}
		if (circleBtn.getGlobalBounds().contains(mouse))
		{
			shape = CIRCLE;
			Mgr->setCurShape(ShapeEnum::CIRCLE);
		}
		if (squareBtn.getGlobalBounds().contains(mouse))
		{
			shape = SQUARE;
			Mgr->setCurShape(ShapeEnum::SQUARE);
		}

	}

	// handles drawing all the settings and contains the logic for the buttons
	void draw(RenderWindow& win)
	{

		color = Mgr->getCurColor();
		shape = Mgr->getCurShape();

		// draws the button region
		btnArea.setPosition(Vector2f(3.0f, 3.0f));
		btnArea.setOutlineColor(Color::Black);
		btnArea.setOutlineThickness(3);
		win.draw(btnArea);

		// draws the Color Label
		Font font;
		if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
			die("couldn't load font");
		Text Color("Drawing Color", font, 25);
		Color.setFillColor(Color::Black);
		Color.setPosition(Vector2f(15.0f, 25.0f));
		win.draw(Color);

		// draws the Color Cirlces
		float x = 70.0f, y = 85.0f;

		redBtn.setOutlineColor(Color::Red);
		redBtn.setOutlineThickness(3);
		redBtn.setPosition(Vector2f(x, y));
		win.draw(redBtn);

		greenBtn.setOutlineColor(Color::Green);
		greenBtn.setOutlineThickness(3);
		greenBtn.setPosition(Vector2f(x, y + 80.0f));
		win.draw(greenBtn);

		blueBtn.setOutlineColor(Color::Blue);
		blueBtn.setOutlineThickness(3);
		blueBtn.setPosition(Vector2f(x, y + 160.0f));
		win.draw(blueBtn);

		// draws the Shape Label
		Font font2;
		if (!font2.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
			die("couldn't load font");
		}

		Text Shape("Shape Selector", font, 25);
		Shape.setFillColor(Color::Black);
		Shape.setPosition(Vector2f(15.0f, y + 280.0f));
		win.draw(Shape);

		// draws the Shape Outlines
		circleBtn.setPosition(Vector2f(x, y + 360));
		circleBtn.setOutlineColor(Color::Black);
		circleBtn.setOutlineThickness(3);
		win.draw(circleBtn);

		squareBtn.setPosition(Vector2f(x, y + 430.0f));
		squareBtn.setOutlineColor(Color::Black);
		squareBtn.setOutlineThickness(3);
		win.draw(squareBtn);

		if (color == Color::Red)
		{
			redBtn.setFillColor(Color::Red);
			win.draw(redBtn);
		}
		else if (color == Color::Green)
		{
			greenBtn.setFillColor(Color::Green);
			win.draw(greenBtn);
		}
		else if (color == Color::Blue)
		{
			blueBtn.setFillColor(Color::Blue);
			win.draw(blueBtn);
		}
		if (shape == CIRCLE)
		{
			circleBtn.setFillColor(Color::Black);
			win.draw(circleBtn);
		}
		else if (shape == SQUARE)
		{
			squareBtn.setFillColor(Color::Black);
			win.draw(squareBtn);
		}

		////////////// detects if mouse is within the button bounds ///////////////
		
		// if mouse is in the button region, they will fill
		if (redBtn.getGlobalBounds().contains(win.mapPixelToCoords(Mouse::getPosition(win))))
		{
			redBtn.setFillColor(Color::Red);
			win.draw(redBtn);
		}
		else if (!(redBtn.getGlobalBounds().contains(win.mapPixelToCoords(Mouse::getPosition(win)))) && color != Color::Red)
		{
			redBtn.setFillColor(Color::White);
			win.draw(redBtn);
		}

		if (greenBtn.getGlobalBounds().contains(win.mapPixelToCoords(Mouse::getPosition(win))))
		{
			greenBtn.setFillColor(Color::Green);
			win.draw(greenBtn);
		}
		else if (!(greenBtn.getGlobalBounds().contains(win.mapPixelToCoords(Mouse::getPosition(win)))) && color != Color::Green)
		{
			greenBtn.setFillColor(Color::White);
			win.draw(greenBtn);
		}

		if (blueBtn.getGlobalBounds().contains(win.mapPixelToCoords(Mouse::getPosition(win))))
		{
			blueBtn.setFillColor(Color::Blue);
			win.draw(blueBtn);
		}
		else if (!(blueBtn.getGlobalBounds().contains(win.mapPixelToCoords(Mouse::getPosition(win)))) && color != Color::Blue)
		{
			blueBtn.setFillColor(Color::White);
			win.draw(blueBtn);
		}

		// ff mouse enters the shapes, they will fill
		if (circleBtn.getGlobalBounds().contains(win.mapPixelToCoords(Mouse::getPosition(win))))
		{
			circleBtn.setFillColor(Color::Black);
			win.draw(circleBtn);
		}
		else if (!(circleBtn.getGlobalBounds().contains(win.mapPixelToCoords(Mouse::getPosition(win)))) && shape != ShapeEnum::CIRCLE)
		{
			circleBtn.setFillColor(Color::White);
			win.draw(circleBtn);
		}

		if (squareBtn.getGlobalBounds().contains(win.mapPixelToCoords(Mouse::getPosition(win))))
		{
			squareBtn.setFillColor(Color::Black);
			win.draw(squareBtn);
		}
		else if (!(squareBtn.getGlobalBounds().contains(win.mapPixelToCoords(Mouse::getPosition(win)))) && shape != ShapeEnum::SQUARE)
		{
			squareBtn.setFillColor(Color::White);
			win.draw(squareBtn);
		}
	}

	void die(string msg) {
		cout << msg << endl;
		exit(400);
	}

};
