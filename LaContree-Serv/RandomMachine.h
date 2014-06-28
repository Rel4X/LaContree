#pragma once

#include	<random>
#include	<ctime>

class		RandomMachine
{
private:
	static bool		p_initialized;

private:
	RandomMachine(void)		{ }
	~RandomMachine(void)	{ }

public:
	static void			Init();
	static int			Randomize(int, int);
};

