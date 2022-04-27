#ifndef KEYS_H
#define KEYS_H

class Keys {
private:
    Grid* grid1;
    Grid* grid2;

	bool rotateLatch1 = false;
	bool moveLeftLatch1 = false;
	bool moveRightLatch1 = false;
	bool dropLatch1 = false;
	bool typeLatch1 = false;
	bool upLatch1 = false;
    bool insertLatch1 = false;
    bool clearLatch1 = false;
    int dropCounter1 = 0;
	int t_type1 = 0;

    bool rotateLatch2 = false;
    bool moveLeftLatch2 = false;
    bool moveRightLatch2 = false;
    bool dropLatch2 = false;
    bool typeLatch2 = false;
    bool upLatch2 = false;
    bool insertLatch2 = false;
    bool clearLatch2 = false;
    int dropCounter2 = 0;
    int t_type2 = 0;

public:
    Keys() {}

    Keys(Grid* g1, Grid* g2) {
        grid1 = g1;
        grid2 = g2;
    }

    void init(Grid* g1, Grid* g2) {
        grid1 = g1;
        grid2 = g2;
    }

    void check() {
        dropCounter1++;
        dropCounter2++;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            if (!moveLeftLatch1) {
                grid1->moveTetromino(-1);
                moveLeftLatch1 = true;
            }
        }
        else {
            moveLeftLatch1 = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            if (!moveRightLatch1) {
                grid1->moveTetromino(1);
                moveRightLatch1 = true;
            }
        }
        else {
            moveRightLatch1 = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            if (dropCounter1 > 25) {
                grid1->moveTetromino(0);
                dropCounter1 = 0;;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)) {
            if (!upLatch1) {
                grid1->reset();
                upLatch1 = true;
            }
        }
        else {
            upLatch1 = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
            if (!insertLatch1) {
                grid1->insertToPlayfield();
                insertLatch1 = true;
            }
        }
        else {
            insertLatch1 = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (!clearLatch1) {
                grid1->resetGame();
                clearLatch1 = true;
            }
        }
        else {
            clearLatch1 = false;
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::T)) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            if (!rotateLatch1) {
                grid1->rotate();
                rotateLatch1 = true;
            }
        }
        else {
            rotateLatch1 = false;
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y)) {
            if (!typeLatch1) {

                if (t_type1 > 6) { t_type1 = 0; }

                switch (t_type1) {
                case 0:
                    grid1->changeType(I);
                    break;
                case 1:
                    grid1->changeType(O);
                    break;
                case 2:
                    grid1->changeType(T);
                    break;
                case 3:
                    grid1->changeType(J);
                    break;
                case 4:
                    grid1->changeType(L);
                    break;
                case 5:
                    grid1->changeType(S);
                    break;
                case 6:
                    grid1->changeType(Z);
                    break;
                default:
                    t_type1 = -1;
                    break;
                }
                t_type1++;
                typeLatch1 = true;
            }
        }
        else {
            typeLatch1 = false;
        }


        //Player 2

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            if (!moveLeftLatch2) {
                grid2->moveTetromino(-1);
                moveLeftLatch2 = true;
            }
        }
        else {
            moveLeftLatch2 = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            if (!moveRightLatch2) {
                grid2->moveTetromino(1);
                moveRightLatch2 = true;
            }
        }
        else {
            moveRightLatch2 = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            if (!rotateLatch2) {
                grid2->rotate();
                rotateLatch2 = true;
            }
        }
        else {
            rotateLatch2 = false;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            if (dropCounter2 > 25) {
                grid2->moveTetromino(0);
                dropCounter2 = 0;
            }
        }
    }
};

#endif