#ifndef TETROMINO_H
#define TETROMINO_H

enum type { I, O, T, J, L, S, Z };         

class Block {
private:

	float length;

#ifdef GRAPHICS
	sf::Sprite shape;
	sf::Texture shapeT;
#else
	sf::RectangleShape shape;
#endif

public:

	Block() {}

	void init(float l) {
		length = l;
		shape.setPosition(100.0f, 100.0f);

#ifdef GRAPHICS
		shapeT.loadFromFile("gfx/block.png");
		shape.setTexture(shapeT);
		shape.setTextureRect(sf::IntRect(400, 0, 100, 100));
		shape.setScale(length / float(shapeT.getSize().x/9), length / float(shapeT.getSize().y));
#else
		sf::Vector2f v(length, length);
		shape.setSize(v);
#endif

	}

	void draw() {
		scale.window.draw(shape);
	}

	vec2f getPosition() {
		return shape.getPosition();
	}

	void setPosition(vec2f v) {
		shape.setPosition(v);
	}

	void setPosition(float x, float y) {
		shape.setPosition(x, y);
	}

	void setColor(sf::Color c) {
#ifdef GRAPHICS			
		switchColor(c);			//seperate image for each mino
		//shape.setColor(c);	//single texture blended with color value
#else
		
		shape.setFillColor(c);	//used for RectangleShape
#endif	
	}

	void switchColor(sf::Color c) {
		if (c == sf::Color::Red) { shape.setTextureRect(sf::IntRect(0, 0, 100, 100)); }
		else if (c == sf::Color::Green) { shape.setTextureRect(sf::IntRect(100, 0, 100, 100)); }
		else if (c == sf::Color::Blue) { shape.setTextureRect(sf::IntRect(200, 0, 100, 100)); }
		else if (c == sf::Color::Yellow) { shape.setTextureRect(sf::IntRect(300, 0, 100, 100)); }
		else if (c == sf::Color::Cyan) { shape.setTextureRect(sf::IntRect(400, 0, 100, 100)); }
		else if (c == sf::Color::Magenta) { shape.setTextureRect(sf::IntRect(500, 0, 100, 100)); }
		else if (c == scale.Orange) { shape.setTextureRect(sf::IntRect(600, 0, 100, 100)); }
		else if (c == sf::Color::White) { shape.setTextureRect(sf::IntRect(700, 0, 100, 100)); }
		else if (c == sf::Color::Black) { shape.setTextureRect(sf::IntRect(800, 0, 100, 100)); }
	}

	~Block() {}
};

class Tetromino {
private:
	Block block[4];
	vec2f pos0;		//actual screen coordinates, p = pos0 + pos
	vec2f pos;
	int rot = 0;
	float length;
	type t;

public:
	
	Tetromino() {}

	void init(float l, vec2f p, type ty) {
		length = l;
		pos0 = p;
		pos = { 0.0f, 0.0f };

		for (int i = 0; i < 4; i++) {
			block[i].init(length);
		}

		t = ty;

		update({0.0f, 0.0f});

		//block[0].setColor(sf::Color::Red);
		//block[1].setColor(sf::Color::Green);
		//block[2].setColor(sf::Color::Blue);
		//block[3].setColor(sf::Color::Yellow);
	}

	void rotate() {
		rot++;
		if (rot > 3) {
			rot = 0;
		}
	}

	void update() {
		update(pos0);
	}

	void update(vec2f p) {

		switch (t) {
		case I:
			if (rot == 0) {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[2].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x + 3 * length, pos0.y + pos.y);
			}
			else if(rot == 1) {
				block[0].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y - length);
				block[1].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
				block[2].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + 2 * length);
			}
			else if (rot == 2) {
				block[0].setPosition(pos0.x + pos.x + 3 * length, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
			}
			else {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y - length);
			}
			for (int i = 0; i < 4; i++) { block[i].setColor(sf::Color::Cyan); }
			break;

		case O:
			if (rot == 0) {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
			}
			else if (rot == 1) {
				block[0].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
			}
			else if (rot == 2) {
				block[0].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
			}
			else {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[2].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
			}
			for (int i = 0; i < 4; i++) { block[i].setColor(sf::Color::Yellow); }
			break;

		case T:
			if (rot == 0) {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
			}
			else if (rot == 1) {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[3].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
			}
			else if (rot == 2) {		
				block[0].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
			}
			else {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
			}
			for (int i = 0; i < 4; i++) { block[i].setColor(sf::Color::Magenta); }
			break;

		case J:
			if (rot == 0) {
				block[0].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y);
			}
			else if (rot == 1) {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
			}
			else if (rot == 2) {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + 2 * length);
			}
			else {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y + 2 * length);
			}
			for (int i = 0; i < 4; i++) { block[i].setColor(sf::Color::Blue); }
			break;

		case L:
			if (rot == 0) {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
			}
			else if (rot == 1) {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[3].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + 2 * length);
			}
			else if (rot == 2) {
				block[0].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y + 2 * length);
			}
			else {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y);
			}
			for (int i = 0; i < 4; i++) { block[i].setColor(scale.Orange); }
			break;

		case S:
			if (rot == 0) {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
			}
			else if (rot == 1) {
				block[0].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + 2 * length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
			}
			else if (rot == 2) {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[1].setPosition(pos0.x + pos.x, pos0.y + pos.y + 2 * length);
				block[2].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);	
			}
			else {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x, pos0.y + pos.y);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
			}
			for (int i = 0; i < 4; i++) { block[i].setColor(sf::Color::Green); }
			break;

		case Z:
			if (rot == 0) {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
			}
			else if (rot == 1) {
				block[0].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
			}
			else if (rot == 2) {
				block[0].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + 2 * length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);	
			}
			else {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y + 2 * length);
				block[1].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);	
			}
			for (int i = 0; i < 4; i++) { block[i].setColor(sf::Color::Red); }
			break;
		}
	}


	void update2(vec2f p) {

		switch (t) {
		case I:
			if (rot == 0 || rot == 2) {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[2].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x + 3 * length, pos0.y + pos.y);
			}
			else {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y + 2 * length);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y + 3 * length);
			}
			for (int i = 0; i < 4; i++) { block[i].setColor(sf::Color::Cyan); }
			break;

		case O:
			block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y);
			block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
			block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
			block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
			for (int i = 0; i < 4; i++) { block[i].setColor(sf::Color::Yellow); }
			break;

		case T:
			if (rot == 0) {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[2].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
			}
			else if (rot == 1) {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
			}
			else if (rot == 2) {
				block[0].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
			}
			else {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y + 2 * length);
				block[1].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
			}
			for (int i = 0; i < 4; i++) { block[i].setColor(sf::Color::Magenta); }
			break;

		case J:
			if (rot == 0) {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[2].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
			}
			else if (rot == 1) {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y + 2 * length);
			}
			else if (rot == 2) {
				block[0].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y);
			}
			else {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y + 2 * length);
				block[1].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
			}
			for (int i = 0; i < 4; i++) { block[i].setColor(sf::Color::Blue); }
			break;

		case L:
			if (rot == 0) {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[2].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
			}
			else if (rot == 1) {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y);
			}
			else if (rot == 2) {
				block[0].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
			}
			else {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y + 2 * length);
				block[1].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
			}
			for (int i = 0; i < 4; i++) { block[i].setColor(sf::Color::White); }
			break;

		case S:
			if (rot == 0 || rot == 2) {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
			}
			else {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + 2 * length);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
			}
			for (int i = 0; i < 4; i++) { block[i].setColor(sf::Color::Green); }
			break;

		case Z:
			if (rot == 0 || rot == 2) {
				block[0].setPosition(pos0.x + pos.x, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[2].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x + 2 * length, pos0.y + pos.y + length);
			}
			else {
				block[0].setPosition(pos0.x + pos.x + length, pos0.y + pos.y);
				block[1].setPosition(pos0.x + pos.x + length, pos0.y + pos.y + length);
				block[2].setPosition(pos0.x + pos.x, pos0.y + pos.y + length);
				block[3].setPosition(pos0.x + pos.x, pos0.y + pos.y + 2 * length);
			}
			for (int i = 0; i < 4; i++) { block[i].setColor(sf::Color::Red); }
			break;
		}
	}

	void move(float amount) {
		pos.x = pos.x + amount;
		update();
	}

	void drop(float amount) {
		pos.y = pos.y + amount;
		update();
	}

	int getColor() {
		return int(t)+1;
	}

	void getPositions(vec2f vec[]) {
		vec[0] = block[0].getPosition();
		vec[1] = block[1].getPosition();
		vec[2] = block[2].getPosition();
		vec[3] = block[3].getPosition();
	}

	void setPosition(vec2f vec) {	// position relative to grid
		pos = vec;
		update();
	}

	void setPosition(float x, float y) {
		pos.x = x;
		pos.y = y;
		update();
	}

	void setPositionZero(vec2f vec) {	// position in space
		pos0 = vec;
		update();
	}

	void setPositionZero(float x, float y) {
		pos0.x = x;
		pos0.y = y;
		update();
	}

	void changeType(type t_new) {
		t = t_new;
		update();
	}

	type getType() {
		return t;
	}

	void draw() {
		for (int i = 0; i < 4; i++) {
			block[i].draw();
		}
	}

	~Tetromino() {}
};

#endif