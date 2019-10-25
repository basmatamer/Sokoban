//
//  entity.hpp
//  myNewGame
//
//  Created by Ahmad Refaat on 3/20/16.
//  Copyright © 2016 Ahmad Refaat. All rights reserved.
//

#ifndef entity_hpp
#define entity_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <cmath>
#include "ResourcePath.hpp"
#include <cstdlib>
#include <functional>
#include <tgmath.h>
#include <deque>
#include <list>
#include <vector>
#include <unistd.h>
using namespace std;

class entity {
    
    
    
public:
    
    
    sf::RectangleShape rect ;
    sf::Sprite sprite ;
    sf::Text text ;
    sf::Texture texture;
    sf::Font font;
    
    
     int xfactor=320;
     int yfactor=128;
     int xSize=64;
     int ySize=64;
    
    private:
    
    
    
    
    
    
};

#endif /* entity_hpp */
