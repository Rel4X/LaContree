#include	"CardsDeck.h"

CardsDeck::CardsDeck(void)
{
	this->p_cards.push_back(new Card(Card::eColor::Club, Card::eFigure::Ace));
	this->p_cards.push_back(new Card(Card::eColor::Club, Card::eFigure::King));
	this->p_cards.push_back(new Card(Card::eColor::Club, Card::eFigure::Queen));
	this->p_cards.push_back(new Card(Card::eColor::Club, Card::eFigure::Jack));
	this->p_cards.push_back(new Card(Card::eColor::Club, Card::eFigure::Ten));
	this->p_cards.push_back(new Card(Card::eColor::Club, Card::eFigure::Nine));
	this->p_cards.push_back(new Card(Card::eColor::Club, Card::eFigure::Eight));
	this->p_cards.push_back(new Card(Card::eColor::Club, Card::eFigure::Seven));

	this->p_cards.push_back(new Card(Card::eColor::Heart, Card::eFigure::Ace));
	this->p_cards.push_back(new Card(Card::eColor::Heart, Card::eFigure::King));
	this->p_cards.push_back(new Card(Card::eColor::Heart, Card::eFigure::Queen));
	this->p_cards.push_back(new Card(Card::eColor::Heart, Card::eFigure::Jack));
	this->p_cards.push_back(new Card(Card::eColor::Heart, Card::eFigure::Ten));
	this->p_cards.push_back(new Card(Card::eColor::Heart, Card::eFigure::Nine));
	this->p_cards.push_back(new Card(Card::eColor::Heart, Card::eFigure::Eight));
	this->p_cards.push_back(new Card(Card::eColor::Heart, Card::eFigure::Seven));

	this->p_cards.push_back(new Card(Card::eColor::Spade, Card::eFigure::Ace));
	this->p_cards.push_back(new Card(Card::eColor::Spade, Card::eFigure::King));
	this->p_cards.push_back(new Card(Card::eColor::Spade, Card::eFigure::Queen));
	this->p_cards.push_back(new Card(Card::eColor::Spade, Card::eFigure::Jack));
	this->p_cards.push_back(new Card(Card::eColor::Spade, Card::eFigure::Ten));
	this->p_cards.push_back(new Card(Card::eColor::Spade, Card::eFigure::Nine));
	this->p_cards.push_back(new Card(Card::eColor::Spade, Card::eFigure::Eight));
	this->p_cards.push_back(new Card(Card::eColor::Spade, Card::eFigure::Seven));

	this->p_cards.push_back(new Card(Card::eColor::Diamond, Card::eFigure::Ace));
	this->p_cards.push_back(new Card(Card::eColor::Diamond, Card::eFigure::King));
	this->p_cards.push_back(new Card(Card::eColor::Diamond, Card::eFigure::Queen));
	this->p_cards.push_back(new Card(Card::eColor::Diamond, Card::eFigure::Jack));
	this->p_cards.push_back(new Card(Card::eColor::Diamond, Card::eFigure::Ten));
	this->p_cards.push_back(new Card(Card::eColor::Diamond, Card::eFigure::Nine));
	this->p_cards.push_back(new Card(Card::eColor::Diamond, Card::eFigure::Eight));
	this->p_cards.push_back(new Card(Card::eColor::Diamond, Card::eFigure::Seven));
}

CardsDeck::~CardsDeck(void)
{
}

void			CardsDeck::PrintConsole()
{
	std::list<Card*>::iterator	is;
	std::list<Card*>::iterator	ie;

	is = this->p_cards.begin();
	ie = this->p_cards.end();
	for (; is != ie; ++is)
		(*is)->PrintConsole();
}

void			CardsDeck::Shuffle()
{
	std::vector<Card*>*				vec;
	std::list<Card*>::iterator		is, ie;
	std::vector<Card*>::iterator	vis, vie;

	vec = new std::vector<Card*>(this->GetSize(), 0x0);
	is = this->p_cards.begin();
	ie = this->p_cards.end();
	vis = vec->begin();
	vie = vec->end();
	for (; is != ie; ++is)
	{
		(*vis) = (*is);
		++vis;
	}
	this->p_cards.clear();
	RandomMachine::Init();
	std::random_shuffle(vec->begin(), vec->end());
	vis = vec->begin();
	for (; vis != vie; ++vis)
		this->p_cards.push_back((*vis));
	delete (vec);
}

void			CardsDeck::Cut()
{
	if (this->GetSize() == 32)
	{
		int								cutplace;
		std::list<Card*>				tmp;
		std::list<Card*>::iterator		is, ie;
		int								i;

		i = 0;
		cutplace = RandomMachine::Randomize(2, 31);
		is = this->p_cards.begin();
		std::cout << cutplace << std::endl;
		while (i < cutplace)
		{
			tmp.push_back(*is);
			++is;
			++i;
			this->p_cards.pop_front();
		}
		is = tmp.begin();
		ie = tmp.end();
		for (; is != ie; ++is)
			this->p_cards.push_back(*is);
	}
}

Card*			CardsDeck::Pick()
{
	Card*		c;

	c = this->p_cards.back();
	this->p_cards.pop_back();
	return (c);
}