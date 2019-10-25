//
//  hints.hpp
//  game testing
//
//  Created by Ahmad Refaat on 5/7/16.
//  Copyright © 2016 Ahmad Refaat. All rights reserved.
//

#ifndef hints_hpp
#define hints_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
using namespace sf;
using namespace std;
class hints
{

public:


	int numberofhints();
	int numberofmoves(int);
	void  generatehints(string, int, int);
	void printhint(int&, RenderWindow&, int, int);
	int x = 0;
	bool hint = false;
	int num = 1;
	vector <string> help;
    bool available = true ;
    bool intial = true;




};
#endif /* hints_hpp */
