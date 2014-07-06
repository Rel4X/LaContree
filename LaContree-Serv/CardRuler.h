#pragma once

#include	<map>
#include	"Card.h"
#include	"CardsPowerMap.h"
#include	"CardsPointMap.h"
#include	"CardsTrumpPowerMap.h"
#include	"CardsTrumpPointMap.h"

class		CardRuler
{
private:
	static CardsPowerMap			p_card_power;		// Puissance des cartes.
	static CardsPointMap			p_card_point;		// Points des cartes.
	static CardsTrumpPowerMap		p_card_trump_power;	// Puissance des cartes, atout.
	static CardsTrumpPointMap		p_card_trump_point;	// Points des cartes, atout.

public:
	CardRuler(void);
	~CardRuler(void);

public:
	unsigned int		WhoWon(Card* [4], Card::eColor, Card::eColor);
	unsigned int		CountScore(Card* [8][4], Card::eColor);
	unsigned int		CompareTwoCards(Card* [4], Card::eColor, Card::eColor, int i1, int i2);
	bool				IsFirstFigureHigher(Card::eFigure, Card::eFigure, bool);
};

