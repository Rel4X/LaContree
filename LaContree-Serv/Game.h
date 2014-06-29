#pragma once

#include	<vector>
#include	<utility>
#include	<string.h>
#include	"CardsDeck.h"
#include	"CardRuler.h"
#include	"Player.h"

#define		TEAM_1					0
#define		TEAM_2					1
#define		GET_TEAM_ID(id)			(id / 2 == 0 ? 0 : 1)
#define		NOT_SPEAKING_TEAM(v)	(v == 1 ? 0 : 1)

class	Game
{
private:
	std::pair<int, Card::eColor>	p_call;						// L'annonce.
	CardsDeck						p_deck;
	CardRuler						p_ruler;					// Classe qui check les regles de la contree.
	std::vector<Player>				p_players;
	Card::eColor					p_trump;					// L'atout.
	unsigned char					p_speaking_team;			// La team qui a passe le contrat.
	unsigned int					p_round_goal;				// Score a atteindre sur ce round.
	unsigned int					p_scores[2];				// Score des deux equipes.
	Card*							p_current_fold[4];			// Cartes jouees sur la table.
	Card*							p_fold_history[2][8][4];	// Plis deja win.
	Card**							p_last_fold;				// Pointeur vers le dernier plis.
	unsigned int					p_dealer;					// Id du mec qui commence la game.
	unsigned int					p_beginer;					// Id du mec qui commence le round.
	unsigned int					p_turn;						// Id du mec a qui c'est le tour de jouer (== p_dealer au debut).
	Card::eColor					p_asked;					// Il s'agit de la couleur demandee sur le fold.

public:
	Game(void);
	~Game(void);

public:
	bool				Run();

private:
	void				PrintConsole();
	void				PrintBoard();
	void				PrintFoldHistory();
	bool				Distribute();
	void				AnnonceStep();
	bool				CheckPlayedCardValidity(const Player&, unsigned int);
	void				GoToNextPlayer();
	void				GoToNextDealer();
	void				UpdateScores(int);
	void				StoreFold(int, int);
	void				SetNewRound();
};

