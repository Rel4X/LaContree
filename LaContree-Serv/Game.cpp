#include	"Game.h"

Game::Game(void) :
	p_players(4), p_round_goal(0), p_dealer(0),
	p_turn(0), p_last_fold(0)
{
	memset(this->p_current_fold, 0, sizeof(Card*) * 4);
	this->p_scores[0] = 0;
	this->p_scores[1] = 0;
	// Tableau de la mort !
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 8; ++j)
			for (int k = 0; k < 4; ++k)
				this->p_fold_history[i][j][k] = 0x0;
}

Game::~Game(void)
{
}

bool		Game::Run()
{
	this->p_deck.Shuffle();

	// Ici boucle principale, tant qu'aucune equipe n'a atteint 1000 points.
	// Ici, on coupe avant de distribuer.
	if (this->Distribute())
	{
		unsigned int	played_card_idx;
		Card*			played_card;

		this->p_dealer = 0;						// Sera definit au hasard ... ou pas ..
		this->p_beginer = 0;
		this->p_turn = 0;
		// annonces
		this->p_trump = Card::eColor::Spade;	//	Ces deux variables seront
		this->p_round_goal = 120;				//  set par les annonces.

		for (int j = 0; j < 8; ++j)
		{
			for (int i = 0; i < 4; ++i)
			{
				this->p_players[this->p_turn].PrintConsole();
				played_card_idx = this->p_players[this->p_turn].Play();				// L'input player vient de la.
				if (this->p_players[this->p_turn].ViewCard(played_card_idx) == 0x0)
					return (false);
				if (this->CheckPlayedCardValidity(this->p_players[this->p_turn], played_card_idx))
				{
					played_card = this->p_players[this->p_turn].PlayCard(played_card_idx);	// On sort la carte du player.
					if (this->p_beginer == this->p_turn)		// Si c'est la premiere carte jouee, on set la couleur.
						this->p_asked = played_card->GetColor();//
					this->p_current_fold[this->p_turn] = played_card;	// On pose la carte sur la table.
				}
				// else, redemander a jouer tant que carte invalide.
				this->GoToNextPlayer();
			}
			// Fin du round : On change le beginner pour que le gagnant du round joue en premier (on met son id dans p_turn).
			// On compte les scores.
			// Modifier la boucle en dessous pour ajouter le plis dans la bonne team, en fonction du player winner.
			
			for (int i = 0; i < 4; ++i)										//
				this->p_fold_history[0][j][i] = this->p_current_fold[i];	//	On place les folds la ou il faut.
			this->p_last_fold = this->p_fold_history[0][j];					//
		}
		// Ici on compte les points
		return (true);
	}
	return (false);
}

void		Game::PrintConsole()
{
	std::cout << "Scores are :"  << std::endl;
	std::cout << "Team 1 : " << this->p_scores[0] << std::endl;
	std::cout << "Team 2 : " << this->p_scores[1] << std::endl;
	std::cout << std::endl;
	std::cout << "Trump is : " << Card::eColorText[this->p_trump] << std::endl;
	std::cout << "Current fold is : " << std::endl;
	if (this->p_current_fold[0] == 0x0)
		std::cout << "None" << std::endl;
	else
		this->p_current_fold[0]->PrintConsole();
	if (this->p_current_fold[1] == 0x0)
		std::cout << "None" << std::endl;
	else
		this->p_current_fold[1]->PrintConsole();
	if (this->p_current_fold[2] == 0x0)
		std::cout << "None" << std::endl;
	else
		this->p_current_fold[2]->PrintConsole();
	if (this->p_current_fold[3] == 0x0)
		std::cout << "None" << std::endl;
	else
		this->p_current_fold[3]->PrintConsole();
	if (this->p_last_fold != 0x0)
	{
		std::cout << "Last fold : " << std::endl;
		this->p_last_fold[0]->PrintConsole();
		this->p_last_fold[1]->PrintConsole();
		this->p_last_fold[2]->PrintConsole();
		this->p_last_fold[3]->PrintConsole();
	}
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

bool		Game::CheckPlayedCardValidity(const Player& p, unsigned int c)
{
	if (this->p_turn == this->p_dealer)
		return (true);
	return (true);
}

void		Game::GoToNextPlayer()
{
	this->p_turn++;
	if (this->p_turn > 3)
		this->p_turn = 0;
}
