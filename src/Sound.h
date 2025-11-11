#ifndef SOUND_H
#define SOUND_H

#include <optional>

class Sound {
private:
	sf::SoundBuffer rotateBuffer;
	std::optional<sf::Sound> rotateSound;

	sf::SoundBuffer fullBuffer;
	std::optional<sf::Sound> fullSound;

public:
	Sound() {

		if (!rotateBuffer.loadFromFile("sound/rotate.wav")) {
			std::cout << "error cannot load sound!" << std::endl;
		}
		rotateSound.emplace(rotateBuffer);

		if (!fullBuffer.loadFromFile("sound/full.wav")) {
			std::cout << "error cannot load sound!" << std::endl;
		}
		fullSound.emplace(fullBuffer);
	}

	void playRotateSound() {
		rotateSound->play();
	}

	void playFullSound() {
		fullSound->play();
	}
};

#endif