#ifndef GRID_H
#define GRID_H

#include "Tetromino.h"

class LineArray {
private:
	sf::VertexArray verts;
	sf::RenderWindow* m_window{};
public:

	LineArray() {
		verts.setPrimitiveType(sf::PrimitiveType::Lines);
	}

	void init(sf::RenderWindow* window) {
		m_window = window;
	}

	void draw() {
		m_window->draw(verts);
	}

	void append(vec2f v) {
		verts.append({v, sf::Color::White, {}});
	}

	void append(float x, float y) {
		const vec2f v(x, y);
		verts.append({ v, sf::Color::White, {} });
	}

	void clear() {
		verts.clear();
	}
};

class Grid {
private:
	LineArray lines;
	vec2f pos;
	float gridWidth;
	float gridHeight;
	float length;
	float size = 200.0f;
	Tetromino tetromino;
	type next;
	std::vector<std::vector<int>> playfield;

	Block block;

	bool fullFrame = false;
	int fullFrameCounter = 0;
	int advanceCounter = 0;

	Timer timer;
	Sound sound;
	bool fullLatch = false;

	std::chrono::time_point<std::chrono::steady_clock> timeDown;

	int level = 1;
	int score = 0;
	int scoreLines = 0;
	int maxScore = 0;
	bool player2;
	const char* filename = "data/data.txt";
	const char* filename2 = "data/data2.txt";

	sf::RenderWindow* m_window{};

public:
	Grid() {}

	void init(vec2f p, float s, sf::RenderWindow* window, bool two = false) {
		m_window = window;
		srand(time(NULL));
		player2 = two;
		size = s;
		pos = p;
		gridWidth = GameConfig::screenWidth - size;
		length = gridWidth / GameConfig::columns;
		gridHeight = length * GameConfig::rows;
		
		lines.init(m_window);
		for (int i = 0; i < GameConfig::columns + 1; i++) {
			lines.append(pos.x + i * length, pos.y);
			lines.append(pos.x + i * length, pos.y + gridHeight);
		}
		for (int i = 0; i < GameConfig::rows + 1; i++) {
			lines.append(pos.x, pos.y + i * length);
			lines.append(pos.x + gridWidth, pos.y + i * length);
		}

		tetromino.init(length, pos, randomType(), m_window);
		block.init(length, m_window);
		
		next = randomType();

		buildPlayfield();
		//printPlayfield();
		loadHiScores();
		reset();

	}

	void loadHiScores() {
		std::string s;
		std::ifstream f;

		if(player2)
			f.open(filename2);

		else
			f.open(filename);

		if (f.is_open()) {
			getline(f, s);
			f.close();
			maxScore = stoi(s);
		}
		else {
			std::cout << "Unable to open data.txt"<< std::endl;
		}
	}

	void buildPlayfield() {
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });

	}

	void buildPlayfield2() {
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,0,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,6,0,0,0,0,0,0 });
		playfield.push_back({ 0,0,0,6,6,0,0,7,7,0 });
		playfield.push_back({ 1,0,0,0,6,0,0,0,7,7 });
		playfield.push_back({ 1,0,0,0,4,3,3,3,5,5 });
		playfield.push_back({ 1,2,2,0,4,0,3,2,2,5 });
		playfield.push_back({ 1,2,2,4,4,0,0,2,2,5 });

	}

	void printPlayfield() {
		for (int j = 0; j < playfield.size(); j++) {
			for (int i : playfield[j]) {
				std::cout << i << " ";
			}
			std::cout<<std::endl;
		}
	}

	void checkPlayfield() { // set full rows to all white blocks
		for (int j = 0; j < playfield.size(); j++) {
			bool full = true;
			
			for (int i = 0; i < playfield[j].size(); i++) {
				if (!playfield[j][i]) {
					full = false;
				}
			}
			if (full) {
				fullFrame = true;
				if (!fullLatch) {
					sound.playFullSound();
					timer.start();
					fullLatch = true;
				}
				for (int i = 0; i < playfield[j].size(); i++) {
					playfield[j][i] = 8;
				}
			}
		}
	}

	void removeFromPlayfield() { //remove rows with white blocks
		int combo = 0;
		for (int j = 0; j < playfield.size(); j++) {
			bool whites = true;

			for (int i = 0; i < playfield[j].size(); i++) {
				if (playfield[j][i] != 8) {
					whites = false;
				}
			}
			if (whites) {
				playfield.erase(playfield.begin() + j);
				playfield.insert(playfield.begin(), { 0,0,0,0,0,0,0,0,0,0 });
				fullFrame = false;
				scoreLines++;
				combo++;
			}
		}
		if (combo == 1) { score += 100 * level; }
		else if (combo == 2) { score += 300 * level; }
		else if (combo == 3) { score += 500 * level; }
		else if (combo == 4) { score += 800 * level; }
	}

	void drawPlayfield() {
		for (int j = 0; j < playfield.size(); j++) {
			for (int i = 0; i < playfield[j].size(); i++) {
				block.setPosition(pos.x + i * length, pos.y + j*length);
				if (playfield[j][i] == 1) {			//I
					block.setColor(sf::Color::Cyan);
				}
				else if (playfield[j][i] == 2) {	//O
					block.setColor(sf::Color::Yellow);
				}
				else if (playfield[j][i] == 3) {	//T
					block.setColor(sf::Color::Magenta);
				}
				else if (playfield[j][i] == 4) {	//J
					block.setColor(sf::Color::Blue);
				}
				else if (playfield[j][i] == 5) {	//L
					block.setColor(GameConfig::Orange);
				}
				else if (playfield[j][i] == 6) {	//S
					block.setColor(sf::Color::Green);
				}
				else if (playfield[j][i] == 7) {	//Z
					block.setColor(sf::Color::Red);
				}
				else if (playfield[j][i] == 8) {	//Full
					block.setColor(sf::Color::White);
				}
				else {
					block.setColor(sf::Color::Black);
				}
				
				block.draw();
			}
		}
	}

	void clearPlayfield() {
		for (int j = 0; j < playfield.size(); j++) {
			for (int i = 0; i < playfield[j].size(); i++) {
				playfield[j][i] = 0;
			}
		}
	}

	void moveGrid(vec2f p) {
		pos = p;
		
		lines.clear();

		for (int i = 0; i < GameConfig::columns + 1; i++) {
			lines.append(pos.x + i * length, pos.y);
			lines.append(pos.x + i * length, pos.y + gridHeight);
		}
		for (int i = 0; i < GameConfig::rows + 1; i++) {
			lines.append(pos.x, pos.y + i * length);
			lines.append(pos.x + gridWidth, pos.y + i * length);
		}

		tetromino.setPositionZero(pos);
	}

	void update() {

		tetromino.update(pos);
		wallKick();
		groundKick();
		checkPlayfield();
		checkDeath();
		timer.update();
	
		if (fullFrame) {
			double whiteTime = 0.25;
			if (timer.getSeconds() > whiteTime) {
				removeFromPlayfield();
				fullLatch = false;
				timer.stop();
			}
		}
	}

	void advance() {
			moveTetromino(0);
	}

	void insertToPlayfield() {
		vec2f v[4];
		tetromino.getPositions(v);
		int color = tetromino.getColor();

		int i[4];
		int j[4];

		getPlayfieldIndexFromBlockPosition(v, i, j);

		for (int k = 0; k < 4; k++) {
			if (j[k] < playfield.size()) {
				if (i[k] < playfield[j[k]].size()) {
					playfield[j[k]][i[k]] = color;
				}
			}
		}

		reset();
	}

	//must use array guards when calling this!
	void getPlayfieldIndexFromBlockPosition(vec2f v[], int i[], int j[]) {
		for (int k = 0; k < 4; k++) {	
			i[k] = int((v[k].x - pos.x) / length);
			j[k] = int((v[k].y - pos.y) / length);
		}
	}

	bool collision() {
		vec2f v[4];
		tetromino.getPositions(v);
		
		int i[4];
		int j[4];

		getPlayfieldIndexFromBlockPosition(v, i, j);
	
		bool filled = false;

		for (int k = 0; k < 4; k++) {
			if (j[k] < playfield.size()) {
				if (i[k] < playfield[j[k]].size()) {
					if (playfield[j[k]][i[k]]) {
						filled = true;
					}
				}
			}
		}

		return filled;
	}

	void moveTetrominoDownFromKey() {
		double dropSpeed = 0.025;
		auto timeNow = std::chrono::steady_clock::now();
		std::chrono::duration<double> elapsed_seconds = timeNow - timeDown;
		if (elapsed_seconds.count() > dropSpeed) {
			moveTetromino(0);
			timeDown = timeNow;
		}
	}

	void moveTetromino(int dir) {
		vec2f v[4];
		tetromino.getPositions(v);

		switch(dir) {
		case 1 :
			if (v[0].x + length < pos.x + gridWidth &&
				v[1].x + length < pos.x + gridWidth &&
				v[2].x + length < pos.x + gridWidth &&
				v[3].x + length < pos.x + gridWidth) {
					tetromino.move(length);

					if (collision()) {
						tetromino.move(-length);
					}
			}
			break;
			
		case -1 :
			if (v[0].x > pos.x &&
				v[1].x > pos.x &&
				v[2].x > pos.x &&
				v[3].x > pos.x) {
					tetromino.move(-length);

					if (collision()) {
						tetromino.move(length);
					}
			}
			break;
		
		case 0:
			if (v[0].y + length < pos.y + gridHeight &&
				v[1].y + length < pos.y + gridHeight &&
				v[2].y + length < pos.y + gridHeight &&
				v[3].y + length < pos.y + gridHeight) {
					tetromino.drop(length);

					if (collision()) {
						tetromino.drop(-length);
						insertToPlayfield();
					}
			}
			else {
				insertToPlayfield();
			}
			break;
		}
	}

	void wallKick() {
		vec2f v[4];
		tetromino.getPositions(v);
		if (v[0].x + length > pos.x + gridWidth ||
			v[1].x + length > pos.x + gridWidth ||
			v[2].x + length > pos.x + gridWidth ||
			v[3].x + length > pos.x + gridWidth) {
				tetromino.move(-length);
		}
		else if (v[0].x < pos.x ||
				 v[1].x < pos.x ||
				 v[2].x < pos.x ||
				 v[3].x < pos.x ) {
					tetromino.move(length);
		}
	}

	void groundKick() {
		vec2f v[4];
		tetromino.getPositions(v);
		if (v[0].y + length > pos.y + gridHeight ||
			v[1].y + length > pos.y + gridHeight ||
			v[2].y + length > pos.y + gridHeight ||
			v[3].y + length > pos.y + gridHeight) {
				tetromino.drop(-length);		
		}

	}

	void checkDeath() {
		for (int i = 0; i < playfield[0].size(); i++) {
			if (playfield[0][i]) {
				resetGame();
			}
		}
	}

	void rotate() {
		sound.playRotateSound();
		tetromino.rotate();
		update();
		for(int i=0; i<3; i++) {
			if (collision()) {
				tetromino.rotate();
				update();
			}
			else {
				break;
			}
		}	
	}

	void changeType(type t_new) {
		tetromino.changeType(t_new);
	}

	type randomType() {
		return type(rand() % 7);
	}

	void reset() {
		tetromino.changeType(next);
		tetromino.setPosition(gridWidth/2.0f - 2 * length, 0.0f);
		tetromino.update();
		next = randomType();
	}

	void resetGame() {
		clearPlayfield();
		if (score > maxScore) {
			maxScore = score;
			
			std::ofstream f;
			if (player2) {
				f.open(filename2);
			}
			else {
				f.open(filename);
			}
			f << maxScore;
			f.close();

		}

		score = 0;
		scoreLines = 0;
		reset();
	}
	
	vec2f getPosition() {
		return pos;
	}

	void setPosition(vec2f v) {
		pos = v;
	}

	void setPosition(float x, float y) {
		pos.x = x;
		pos.y = y;
	}

	int getScore() {
		return score;
	}

	int getLines() {
		return scoreLines;
	}
	
	int getHiScore() {
		return maxScore;
	}

	void drawNextPiece() {
		Tetromino n;
		vec2f p = { pos.x + 7 * length, pos.y - 2 * length - 7.0f };
		vec2f p_I = { pos.x + 7 * length - length, pos.y - 2 * length - 7.0f };
		if (next == I) {
			n.init(length, p_I, next, m_window);
		}
		else {
			n.init(length, p, next, m_window);
		}
		n.draw();
	}

	void draw() {
		drawPlayfield();
		lines.draw();
		tetromino.draw();
		drawNextPiece();
	}
};

#endif
