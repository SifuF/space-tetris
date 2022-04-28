#ifndef SCALE_H
#define SCALE_H

typedef sf::Vector2f vec2f;

struct vec8f{
public:
	vec2f v0;
	vec2f v1;
	vec2f v2;
	vec2f v3;
};

class Scale {
public:
	int screenWidth = 1080;
	int screenHeight = 1000;
	//float length = screenWidth/10.0f;
	int columns = 10;
	int rows = 20;
	sf::RenderWindow window;
	sf::Color Orange;

	bool graphics = true;


	Scale() {
		window.create(sf::VideoMode(screenWidth, screenHeight), "SifuF Tetris");

		Orange.r = 255;
		Orange.g = 165;
		Orange.b = 0;
	}
}scale;

#endif
