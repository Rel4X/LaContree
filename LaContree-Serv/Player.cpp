#include	"Player.h"

unsigned int	Player::p_nxt_id = 0;

Player::Player(void) :
	p_cards(8, 0x0)
{
	this->p_id = Player::p_nxt_id;
	++Player::p_nxt_id;
}

Player::~Player(void)
{
}

void			Player::PrintConsole()
{
	for (int i = 0; i < 8; ++i)
	{
		if (this->p_cards[i] == 0x0)
			std::cout << "None" << std::endl;
		else
			this->p_cards[i]->PrintConsole();
	}
}

void			Player::GiveCard(Card* c, int idx)
{
	this->p_cards[idx] = c;
}

const Card*		Player::ViewCard(unsigned int idx)
{
	if (idx >= 0 && idx <= 7)
		return (this->p_cards[idx]);
	return (0x0);
}

void			Player::MakeCall(std::pair<int, Card::eColor>& call)
{
	;
}

unsigned int	Player::Play()
{
	// C'est la qu'il y aura l'arrivee de l'Input network.
	// En attendant, je fais ca a la main.
	int		idx;	// L'index de la carte a jouer.

	std::cout << "*******" << std::endl;
	std::cin >> idx;
	if (idx >= 0 && idx <= 7)
		return (idx);
	return (0x0);
}

Card*			Player::PlayCard(unsigned int idx)
{
	Card*		card;

	card = this->p_cards[idx];
	this->p_cards[idx] = 0x0;
	return (card);
}