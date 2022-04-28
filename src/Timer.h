#ifndef TIMER_H
#define TIMER_H

class Timer{
private:
	std::chrono::time_point<std::chrono::steady_clock> t0;
	std::chrono::time_point<std::chrono::steady_clock> t1;
	bool ticking = false;

public:

	Timer() {}

	void start() {
		ticking = true;
		t0 = std::chrono::steady_clock::now();
		t1 = std::chrono::steady_clock::now();
	}

	void stop() {
		ticking = false;
	}

	double getSeconds() {
		if (ticking) {
			std::chrono::duration<double> elapsed_seconds = t1 - t0;
			return elapsed_seconds.count();
		}
		else {
			return 0.0;
		}
	}

	void update() {
		if (ticking) {
			t1 = std::chrono::steady_clock::now();
		}
	}
};

#endif