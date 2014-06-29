#pragma once

#include	<map>
#include	"Card.h"

class		CardsPointMap :
	public std::map<Card::eFigure, unsigned int>
{
public:
	CardsPointMap(void);
	~CardsPointMap(void);
};

