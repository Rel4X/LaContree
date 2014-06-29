#pragma once

#include	<map>
#include	"Card.h"

class		CardsTrumpPowerMap :
	public std::map<Card::eFigure, unsigned int>
{
public:
	CardsTrumpPowerMap(void);
	~CardsTrumpPowerMap(void);
};

