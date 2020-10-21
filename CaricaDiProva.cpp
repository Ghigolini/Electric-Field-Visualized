#include "CaricaDiProva.h"

CaricaDiProva::CaricaDiProva(Vector2f position) {
	cdp.resize(2);
	cdp.setPrimitiveType(Lines);
	cdp[0].position = position;
	cdp[0].color = Color::White;
	cdp[1].color = Color::White;
}

float getMagnitude(Vector2f v) {
	return sqrt(v.x * v.x + v.y * v.y);
}

void setMagnitude(Vector2f& v, float magnitude) {
	v.x = v.x * (magnitude / getMagnitude(v));
	v.y = v.y * (magnitude / getMagnitude(v));
}

void CaricaDiProva::update(vector<Carica*> c, Color color) {
	electricField = 0.f;
	E = Vector2f(0, 0);
	for (int i = 0; i < c.size(); i++) {
		double angle = atan2(c[i]->c.getPosition().y - cdp[0].position.y, c[i]->c.getPosition().x - cdp[0].position.x);
		float k0 = 8.988 * pow(10, 9);
		float Q = c[i]->q;
		float r = sqrt(pow(c[i]->c.getPosition().x - cdp[0].position.x, 2) + pow(c[i]->c.getPosition().y - cdp[0].position.y, 2));
		E.x += (k0 * Q / pow(r, 2)) * cos(angle);
		E.y += (k0 * Q / pow(r, 2)) * sin(angle);
	}
	electricField = sqrt(E.x * E.x + E.y * E.y);
	cdp[0].color = color;
	cdp[1].color = color;
	a = atan2(cdp[0].position.y - (cdp[0].position.y + E.y), cdp[0].position.x - (cdp[0].position.x + E.x));
	cdp[1].position.x = cdp[0].position.x + 10 * cos(a);
	cdp[1].position.y = cdp[0].position.y + 10 * sin(a);
}

void CaricaDiProva::draw(RenderWindow& window) {
	window.draw(cdp);
}