#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Carica {
public:
	CircleShape c;
	double q;
	Carica(Vector2f position, bool p);
	void update(Vector2f position);
	void draw(RenderWindow& window);
};

