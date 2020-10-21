#include "Carica.h"

Carica::Carica(Vector2f position, bool p) {
	if (p) {
		q = 0.1;
	}
	else {
		q = -0.1;
	}
	c.setPosition(position);
	c.setRadius(10);
	c.setOrigin(c.getRadius(), c.getRadius());
	if (q >= 0) {
		c.setFillColor(Color::Red);
	}
	else {
		c.setFillColor(Color::Blue);
	}
}

void Carica::update(Vector2f position) {
	c.setPosition(position);
	if (q >= 0) {
		c.setFillColor(Color::Red);
	}
	else {
		c.setFillColor(Color::Blue);
	}
}

void Carica::draw(RenderWindow& window) {
	window.draw(c);
}