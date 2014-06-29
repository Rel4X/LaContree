#pragma once

#include	<map>
#include	"Card.h"

class		CardsTrumpPointMap :
	public std::map<Card::eFigure, unsigned int>
{
public:
	CardsTrumpPointMap(void);
	~CardsTrumpPointMap(void);
};

