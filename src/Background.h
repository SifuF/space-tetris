#ifndef BACKGROUND_H
#define BACKGROUND_H

class Background {
private:
	sf::Sprite sprite;
	sf::Texture texture;

	float border = 100.0f;
	bool right = true;

	std::chrono::time_point<std::chrono::steady_clock> timePrev;

public:
	Background() {
		texture.loadFromFile("gfx/bg.jpg");
		sprite.setTexture(texture);
		sprite.setScale( ( scale.screenWidth + border )/ float(texture.getSize().x), (scale.screenHeight + border )/ float(texture.getSize().y ));
		sprite.setPosition(sprite.getPosition().x - border / 2.0f, sprite.getPosition().y - border / 2.0f);
		
		timePrev = std::chrono::steady_clock::now();
	}
	void update() {

		double frameTime = 0.02;
		auto timeNow = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = timeNow - timePrev;
		if (elapsed_seconds.count() > frameTime) {

			float sFactor = 0.025f;
			if (right) {
				if (sprite.getPosition().x < 0) {
					sprite.setPosition(sprite.getPosition().x + sFactor, sprite.getPosition().y + sFactor * 0.25);
				}
				else {
					right = false;
				}
			}
			else {
				if (sprite.getPosition().x > -border) {
					sprite.setPosition(sprite.getPosition().x - sFactor, sprite.getPosition().y - sFactor * 0.25);
				}
				else {
					right = true;
				}
			}

			timePrev = timeNow;
		}
	}

	void draw() {
		scale.window.draw(sprite);
	}
};

#endif
