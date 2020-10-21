#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <corecrt_math_defines.h>
#include "Carica.h"
using namespace sf;
using namespace std;

class CaricaDiProva
{
public:
	VertexArray cdp;
	CaricaDiProva(Vector2f position);
	void update(vector<Carica*> c, Color color);
	void draw(RenderWindow& window);
	float electricField = 0.f;
	Vector2f E = Vector2f(0, 0);
	float a = 0;
};

