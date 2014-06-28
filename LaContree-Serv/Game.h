#pragma once

#include	<vector>
#include	<utility>
#include	<string.h>
#include	"CardsDeck.h"
#include	"Player.h"

#define		GET_TEAM_ID(id)			(id / 2 == 0 ? 0 : 1)

class	Game
{
private:
	CardsDeck						p_deck;
	std::vector<Player>				p_players;
	Card::eColor					p_trump;					// L'atout.
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
	bool				Distribute();
	bool				CheckPlayedCardValidity(const Player&, unsigned int);
	void				GoToNextPlayer();
};

