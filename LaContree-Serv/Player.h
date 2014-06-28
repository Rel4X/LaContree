#pragma once

#include	<iostream>
#include	<vector>
#include	"Card.h"

class		Player
{
private:
	std::vector<Card*>	p_cards;

public:
	Player(void);
	~Player(void);

public:
	void	PrintConsole();
	void	GiveCard(Card*, int);
};

