#pragma once

#include	<map>
#include	"Card.h"

class		CardsPowerMap :
	public std::map<Card::eFigure, unsigned int>
{
public:
	CardsPowerMap(void);
	~CardsPowerMap(void);
};

