#pragma once
#include <SFML/Graphics.hpp>
#include <string>
using namespace std;
using namespace sf;

// an abstract base class 
// for Circle and Square
class DrawingShape 
{

	private:
		ShapeEnum shape;
		Color color;
		Vector2f pos;

	public:
		virtual void draw(RenderWindow& win) = 0;

		DrawingShape(ShapeEnum shape, Color color, Vector2f pos) {
			this->shape = shape;
			this->color = color;
			this->pos = pos;
		}
		// Sets cur color
		void setColor(Color col) {
			color = col;
		}
		// Returns cur color
		Color getColor() {
			return color;
		}
		// Sets cur shape
		void setShape(ShapeEnum newShape) {
			shape = newShape;
		}
		// Returns cur shape
		ShapeEnum getShape() {
			return shape;
		}
		// Sets position
		void setPos(Vector2f Pos) {
			pos = Pos;
		}
		// Returns position
		Vector2f getPos() {
			return pos;
		}

};

// add Circle, Square classes below. These are derived from DrawingShape

class Circle: public DrawingShape
{

	private:
		CircleShape circle;

	public:
		Circle(ShapeEnum shape, Color color, Vector2f pos) : DrawingShape(shape, color, pos) {}

		void draw(RenderWindow& win) {
			circle.setRadius(20.0f);
			circle.setFillColor(getColor());
			circle.setOutlineColor(getColor());
			circle.setPosition(getPos());
			win.draw(circle);
		}

};

class Square :public DrawingShape
{

	private:
		RectangleShape square;

	public:
		Square(ShapeEnum shape, Color color, Vector2f pos) : DrawingShape(shape, color, pos) {}

		void draw(RenderWindow& win) {
			square.setSize(Vector2f(40.0f, 40.0f));
			square.setFillColor(getColor());
			square.setOutlineColor(getColor());
			square.setPosition(getPos());
			win.draw(square);
		}
};


