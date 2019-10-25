//
//  hints.cpp
//  game testing
//
//  Created by Ahmad Refaat on 5/7/16.
//  Copyright © 2016 Ahmad Refaat. All rights reserved.
//

#include "hints.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int totalmoves(game mygame)
{
	int x;
	x = mygame.getCount();
	return x;
}
int hints::numberofhints()
{
	return 3;
}
int hints::numberofmoves(int moves)
{

	if (moves > 35)
		return 0.2*moves;
	else
		return 0.3*moves;

}
void hints::generatehints(string s, int Tmoves, int movesleft)
{

	int x = 0, y;
	//cout << s;
	if (numberofmoves(Tmoves)  < movesleft)
		y = numberofmoves(Tmoves) - 1;
	else
		y = movesleft;

	while (x < y)
	{
		switch (s.at(x))
		{
		case 'r':
			help.push_back("right"); x++;
			break;
		case 'u':
			help.push_back("up"); x++;
			break;
		case 'd':
			help.push_back("down"); x++;
			break;
		case 'l':
			help.push_back("left"); x++;
			break;
		default: x++; y++;

		}
	}
}
void hints::printhint(int& x, RenderWindow& w, int movesleft, int Tmoves)
{

 
	Text t;
	Font font;
	if (!font.loadFromFile(resourcePath()+"sansation.ttf"))
	{
		cout << "no";
	}


	sf::Event event;
	while (w.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			w.close();
	}
	string H;
	int y;
	if (numberofmoves(Tmoves)  < movesleft)
		y = numberofmoves(Tmoves) - 1;
	else
		y = movesleft;


	if (x < y)
	{
        available= false ;
		//cout << "size:" << help.size() << endl << x;
		//cout << endl << x;
		H = help.at(x);
		//cout << endl << H;
		t.setFont(font);
		t.setCharacterSize(100);
		t.setColor(sf::Color::Black);
		t.setPosition(900, 550);
		t.setString(H);

       
		w.draw(t);

	}
    else
        available=true;

}





