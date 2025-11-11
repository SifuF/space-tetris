#ifndef TEXT_H
#define TEXT_H

class Text {
private:
	std::optional<sf::Text> text;
	sf::Font font;
	sf::RenderWindow* m_window;

public:
	Text() {
		if (!font.openFromFile("fonts/arial.ttf")) {
			throw std::runtime_error("Cannot load font");
		}

		text.emplace(font, "Hello world", 24);
		text->setFillColor(sf::Color::Red);
		text->setStyle(sf::Text::Bold);
	}

	void init(sf::RenderWindow* window) {
		m_window = window;
	}

	void update(std::string str, int data) {
		std::string s = std::to_string(data);
		text->setString(str + s);
	}

	void setPosition(vec2f pos) {
		text->setPosition(pos);
	}

	vec2f getPosition() {
		return text->getPosition();
	}

	void setColor(sf::Color color) {
		text->setFillColor(color);
	}

	void draw() {
		m_window->draw(text.value());
	}
};

class ScoreManager {
private: 
	Text text;
	Grid* grid1;
	Grid* grid2;
	sf::RenderWindow* m_window;

public:
	ScoreManager() {}

	void init(Grid* g1, Grid* g2, sf::RenderWindow* window) {
		grid1 = g1;
		grid2 = g2;
		m_window = window;
		text.init(window);
	}

	void updateAndDraw() {
		// Player 1
		text.setPosition({ grid1->getPosition().x, grid1->getPosition().y - 100.0f });
		text.update("Score ", grid1->getScore());
		text.setColor(sf::Color::Red);
		text.draw();

		text.setPosition({ text.getPosition().x, text.getPosition().y + 30.0f });
		text.update("Lines ", grid1->getLines());
		text.setColor(sf::Color::Green);
		text.draw();

		text.setPosition({ text.getPosition().x, text.getPosition().y + 30.0f });
		text.update("Hi Score ", grid1->getHiScore());
		text.setColor(sf::Color::Blue);
		text.draw();

		// Player 2
		text.setPosition({ grid2->getPosition().x, grid2->getPosition().y - 100.0f });
		text.update("Score ", grid2->getScore());
		text.setColor(sf::Color::Magenta);
		text.draw();

		text.setPosition({ text.getPosition().x, text.getPosition().y + 30.0f });
		text.update("Lines ", grid2->getLines());
		text.setColor(sf::Color::Yellow);
		text.draw();

		text.setPosition({ text.getPosition().x, text.getPosition().y + 30.0f });
		text.update("Hi Score ", grid2->getHiScore());
		text.setColor(sf::Color::Cyan);
		text.draw();
	
	}
};

#endif
