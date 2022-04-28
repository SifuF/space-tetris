#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background {
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float border = 100.0f;
	bool right = true;

public:
	Background() {
		texture.loadFromFile("gfx/bg.jpg");
		sprite.setTexture(texture);
		sprite.setScale( ( scale.screenWidth + border )/ float(texture.getSize().x), (scale.screenHeight + border )/ float(texture.getSize().y ));
		sprite.setPosition(sprite.getPosition().x - border / 2.0f, sprite.getPosition().y - border / 2.0f);
	}
	void update() {
		float sFactor = 0.025f;
		if (right) {
			if (sprite.getPosition().x < 0) {
				sprite.setPosition(sprite.getPosition().x + sFactor, sprite.getPosition().y + sFactor * 0.25);
			}
			else{
				right = false;
			}
		}
		else {
			if (sprite.getPosition().x > - border) {
				sprite.setPosition(sprite.getPosition().x - sFactor, sprite.getPosition().y - sFactor * 0.25);
			}
			else {
				right = true;
			}
		}
	}

	void draw() {
		scale.window.draw(sprite);
	}
};

#endif
