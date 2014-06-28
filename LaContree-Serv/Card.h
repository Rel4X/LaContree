#pragma once

#include	<iostream>

class		Card
{
public:
	enum	eColor
	{
		Spade	= 0,
		Heart	= 1,
		Diamond	= 2,
		Club	= 3
	};

	enum	eFigure
	{
		Ace		= 0,
		King	= 1,
		Queen	= 2,
		Jack	= 3,
		Ten		= 4,
		Nine	= 5,
		Eight	= 6,
		Seven	= 7
	};

private:
	static const char*	p_eColorText[4];
	static const char*	p_eFigureText[8];

private:
	eColor		p_color;
	eFigure		p_figure;

public:
	Card(eColor, eFigure);
	~Card(void);

private:
	Card(void)	{ }

public:
	eColor			GetColor() const	{ return (this->p_color); }
	eFigure			GetFigure() const	{ return (this->p_figure); }

public:
	void			PrintConsole();
	
};

