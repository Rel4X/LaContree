#include	"Card.h"

const char*	Card::p_eColorText[4] = {
				"Spade",
				"Heart",
				"Diamond",
				"Club"
};

const char*	Card::p_eFigureText[8] = {
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

void		Card::PrintConsole()
{
	std::cout << Card::p_eFigureText[this->GetFigure()];
	std::cout << " of ";
	std::cout << Card::p_eColorText[this->GetColor()];
	std::cout << "." << std::endl;
}