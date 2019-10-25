//
//  highscores.hpp
//  game testing
//
//  Created by Ahmad Refaat on 4/22/16.
//  Copyright © 2016 Ahmad Refaat. All rights reserved.
//

#ifndef highscores_hpp
#define highscores_hpp

#include <stdio.h>
#include "entity.hpp"
#pragma once
#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<iomanip>
#include<string>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<cctype>
#define width 900
#define height 900
#define boardw 350
#define boardh 130
#define space 50
#define boxw 700
#define boxh 670
using namespace std;
using namespace sf;

class highScores
{
public:
    
    highScores(int,int);
    void addUser(string name, int level, string diff);
    void display(int number, string diff, RenderWindow& );
    int search(string name, string diff);
    void choose(int&,RectangleShape,RenderWindow&,int&,Sprite&,Clock&);

private:
    
    RectangleShape easyRectangle;
    RectangleShape MediumRectangle;
    RectangleShape HardRectangle;

    
    Sprite easyButton ;
    Sprite mediumButton ;
    Sprite hardButton ;
    
    Texture easyTexture ;
    Texture mediumTexture ;
    Texture hardTexture ;

    
    string diff;
    fstream state;
   // fstream Ostate;

    struct user
    {
        string name;
        int level;
    };
    vector<user> list;
    void sort();
    string assigndiff(string diff);
    void first(string name, int level, string diff);
    void swap(user&,user&);
    void transfer(string diff);
    
};


#endif /* highscores_hpp */
