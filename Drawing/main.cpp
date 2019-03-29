//================================================
// Zach Harris <-----------------  
//================================================
#include <iostream>
#include <fstream>
using namespace std;
#include <SFML\Graphics.hpp>
#include "SettingsMgr.h"
#include "ShapeMgr.h"
#include "SettingsUI.h"
#include "DrawingUI.h"
using namespace sf;

struct saveSettings {
	Color color;
	ShapeEnum shape;
};
struct saveShapes {
	ShapeEnum shape;
	Color color;
	Vector2f pos;
};

void readFromFile(SettingsMgr& settingsMgr, ShapeMgr& shapeMgr);
void writeToFile(SettingsMgr&, ShapeMgr&);

int main()
{
	const int WINDOW_WIDTH = 800;
	const int WINDOW_HEIGHT = 600;

	RenderWindow window(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Drawing");
	window.setFramerateLimit(60);

	SettingsMgr settingsMgr(Color::Blue, ShapeEnum::CIRCLE);
	SettingsUI  settingsUI(&settingsMgr);
	ShapeMgr    shapeMgr;
	DrawingUI   drawingUI(Vector2f(200, 50));
	
	readFromFile(settingsMgr, shapeMgr);

	while (window.isOpen()) 
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				writeToFile(settingsMgr, shapeMgr);
			}
			else if (event.type == Event::MouseButtonReleased)
			{
				// maybe they just clicked on one of the settings "buttons"
				// check for this and handle it.
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				settingsUI.handleMouseUp(mousePos);
			}
			else if (event.type == Event::MouseMoved && Mouse::isButtonPressed(Mouse::Button::Left))
			{
				
				Vector2f mousePos = window.mapPixelToCoords(Mouse::getPosition(window));
				// check to see if mouse is in the drawing area
				if (drawingUI.isMouseInCanvas(mousePos))
				{
					// add a shape to the list based on current settings
					shapeMgr.addShape(mousePos, settingsMgr.getCurShape(), settingsMgr.getCurColor());
				}
			}
		}

		// the remainder of the body of the loop draws one frame of the animation
		window.clear();

		// this should draw the left hand side of the window (all of the settings info)
		settingsUI.draw(window);

		// this should draw the rectangle that encloses the drawing area, then draw the
		// shapes. This is passed the shapeMgr so that the drawingUI can get the shapes
		// in order to draw them. This redraws *all* of the shapes every frame.
		drawingUI.draw(window, &shapeMgr);

		window.display();
	} // end body of animation loop

	return 0;
}

// reads settings and shapes stored in shapes.bin if that file exists
// if the file doesn't exist it is created
void readFromFile(SettingsMgr& settingsMgr, ShapeMgr& shapeMgr) {

	saveSettings settings;
	saveShapes shapes;
	ifstream save;

	save.open("shapes.bin", ios::binary | ios::in);
	// reads the save settings at the beginning of the file and then sets the current settings to what is stored in the struct
	save.read(reinterpret_cast<char*>(&settings), sizeof(saveSettings));

	if (settings.color == Color::Black) {
		settings.color = Color::Blue;   // if statement if file isn't red and color is defaulted to black
		settings.shape = ShapeEnum::CIRCLE;
	}
			
	settingsMgr.setCurColor(settings.color);
	settingsMgr.setCurShape(settings.shape);
	// uses end of file loop 
	// reads one struct of vector values which is recreated based on if the shape is a circle or a square
	while (save.read(reinterpret_cast<char*>(&shapes), sizeof(saveShapes))) {

		if (shapes.shape == CIRCLE) {

			Circle* circlePtr = new Circle(shapes.shape, shapes.color, shapes.pos);
			shapeMgr.getPtr()->push_back(circlePtr);

		}
		else {

			Square* squarePtr = new Square(shapes.shape, shapes.color, shapes.pos);
			shapeMgr.getPtr()->push_back(squarePtr);

		}

	}

	save.close();

}

// writes all the settings and shapes that are on the screen to the file
void writeToFile(SettingsMgr& settingsMgr, ShapeMgr& shapeMgr) {

	// wtores the current settings into struct
	saveSettings settings = { settingsMgr.getCurColor(), settingsMgr.getCurShape() };
	ofstream save;
	save.open("shapes.bin", ios::binary | ios::out);

	// writes the settings struct to the save file
	save.write(reinterpret_cast<char*>(&settings), sizeof(saveSettings));
	saveShapes shapes;

	// stores the current vector pointer attributes into shapes struct then writes the struct to the save file
	for (int ndx = 0; ndx < shapeMgr.getPtr()->size(); ndx++) {

		shapes = { shapeMgr.getPtr()->operator[](ndx)->getShape(), shapeMgr.getPtr()->operator[](ndx)->getColor(), shapeMgr.getPtr()->operator[](ndx)->getPos() };
		save.write(reinterpret_cast<char*>(&shapes), sizeof(saveShapes));

	}

	save.close();

}