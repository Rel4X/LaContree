#include	"CardsTrumpPowerMap.h"

CardsTrumpPowerMap::CardsTrumpPowerMap(void)
{
	this->insert(std::make_pair(Card::eFigure::Jack, 7));
	this->insert(std::make_pair(Card::eFigure::Nine, 6));
	this->insert(std::make_pair(Card::eFigure::Ace, 5));
	this->insert(std::make_pair(Card::eFigure::Ten, 4));
	this->insert(std::make_pair(Card::eFigure::King, 3));
	this->insert(std::make_pair(Card::eFigure::Queen, 2));
	this->insert(std::make_pair(Card::eFigure::Eight, 1));
	this->insert(std::make_pair(Card::eFigure::Seven, 0));
}

CardsTrumpPowerMap::~CardsTrumpPowerMap(void)
{
}
