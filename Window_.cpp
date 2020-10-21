#include "Window_.h"
#include "Carica.h"
#include "CaricaDiProva.h"

vector<CaricaDiProva> cdp;
vector<Carica*> c;
float maxField, minField;
bool p = true;

Window_::Window_(Vector2f windowSize, string title, bool fullscreen) {
	ContextSettings settings;
	settings.antialiasingLevel = 8;
	Uint32 *style = new Uint32;
	if (fullscreen) {
		*style = Style::Fullscreen;
	}
	else {
		*style = Style::None;
	}
	this->window.create(VideoMode(windowSize.x, windowSize.y), "title", *style, settings);
	this->window.setVerticalSyncEnabled(true);

	delete style;

	c.push_back(new Carica(Vector2f(Mouse::getPosition().x, Mouse::getPosition().x), p));
	
	for (int i = 0; i < 1120; i += 10) {
		for (int j = 0; j < 630; j += 10) {
			cdp.push_back(CaricaDiProva(Vector2f(i, j)));
		}
	}

	maxField = cdp[0].electricField, minField = cdp[0].electricField;
	for (int i = 0; i < c.size(); i++) {
		if (maxField < cdp[i].electricField) {
			maxField = cdp[i].electricField;
		}
		if (minField > cdp[i].electricField) {
			minField = cdp[i].electricField;
		}
	}	
}

void Window_::Run() {
	while (this->window.isOpen()) {
		this->Update();
		this->Render();
	}
}

Time spawnTime = seconds(0);
Time changeTime = seconds(0);

float mapValue(float s, float a1, float a2, float b1, float b2) {
	return b1 + ((a2 - a1) * (b2 - b1)) / (s - a1);
}

void Window_::Update() {
	gameTime = clock.getElapsedTime();
	Event e;
	this->window.pollEvent(e);
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		this->window.close();
	}
	if (Mouse::isButtonPressed(Mouse::Right) && gameTime - changeTime > milliseconds(500)) {
		p = !p;
		c[0]->q = -c[0]->q;
		changeTime = gameTime;
	}
	if (Mouse::isButtonPressed(Mouse::Left) && gameTime - spawnTime > seconds(1)) {
		c.push_back(new Carica(Vector2f(Mouse::getPosition().x - window.getPosition().x, Mouse::getPosition().y - window.getPosition().y), p));
		spawnTime = gameTime;
	}
	c[0]->update(Vector2f(Mouse::getPosition().x - window.getPosition().x, Mouse::getPosition().y - window.getPosition().y));

	for (int i = 0; i < cdp.size(); i++) {
		Color color = Color::Color(255 - mapValue(cdp[i].electricField, maxField - 100000, maxField, 0, 255), 0, 0);
		cdp[i].update(c, color);
	}
}

void Window_::Render() {
	this->window.clear();
	for (int i = 0; i < cdp.size(); i++) {
		if (cdp[i].cdp[0].color.a != 0) {
			cdp[i].draw(window);
		}
	}
	for (int i = 0; i < c.size(); i++) {
		c[i]->draw(window);
	}
	this->window.display();
}