#include	"Game.h"

Game::Game(void) :
	p_players(4), p_round_goal(0)
{
	this->p_scores[0] = 0;
	this->p_scores[1] = 0;
}

Game::~Game(void)
{
}

bool		Game::Run()
{
	this->p_deck.Shuffle();
	if (this->Distribute())
	{
		// annonces
		this->p_trump = Card::eColor::Spade;	//	Ces deux variables seront
		this->p_round_goal = 120;				//  set par les annonces.

		return (true);
	}
	return (false);
}

bool		Game::Distribute()
{
	if (this->p_deck.GetSize() == 32)
	{
		this->p_players[0].GiveCard(this->p_deck.Pick(), 0);
		this->p_players[0].GiveCard(this->p_deck.Pick(), 1);
		this->p_players[0].GiveCard(this->p_deck.Pick(), 2);
		this->p_players[1].GiveCard(this->p_deck.Pick(), 0);
		this->p_players[1].GiveCard(this->p_deck.Pick(), 1);
		this->p_players[1].GiveCard(this->p_deck.Pick(), 2);
		this->p_players[2].GiveCard(this->p_deck.Pick(), 0);
		this->p_players[2].GiveCard(this->p_deck.Pick(), 1);
		this->p_players[2].GiveCard(this->p_deck.Pick(), 2);
		this->p_players[3].GiveCard(this->p_deck.Pick(), 0);
		this->p_players[3].GiveCard(this->p_deck.Pick(), 1);
		this->p_players[3].GiveCard(this->p_deck.Pick(), 2);

		this->p_players[0].GiveCard(this->p_deck.Pick(), 3);
		this->p_players[0].GiveCard(this->p_deck.Pick(), 4);
		this->p_players[1].GiveCard(this->p_deck.Pick(), 3);
		this->p_players[1].GiveCard(this->p_deck.Pick(), 4);
		this->p_players[2].GiveCard(this->p_deck.Pick(), 3);
		this->p_players[2].GiveCard(this->p_deck.Pick(), 4);
		this->p_players[3].GiveCard(this->p_deck.Pick(), 3);
		this->p_players[3].GiveCard(this->p_deck.Pick(), 4);

		this->p_players[0].GiveCard(this->p_deck.Pick(), 5);
		this->p_players[0].GiveCard(this->p_deck.Pick(), 6);
		this->p_players[0].GiveCard(this->p_deck.Pick(), 7);
		this->p_players[1].GiveCard(this->p_deck.Pick(), 5);
		this->p_players[1].GiveCard(this->p_deck.Pick(), 6);
		this->p_players[1].GiveCard(this->p_deck.Pick(), 7);
		this->p_players[2].GiveCard(this->p_deck.Pick(), 5);
		this->p_players[2].GiveCard(this->p_deck.Pick(), 6);
		this->p_players[2].GiveCard(this->p_deck.Pick(), 7);
		this->p_players[3].GiveCard(this->p_deck.Pick(), 5);
		this->p_players[3].GiveCard(this->p_deck.Pick(), 6);
		this->p_players[3].GiveCard(this->p_deck.Pick(), 7);
		return (true);
	}
	return (false);
}