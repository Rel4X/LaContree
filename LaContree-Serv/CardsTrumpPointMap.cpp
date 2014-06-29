#include	"CardsTrumpPointMap.h"

CardsTrumpPointMap::CardsTrumpPointMap(void)
{
	this->insert(std::make_pair(Card::eFigure::Ace, 11));
	this->insert(std::make_pair(Card::eFigure::Ten, 10));
	this->insert(std::make_pair(Card::eFigure::King, 4));
	this->insert(std::make_pair(Card::eFigure::Queen, 3));
	this->insert(std::make_pair(Card::eFigure::Jack, 20));
	this->insert(std::make_pair(Card::eFigure::Nine, 14));
	this->insert(std::make_pair(Card::eFigure::Eight, 0));
	this->insert(std::make_pair(Card::eFigure::Seven, 0));
}

CardsTrumpPointMap::~CardsTrumpPointMap(void)
{
}
