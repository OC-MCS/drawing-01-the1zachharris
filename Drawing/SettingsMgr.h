#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

enum ShapeEnum { CIRCLE, SQUARE };

// stores and manages the settings
class SettingsMgr
{
private:
	Color color;
	ShapeEnum shape;
	
public:
	SettingsMgr(Color startingColor, ShapeEnum startingShape )
	{
		color = startingColor;
		shape = startingShape;

	}

	Color getCurColor()
	{
		return color; 
	}


	ShapeEnum getCurShape()
	{
		return shape;
	}

	void setCurColor(Color newColor)
	{
		color = newColor;
	}

	void setCurShape(ShapeEnum newShape)
	{
		shape = newShape;
	}

};
