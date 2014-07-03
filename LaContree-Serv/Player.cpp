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
	if (c != 0x0)
		this->p_cards[idx] = c;
}

const Card*		Player::ViewCard(unsigned int idx)
{
	if (idx >= 0 && idx <= 7)
		return (this->p_cards[idx]);
	return (0x0);
}

void			Player::MakeCall(std::pair<int, std::pair<int, Card::eColor>>& call)
{
	// Ici arrive l'input network pour les annonces. Le serveur aura un timeout de 2 minutes avant de
	// valider ou invalider l'annonce.
	std::cout << "Annonce du joueur : " << call.first << std::endl;
	std::cout << "Valeur :" << std::endl;
	std::cin >> call.second.first;
	if (call.second.first == 0)
	{
		std::cout << "Joueur " << call.first << " a passe." << std::endl;
		return ;
	}
	std::cout << "Couleur :" << std::endl;
	int	c;

	std::cin >> c;
	if (c == 0)
		call.second.second = Card::eColor::Spade;
	else if (c == 1)
		call.second.second = Card::eColor::Heart;
	else if (c == 2)
		call.second.second = Card::eColor::Diamond;
	else if (c == 3)
		call.second.second = Card::eColor::Club;
	else
	{
		std::cout << "Erreur de couleur, on considere que le mec a passe." << std::endl;
		call.second.first = 0;
	}
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