#pragma once

#include	<iostream>
#include	<vector>
#include	<utility>
#include	"Card.h"

class		Player
{
private:
	static unsigned int	p_nxt_id;

private:
	unsigned int		p_id;
	std::vector<Card*>	p_cards;

public:
	Player(void);
	~Player(void);

public:
	unsigned int	GetId() const	{ return (this->p_id); }

public:
	void			PrintConsole();
	void			GiveCard(Card*, int);
	const Card*		ViewCard(unsigned int);
	void			MakeCall(std::pair<int, Card::eColor>&);
	unsigned int	Play();
	Card*			PlayCard(unsigned int);
};

