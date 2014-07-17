#pragma once

#include	<iostream>
#include	<list>
#include	<vector>
#include	<algorithm>
#include	"RandomMachine.h"
#include	"Card.h"

class		CardsDeck
{
private:
	std::list<Card*>	p_cards;

public:
	CardsDeck(void);
	~CardsDeck(void);

public:
	unsigned int		GetSize() const		{ return (this->p_cards.size()); }

public:
	void	PrintConsole() const;
	void	Shuffle();
	void	Cut();
	Card*	Pick();
	void	Put(Card*);
};

