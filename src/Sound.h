#ifndef SOUND_H
#define SOUND_H

class Sound {
private:
	sf::SoundBuffer rotateBuffer;
	sf::Sound rotateSound;

	sf::SoundBuffer fullBuffer;
	sf::Sound fullSound;

public:
	Sound() {

		if (!rotateBuffer.loadFromFile("sound/rotate.wav")) {
			std::cout << "error cannot load sound!" << std::endl;
		}
		rotateSound.setBuffer(rotateBuffer);

		if (!fullBuffer.loadFromFile("sound/full.wav")) {
			std::cout << "error cannot load sound!" << std::endl;
		}
		fullSound.setBuffer(fullBuffer);
	}

	void playRotateSound() {
		rotateSound.play();
	}

	void playFullSound() {
		fullSound.play();
	}
};

#endif