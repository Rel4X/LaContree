#include	"Player.h"

Player::Player(void) :
	p_cards(8, 0x0)
{
}

Player::~Player(void)
{
}

void		Player::PrintConsole()
{
	for (int i = 0; i < 8; ++i)
	{
		if (this->p_cards[i] == 0x0)
			std::cout << "None" << std::endl;
		else
			this->p_cards[i]->PrintConsole();
	}
}

void		Player::GiveCard(Card* c, int idx)
{
	this->p_cards[idx] = c;
}