#pragma once

class	Timer
{
private:
	int		_startTicks;
	int		_pausedTicks;
	bool	_paused;
	bool	_started;
public:
	Timer();
	~Timer();

	void	start();
	void	stop();
	void	pause();
	void	unPause();
	int		getTicks();
	bool	isStarted();
	bool	isPaused();
};
