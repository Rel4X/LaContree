#include	"RandomMachine.h"

bool		RandomMachine::p_initialized = false;

void		RandomMachine::Init()
{
	if (RandomMachine::p_initialized == false)
	{
		srand(time(0));
		RandomMachine::p_initialized = true;
	}
}

int			RandomMachine::Randomize(int min, int max)
{
	RandomMachine::Init();
	return ((rand() % max) + min);
}