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
	this->p_call.first = -2;
	this->p_call.second.first = 42;
	this->p_call.second.second = Card::eColor::Diamond;
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

	std::cout << "+------------------+" << std::endl;
	std::cout << "| Debut de la game |" << std::endl;
	std::cout << "+------------------+" << std::endl;

	gamefinished = false;
	this->p_deck.Shuffle();
	this->p_dealer = 0;			// Sera definit au hasard ... ou pas ..
	this->p_beginer = 0;		//
	this->p_turn = 0;			//
	this->p_master = -1;		// Personne a joue donc master -1.
	while (!gamefinished)
	{
		this->p_deck.Cut();
		if (this->Distribute())
		{
			std::cout << "+----------------+" << std::endl;
			std::cout << "| Debut du round |" << std::endl;
			std::cout << "+----------------+" << std::endl;
			std::cout << "Le dealer est le joueur numero : " << this->p_dealer << std::endl;
			std::cout << "Les scores sont de [0] : " << this->p_scores[0] << " [1] : " << this->p_scores[1] << std::endl;

			/* -- Les annonces commencent -- */
			std::cout << "+--------------------+" << std::endl;
			std::cout << "| Debut des annonces |" << std::endl;
			std::cout << "+--------------------+" << std::endl;
			if (this->AnnonceStep() == false)							//
				return (false);											// Si annonce Fail, on stop tout (pour le moment).
			this->p_trump = this->p_call.second.second;					// Si annonces success, on set les infos pour
			this->p_round_goal = this->p_call.second.first;				// la partie.
			this->p_speaking_team = GET_TEAM_ID(this->p_call.first);	// 
			// TODO: Checker ... si tout le monde a passe, faire un truc.
			
			this->p_turn = this->p_dealer;						// Le dealer commence.
			this->p_beginer = this->p_dealer;					//

			/* -- Le round commence -- */
			for (int j = 0; j < 8; ++j)				// Boucle du round.
			{	
				/* -- La main commence -- */
				std::cout << "+------------------+" << std::endl;
				std::cout << "| Debut de la main |" << std::endl;
				std::cout << "+------------------+" << std::endl;
				for (int i = 0; i < 4; ++i)			// Boucle du fold.
				{
					if (i == 0)
						std::cout << "Joueur " << this->p_turn << " commence." << std::endl;
					else
						std::cout << "Joueur " << this->p_turn << " joue." << std::endl;
					this->p_players[this->p_turn].PrintConsole();
					played_card_idx = this->p_players[this->p_turn].Play();				// L'input player vient de la.
					if (this->p_players[this->p_turn].ViewCard(played_card_idx) == 0x0)
					{
						std::cout << "Carte 0x0 ..." << std::endl;
						return (false);
					}
					
					if (this->CheckPlayedCardValidity(this->p_players[this->p_turn], this->p_turn, played_card_idx) == true)
					{
						played_card = this->p_players[this->p_turn].PlayCard(played_card_idx);	// On sort la carte du player.
						if (this->p_beginer == this->p_turn)			//
						{												//
							this->p_asked = played_card->GetColor();	// Si c'est la premiere carte jouee, on set la couleur.
							this->p_master = this->p_turn;				// et le joueur devient le maitre.
						}												//

						// TODO: Repenser la ligne de dessous pour que les cartes soient stockees dans l'ordre ou elles ont ete jouees.
						this->p_current_fold[this->p_turn] = played_card;			// On pose la carte sur la table.
					}
					else
					{
						std::cout << "Impossible de jouer cette carte : ";
						this->p_players[this->p_turn].ViewCard(played_card_idx)->PrintConsole();
						return (false);
					}
					
					this->PrintBoard();
					if (this->p_master != -1)
						this->p_master = this->p_ruler.CompareTwoCards(this->p_current_fold, this->p_asked, this->p_trump, this->p_master, this->p_turn);
					
					std::cout << "Le Maitre est ";
					this->p_current_fold[this->p_master]->PrintConsole();
					
					this->GoToNextPlayer();
				}
				// On voit qui a gagne le fold. (On doit pouvoir opti en ne se servant que du master)
				id_fold_winner = this->p_ruler.WhoWon(this->p_current_fold, this->p_asked, this->p_trump);
				if (j == 7)													//
					last_fold_winner_team = GET_TEAM_ID(id_fold_winner);	// Recupere la team qui fait la der.

				std::cout << "Joueur " << id_fold_winner << " gagne avec son ";
				this->p_current_fold[id_fold_winner]->PrintConsole();

				this->p_beginer = id_fold_winner;			//
				this->p_turn = id_fold_winner;				// On set le winner en beginer.
				this->p_master = -1;

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

void		Game::PrintCall()
{
	std::cout << "Annonce : " << this->p_call.second.first << " " 
		<< Card::eColorText[this->p_call.second.second] << std::endl;
	std::cout << "Par joueur No : " << this->p_call.first << std::endl << std::endl;;
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

void		Game::PrintWinnerCard(int id)
{
	std::cout << "Winner Card: " << std::endl;
	this->p_current_fold[id]->PrintConsole();
	std::cout << "---------" << std::endl;
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

bool		Game::AnnonceStep()
{
	// Premier int pour l'id du player, 2e int pour la valeur de l'annonce puis couleur de l'annonce.
	std::pair<int, std::pair<int, Card::eColor>>			player_call;

	player_call.second.first = -1;					// On init avec des valeurs random,
	player_call.second.second = Card::eColor::Club;	// et une couleur random.

	this->p_call.first = -1;						// Si id player a -1 c'est qu'aucune annonce n a ete faite.

	while (0x0b)
	{
		if (this->p_call.first == this->p_turn)
			break ;
		player_call.first = this->p_turn;						// On prepare le call pour le joueur adequat.
		this->p_players[this->p_turn].PrintConsole();			//
		this->p_players[this->p_turn].MakeCall(player_call);	// On recupere l'annonce du mec.
		if (this->CheckCallValidity(player_call) == false)		// On check sa validite.
		{
			std::cout << "Failed annonce" << std::endl;
			return (false);
		}
		this->GoToNextPlayer();									// On passe au joueur suivant.
	}
	std::cout << "Fin des annonces." << std::endl;
	this->PrintCall();
	return (true);
}

bool		Game::CheckCallValidity(const std::pair<int, std::pair<int, Card::eColor>>& call)
{
	if (this->CheckCallValueValidity(call.second.first) == false)
		return (false);
	if (this->p_call.first == -1)	// Premiere annonce a etre faite.
	{								// Meme si le mec a passe (call.second.first == 0).
		this->p_call.first = call.first;					// On set l'id du joueur qui annonce le premier.
		this->p_call.second.first = call.second.first;		// Ainsi que son annonce.
		this->p_call.second.second = call.second.second;	// ...
	}
	else
	{
		if (call.second.first == 0)							// Si le mec a passe,
			return (true);									// c'est ok mais on change rien.
		else
		{
			if (call.second.first > this->p_call.second.first)		// Si l'annonce est plus grande, 
			{
				this->p_call.first = call.first;					// On set la nouvelle annonce.
				this->p_call.second.first = call.second.first;
				this->p_call.second.second = call.second.second;
				return (true);
			}
			return (false);
		}
	}
}

bool		Game::CheckCallValueValidity(unsigned int value)
{
	if (value == 0 || (value % 10 == 0 && value >= 80 && value <= 170))
		return (true);
	return (false);
}

bool		Game::CheckPlayedCardValidity(const Player& p, unsigned int id, unsigned int c)
{
	if (this->p_beginer == this->p_turn)
		return (true);
	if (p.HasSome(this->p_asked))				// Est ce que le joueur a de la couleur demandee ?
	{
		if (this->p_asked == this->p_trump)		// Est ce que la couleur demandee est de l'atout ?
		{
			if (this->HasBetterThan(p, this->p_current_fold[this->p_master]->GetColor(), this->p_current_fold[this->p_master]->GetFigure()))
			{
				if (p.ViewCard(c)->GetColor() == this->p_trump
					&& this->p_ruler.IsFirstFigureHigher(p.ViewCard(c)->GetFigure(), this->p_current_fold[this->p_master]->GetFigure(), true))
				{
					return (true);
				}
				std::cout << "Le joueur a : La couleur demandee qui est l'atout, et il a mieux." << std::endl;
				return (false);
			}
			else
			{
				if (p.ViewCard(c)->GetColor() == this->p_trump)
					return (true);
				std::cout << "Le joueur a de la couleur demandee, qui est de l'atout, et n'a pas mieux. Il doit quand meme mettre de l'atout." << std::endl;
				return (false);
			}
		}
		else
		{
			if (p.ViewCard(c)->GetColor() == this->p_asked)
				return (true);
			std::cout << "Le joueur a de la couleur demandee." << std::endl;
			return (false);
		}
	}
	else
	{
		if (GET_TEAM_ID(id) == GET_TEAM_ID(this->p_master))
		{
			return (true);
		}
		else
		{
			if (p.HasSome(this->p_trump))
			{
				if (this->p_current_fold[this->p_master]->GetColor() == this->p_trump)	// On regarde si il y a de l'atout.
				{
					if (this->HasBetterThan(p, this->p_current_fold[this->p_master]->GetColor(), this->p_current_fold[this->p_master]->GetFigure()))
					{
						if (p.ViewCard(c)->GetColor() == this->p_trump
							&& this->p_ruler.IsFirstFigureHigher(p.ViewCard(c)->GetFigure(), this->p_current_fold[this->p_master]->GetFigure(), true))
						{
							return (true);
						}
						std::cout << "Le joueur n'a pas la couleur demandee et copain pas maitre. Joueur l a de l'atout. Et en plus il en a un meilleurs." << std::endl;
						return (false);
					}
					else
					{
						return (true);
					}
				}
				else
				{
					if (p.ViewCard(c)->GetColor() == this->p_trump)
						return (true);
					std::cout << "Le joueur n a pas la couleur. Copain pas maitre. Pas d'atout pose, et joueur en a." << std::endl;
					return (false);
				}
			}
			else
			{
				return (true);
			}
		}
	}
}

bool		Game::HasBetterThan(const Player& p, Card::eColor c, Card::eFigure f)
{
	const Card*	cd;
	bool		trump;

	trump = false;
	if (c == this->p_trump)
		trump = true;
	for (int i = 0; i < 8; ++i)
	{
		cd = p.ViewCard(i);
		if (c != 0x0)
		{
			if (cd->GetColor() == c)
			{
				if (this->p_ruler.IsFirstFigureHigher(cd->GetFigure(), f, trump))
					return (true);
			}
		}
	}
	return (false);
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
	unsigned char		score[2];

	score[TEAM_1] = this->p_ruler.CountScore(this->p_fold_history[TEAM_1], this->p_trump);	// Possible optimisation car pas
	score[TEAM_2] = this->p_ruler.CountScore(this->p_fold_history[TEAM_2], this->p_trump);	// necessaire de compter les 2 scores.
	score[der] += 10;

	std::cout << "+---------------------+" << std::endl;
	std::cout << "| Comptage des scores |" << std::endl;
	std::cout << "+---------------------+" << std::endl;
	std::cout << "Team 0 fait : " << (int)score[0] << std::endl;
	std::cout << "Team 1 fait : " << (int)score[1] << std::endl;
	std::cout << "Team " << (int)this->p_speaking_team << " avait annonce " << this->p_call.second.first << std::endl;

	if (score[this->p_speaking_team] >= this->p_round_goal)
		this->p_scores[this->p_speaking_team] += this->p_round_goal;
	else
		this->p_scores[NOT_SPEAKING_TEAM(this->p_speaking_team)] += 160;
}

void		Game::StoreFold(int winning_team, int round)
{
	for (int i = 0; i < 4; ++i)													//
	{																			//
		this->p_fold_history[winning_team][round][i] = this->p_current_fold[i];	//	On place les folds la ou il faut.
		this->p_current_fold[i] = 0x0;											//
	}																			//
	this->p_last_fold = this->p_fold_history[winning_team][round];				//
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