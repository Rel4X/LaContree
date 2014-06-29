#include	"CardsPowerMap.h"

CardsPowerMap::CardsPowerMap(void)
{
	this->insert(std::make_pair(Card::eFigure::Ace, 7));
	this->insert(std::make_pair(Card::eFigure::Ten, 6));
	this->insert(std::make_pair(Card::eFigure::King, 5));
	this->insert(std::make_pair(Card::eFigure::Queen, 4));
	this->insert(std::make_pair(Card::eFigure::Jack, 3));
	this->insert(std::make_pair(Card::eFigure::Nine, 2));
	this->insert(std::make_pair(Card::eFigure::Eight, 1));
	this->insert(std::make_pair(Card::eFigure::Seven, 0));
}

CardsPowerMap::~CardsPowerMap(void)
{
}
