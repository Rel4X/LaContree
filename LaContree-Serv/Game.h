#pragma once

#include	<vector>
#include	<utility>
#include	"CardsDeck.h"
#include	"Player.h"

class	Game
{
private:
	CardsDeck			p_deck;
	std::vector<Player>	p_players;
	Card::eColor		p_trump;
	unsigned int		p_round_goal;	// Score a atteindre sur cette main.
	unsigned int		p_scores[2];	// Score des deux equipes.

public:
	Game(void);
	~Game(void);

public:
	bool				Run();

private:
	bool				Distribute();
};

