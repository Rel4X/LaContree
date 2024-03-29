#include	"CardRuler.h"

const CardsPowerMap			CardRuler::p_card_power;
const CardsPointMap			CardRuler::p_card_point;
const CardsTrumpPowerMap	CardRuler::p_card_trump_power;
const CardsTrumpPointMap	CardRuler::p_card_trump_point;

CardRuler::CardRuler(void)
{
}

CardRuler::~CardRuler(void)
{
}

unsigned int		CardRuler::WhoWon(Card* fold[4], Card::eColor asked, Card::eColor trump)
{
	int				iwin;

	iwin = this->CompareTwoCards(fold, asked, trump, 0, 1);
	iwin = this->CompareTwoCards(fold, asked, trump, iwin, 2);
	iwin = this->CompareTwoCards(fold, asked, trump, iwin, 3);
	return (iwin);
}

unsigned int		CardRuler::CompareTwoCards(Card* fold[4], Card::eColor asked, Card::eColor trump, int i1, int i2)
{
	Card*			c1;
	Card*			c2;

	c1 = fold[i1];
	c2 = fold[i2];
	if (c1->GetColor() == trump)
	{
		if (c2->GetColor() == trump)
		{
			if (CardRuler::p_card_trump_power.at(c1->GetFigure()) > CardRuler::p_card_trump_power.at(c2->GetFigure()))
				return (i1);
			return (i2);
		}
		else
			return (i1);
	}
	else
	{
		if (c2->GetColor() == trump)
			return (i2);
		else
		{
			if (c1->GetColor() == asked)
			{
				if (c2->GetColor() == asked)
				{
					if (CardRuler::p_card_power.at(c1->GetFigure()) > CardRuler::p_card_power.at(c2->GetFigure()))
						return (i1);
					return (i2);
				}
				else
					return (i1);
			}
			else
			{
				if (c2->GetColor() == asked)
					return (i2);
				else
					return (i1); // Mais en fait c'est egalite.
			}
		}
	}
}

unsigned int		CardRuler::CountScore(Card* folds[8][4], Card::eColor trump)
{
	int				score;

	score = 0;
	for (int i = 0; i < 8; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			if (folds[i][j] != 0x0)
			{
				if (folds[i][j]->GetColor() == trump)
					score += CardRuler::p_card_trump_point.at(folds[i][j]->GetFigure());
				else
					score += CardRuler::p_card_point.at(folds[i][j]->GetFigure());
			}
		}
	}
	return (score);
}

bool				CardRuler::IsFirstFigureHigher(Card::eFigure f1, Card::eFigure f2, bool t)
{
	if (t == true)
	{
		if (CardRuler::p_card_trump_power.at(f1) > CardRuler::p_card_trump_power.at(f2))
			return (true);
	}
	else
	{
		if (CardRuler::p_card_power.at(f1) > CardRuler::p_card_power.at(f2))
			return (true);
	}
	return (false);
}