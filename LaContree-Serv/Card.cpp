#include	"Card.h"

const char*	Card::eColorText[4] = {
				"Spade",
				"Heart",
				"Diamond",
				"Club"
};

const char*	Card::eFigureText[8] = {
				"Ace",
				"King",
				"Queen",
				"Jack",
				"Ten",
				"Nine",
				"Eight",
				"Seven"
};

Card::Card(eColor c, eFigure f) :
	p_color(c), p_figure(f)
{
}

Card::~Card(void)
{
}

void		Card::PrintConsole() const
{
	std::cout << " -- ";
	std::cout << Card::eFigureText[this->GetFigure()];
	std::cout << " of ";
	std::cout << Card::eColorText[this->GetColor()];
	std::cout << "." << std::endl;
}