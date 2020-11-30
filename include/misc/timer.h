#pragma once

class timer {
	typedef std::chrono::microseconds ms;
	typedef std::chrono::steady_clock clk;
	typedef clk::time_point tick;

	tick start;
	ms flow;

	void now() {
		start = clk::now();
	}
public:
	timer() : start(clk::now()), flow(ms(0)) {}

	void run() {
		now();
	}

	void pause() {
		flow += std::chrono::duration_cast<ms>(clk::now() - start);
		now();
	}

	void clear() {
		now();
		flow = ms(0);
	}

	ll count() {
		return flow.count();
	}

	double real() {
		return 1. * flow.count() / 1000;
	}
};
