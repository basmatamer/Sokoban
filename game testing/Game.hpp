//
//  Game.hpp
//  game testing
//
//  Created by Ahmad Refaat on 4/21/16.
//  Copyright © 2016 Ahmad Refaat. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "tiles.hpp"
#include <iostream>
#include <sys/time.h>
#include <cstdlib>
#include <sstream>
#include <vector>
#include <queue>
#include <deque>
#include <string>
#include <fstream>
#include "music.hpp"
using namespace std ;



class game:public entity{
    
    
public:
    
    game();
    struct State {
        
        string state_str;
        string move_list;
        int lvlSize;
        int depth;
        int moves;
        int pushes;
        int total_cost;
        int hscore;
    };
    
    struct position {
        
        int x ;
        int y ;
        int pos ;
        
        
    };

    void intlGame();
    bool checkCol(Sprite,int,int);
    bool checkBox(Sprite,int,int,music&);
    int prevI , prevJ,cI,cJ;
    void undo(Sprite&,int,int);
    void view();
    Vector2f getP();
    int playerI,playerJ ;
    string sol;
	bool checkLoss(int);
    void updatelvl(int);
    int rows,cols;
    void drawGame(RenderWindow&);
    int getCount();
    void displayArray();
    void reset();
    void movePlayer(int,int,int,int);
    string as(State &);
    queue<State> gen_valid_states (const State&);
    int heuristics(const State& );
    void print_level(State&);
    bool is_goal(State&);
    string displaySolution(); 
	bool checkwin();
    int currentlvl=1;
    bool boxPushed = false ;
    void copyArray();
    void deleteArray();
    bool checkDifference();
    void buttonsGame(RenderWindow& , Clock& ,int ,int,int&,RectangleShape,Text& , Sprite& ,music&,int );

private:
    
   
    int count ;
    ifstream myInput;
    tiles myGame[20][20];
    int array[20][20];
    int oldarray[20][20];
    string solution ;
    string tempLevel ;
    vector<string>copies;
    bool mute = false ;
    
};



#endif /* Game_hpp */
