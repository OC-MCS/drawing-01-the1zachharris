#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Shape.h"

using namespace std;
using namespace sf;


// stores and manages the vector that holds the drawn shapes
class ShapeMgr
{
private:
	vector<DrawingShape*> shapes;
public:
	ShapeMgr()
	{
		
	}

	void addShape(Vector2f pos, ShapeEnum whichShape, Color color)
	{

		if (whichShape == CIRCLE) {
			Circle* circlePtr = new Circle(whichShape, color, pos);
			shapes.push_back(circlePtr);
		}
		else {
			Square* squarePtr = new Square(whichShape, color, pos);
			shapes.push_back(squarePtr);
		}

	}

	vector<DrawingShape*>* getPtr() {
		return &shapes;
	}

};
