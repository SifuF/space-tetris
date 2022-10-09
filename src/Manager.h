#ifndef MANAGER_H
#define MANAGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Scale.h"
#include "Timer.h"
#include "Sound.h"
#include "Grid.h"
#include "Tetromino.h"
#include "Keys.h"
#include "Text.h"
#include "Background.h"

class GameManager {
private: 
	Grid grid1;
	Grid grid2;
    Keys keys;
    ScoreManager scoreManager;
    Background background;

	sf::Music music;

    bool twoPlayer = true;

public:

	GameManager() {
        float xBorder = 50.0f;
        float yBorder = 100.0f;
        grid1.init({0.0f + xBorder, yBorder }, 650.0f);
        grid2.init({scale.screenWidth/2.0f + xBorder, yBorder }, 650.0f, true);

        keys.init(&grid1, &grid2);
        scoreManager.init(&grid1, &grid2);

        if (!music.openFromFile("sound/music.ogg")) {
            std::cout << "error cannot load music!" << std::endl;
        }
        music.setLoop(true);
        music.play();
        
	}
    void advance() {
        grid1.advance();
        grid2.advance();
    }
    
    void run() {
 
        auto timePrev = std::chrono::steady_clock::now();
        double frameTime = 0.5;

        while (scale.window.isOpen())
        {
            sf::Event event;
            while (scale.window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    scale.window.close();
            }

            keys.check();
            scale.window.clear();

#ifdef GRAPHICS
            background.update();
            background.draw();
#endif
            
            grid1.update();
            grid1.draw();

            if (twoPlayer) {
                grid2.update();
                grid2.draw();
            }

            auto timeNow = std::chrono::steady_clock::now();
            std::chrono::duration<double> elapsed_seconds = timeNow - timePrev;
            if (elapsed_seconds.count() > frameTime) {
                advance();
                timePrev = timeNow;
            }

            scoreManager.updateAndDraw();

            scale.window.display();
        }
    }
};

#endif