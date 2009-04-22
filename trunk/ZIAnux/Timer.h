#pragma once

#include <time.h>

#define TICK_FACTOR_MS (CLOCKS_PER_SEC / 1000)

class	Timer
{
private:
	clock_t		_startTicks;
	clock_t		_pausedTicks;
	bool	_paused;
	bool	_started;

	const clock_t	tickTac();
public:
	Timer();
	~Timer();

	void		start();
	void		stop();
	void		pause();
	void		unPause();
	const clock_t	getTicks();
	bool		isStarted();
	bool		isPaused();
};
