#pragma once

#include	"Card.h"

class		CardRuler
{
public:
	CardRuler(void);
	~CardRuler(void);

public:
	unsigned int		PointCounter(Card***);
	unsigned int		WhosWinner(Card**, Card::eColor);
};

