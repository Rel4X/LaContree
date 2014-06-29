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
	bool			gamefinished;
	unsigned int	played_card_idx;
	Card*			played_card;
	int				id_fold_winner;
	int				last_fold_winner_team;

	gamefinished = false;
	this->p_deck.Shuffle();
	this->p_dealer = 0;			// Sera definit au hasard ... ou pas ..
	this->p_beginer = 0;
	this->p_turn = 0;
	while (!gamefinished)
	{
		this->p_deck.Cut();
		if (this->Distribute())
		{
			// annonces
			this->p_trump = Card::eColor::Spade;	//	Ces deux variables seront
			this->p_round_goal = 120;				//  set par les annonces.
			this->p_speaking_team = TEAM_1;			//

			for (int j = 0; j < 8; ++j)				//	Boucle du round.
			{
				for (int i = 0; i < 4; ++i)			//	Boucle du fold.
				{
					this->p_players[this->p_turn].PrintConsole();
					played_card_idx = this->p_players[this->p_turn].Play();				// L'input player vient de la.
					if (this->p_players[this->p_turn].ViewCard(played_card_idx) == 0x0)
						return (false);
					if (this->CheckPlayedCardValidity(this->p_players[this->p_turn], played_card_idx))
					{
						played_card = this->p_players[this->p_turn].PlayCard(played_card_idx);	// On sort la carte du player.
						if (this->p_beginer == this->p_turn)							//
							this->p_asked = played_card->GetColor();					// Si c'est la premiere carte jouee, on set la couleur.
						// TODO: Repenser la ligne de dessous pour que les cartes soient stockees dans l'ordre ou elles ont ete jouees.
						this->p_current_fold[this->p_turn] = played_card;				// On pose la carte sur la table. PS:
					}
					// else, redemander a jouer tant que carte invalide.
					this->PrintBoard();
					this->GoToNextPlayer();
				}
				// On voit qui a gagne le fold.
				id_fold_winner = this->p_ruler.WhoWon(this->p_current_fold, this->p_asked, this->p_trump);
				if (j == 7)													//
					last_fold_winner_team = GET_TEAM_ID(id_fold_winner);	// Recupere la team qui fait la der.

				this->p_beginer = id_fold_winner;			//
				this->p_turn = id_fold_winner;				// On set le winner en beginer.

				this->StoreFold(GET_TEAM_ID(id_fold_winner), j);			// Range le plis courrant et nettoie la table.
			}
			this->UpdateScores(last_fold_winner_team);
			this->SetNewRound();
			// Check ici si la partie n'est pas terminee.
		}
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

void		Game::PrintBoard()
{
	std::cout << "----------------" << std::endl;
	std::cout << "Asked : " << Card::eColorText[this->p_asked] << std::endl;
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
	std::cout << "----------------" << std::endl;
}

void		Game::PrintFoldHistory()
{
	std::cout << "Printing fold history:" << std::endl;
	for (int i = 0; i < 2; ++i)
	{
		std::cout << "Team " << i + 1 << ":" << std::endl;
		for (int j = 0; j < 8; ++j)
		{
			for (int k = 0; k < 4; ++ k)
			{
				if (this->p_fold_history[i][j][k] != 0x0)
					this->p_fold_history[i][j][k]->PrintConsole();
			}
			std::cout << "========" << std::endl;
		}
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

void		Game::GoToNextDealer()
{
	this->p_dealer++;
	if (this->p_dealer > 3)
		this->p_dealer = 0;
}

void		Game::UpdateScores(int der)
{
	char		score[2];

	score[TEAM_1] = this->p_ruler.CountScore(this->p_fold_history[TEAM_1], this->p_trump);	// Possible optimisation car pas
	score[TEAM_2] = this->p_ruler.CountScore(this->p_fold_history[TEAM_2], this->p_trump);	// necessaire de compter les 2 scores.
	score[der] += 10;
	if (score[this->p_speaking_team] >= this->p_round_goal)
		this->p_scores[this->p_speaking_team] += this->p_round_goal;
	else
		this->p_scores[NOT_SPEAKING_TEAM(this->p_speaking_team)] += 160;
}

void		Game::StoreFold(int winning_team, int round)
{
	for (int i = 0; i < 4; ++i)																//
	{																						//
		this->p_fold_history[winning_team][round][i] = this->p_current_fold[i];				//	On place les folds la ou il faut.
		this->p_current_fold[i] = 0x0;														//
	}																						//
	this->p_last_fold = this->p_fold_history[winning_team][round];							//
}

void		Game::SetNewRound()
{
	this->GoToNextDealer();				// On deplace le dealer et
	this->p_beginer = this->p_dealer;	// on set pour qu'il commence
	this->p_turn = this->p_dealer;		// bien.
	for (int i = 0; i < 2; ++i)											//
	{																	//
		for (int j = 0; j < 8; ++j)										//
		{																// On reconstruit le deck en
			for (int k = 0; k < 4; ++ k)								// empilant les cartes du fold
			{															// history.
				if (this->p_fold_history[i][j][k] != 0x0)				//
					this->p_deck.Put(this->p_fold_history[i][j][k]);	//
				this->p_fold_history[i][j][k] = 0x0;					//
			}															//
		}																//
	}																	//
	this->p_last_fold = 0x0;		// On reset a 0 le pointer vers le last fold.
}