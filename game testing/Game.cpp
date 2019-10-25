//
//  Game.cpp
//  game testing
//
//  Created by Ahmad Refaat on 4/21/16.
//  Copyright © 2016 Ahmad Refaat. All rights reserved.
//

#include "Game.hpp"



game::game(){

    updatelvl(currentlvl);
    cout << currentlvl << endl ;
    
}

void game::displayArray(){
    
    for(int i=0 ; i<rows ; i++){
        for(int j=0 ; j<cols ; j++)
            cout<<array[j][i];
            cout<<endl ;
            }
 
    cout<<endl ;
}


void game::intlGame(){
    
    
    
    for(int i=0;i<rows;i++)
        for(int j=0 ;j<cols ; j++){
            myGame[i][j].setType(array[i][j],currentlvl);
            myGame[i][j].setPos(i, j,xfactor,yfactor);
        }
    
    
}



void game::drawGame(RenderWindow& window){
    
    
    for(int i=0;i<rows;i++)
        for(int j=0;j<cols;j++)
            window.draw(myGame[i][j].getSprite());

}

void game::reset(){
    
    for(int i=0;i<10;i++)
        for(int j=0 ;j<10 ; j++){
            array[i][j]=1;
        }
    rows=10;
    cols=10;
    
    intlGame();
}



bool game::checkCol(Sprite myPlayer,int i,int j){
    
    int xPos=(myPlayer.getPosition().x-xfactor)/xSize;
    int yPos=(myPlayer.getPosition().y-yfactor)/ySize;
    
    
    if(array[xPos+i][yPos+j]==1)
        return false ;
    
      return true ;
    
}

void game::deleteArray(){
    
    copies.erase(copies.end()-1);
    cout <<"After moving the size is: " <<copies.size() << endl ;

}

void game::copyArray(){
    
//    for(int i=0 ; i<rows; i++)
//        for(int j=0 ; j< cols ; j++)
//            oldarray[i][j]=array[i][j];
//   
//    for(int i=0 ; i<rows; i++){
//        for(int j=0 ; j< cols ; j++)
//          cout <<  oldarray[j][i];
//        cout << endl ;
//    }
//    cout << endl ;

    tempLevel="";
    for(int i=0 ; i< rows ; i++)
        for(int j=0 ; j<cols ; j++){
         
            tempLevel+=to_string(array[i][j]);
            //cout <<tempLevel;
        }
            
    int k=0 ;
    for(int i=0 ; i< rows ; i++)
        for(int j=0 ; j<cols ; j++)
           oldarray[i][j]=tempLevel.at(k++)-48 ;
    
//    
//        for(int i=0 ; i<rows; i++){
//            for(int j=0 ; j< cols ; j++)
//              cout <<  oldarray[j][i];
//            cout << endl ;
//        }
//        cout << endl ;
    
    copies.push_back(tempLevel);
    cout <<"After moving the size is: " <<copies.size() << endl ;

    
    
}
bool game::checkBox(Sprite myPlayer,int i,int j,music& mymusic){
    
    
    int xPos=(myPlayer.getPosition().x-xfactor)/xSize;
    int yPos=(myPlayer.getPosition().y-yfactor) /ySize;
    
    if(array[xPos+i][yPos+j]==2&&(array[xPos+i*2][yPos+j*2]==2||array[xPos+i*2][yPos+j*2]==5)){
        boxPushed=false ;
        return false ;

    }
    
   else if(array[xPos+i][yPos+j]==2&&array[xPos+i*2][yPos+j*2]!=1&&array[xPos+i*2][yPos+j*2]!=2)
    {

        if(array[xPos+i*2][yPos+j*2]==7){
            array[xPos+i][yPos+j]=0 ;
            array[xPos+i*2][yPos+j*2]=5;
            prevI=99;prevJ=99;
            cI=99; cJ=99;
            cout<<"Box arrived "<< endl;
            mymusic.inplace();
        }
        else
        {
            array[xPos+i][yPos+j]=0 ;
            array[xPos+i*2][yPos+j*2]=2;
            prevI=xPos+i;prevJ=yPos+j;
            cI=xPos+i*2; cJ=yPos+j*2;
           mymusic.moveBox();
        }
        intlGame();
       
     //   cout<<"Success";
        boxPushed=true ;
        return true ;

    }
    
    
   else  if((array[xPos+i][yPos+j]==2||array[xPos+i][yPos+j]==5)&&array[xPos+i*2][yPos+j*2]==1){
       boxPushed=false ;

       return false ;
   }
    
  else  if(array[xPos+i][yPos+j]==5&&(array[xPos+i*2][yPos+j*2]==7||array[xPos+i*2][yPos+j*2]==0))
    {

        if(array[xPos+i*2][yPos+j*2]==7)
        {
            
            array[xPos+i*2][yPos+j*2]=5;
            mymusic.inplace();
        }
        else
        {
            
            array[xPos+i*2][yPos+j*2]=2;
            mymusic.moveBox();
        }
        
        array[xPos+i][yPos+j]=7;

        intlGame();
        boxPushed=true ;
        return true ;

        
    }
    
  else if(array[xPos+i][yPos+j]==5){
      
      boxPushed=false ;
      return false ;
  
  }
    
    boxPushed=false ;
    return true ;
    
    
    
    
}

bool game::checkDifference(){
    
//    for(int i=0 ; i<rows; i++)
//        for(int j=0 ; j< cols ; j++)
//           if( array[i][j]!=oldarray[i][j])
//               return true ;

    if(copies.size()>1){
        cout <<"allowed to undo " <<endl ;
        return true;
    }
    
    return false ;
}


void game::undo(Sprite& myWalker ,int a,int b){
    
    
//    myWalker.setPosition(a*xSize+xfactor, b*ySize+yfactor);
//
//    for(int i=0 ; i<rows; i++)
//        for(int j=0 ; j< cols ; j++)
//            array[i][j]=oldarray[i][j];
//    
    int k=0;
    tempLevel = copies.back();
    copies.pop_back();
    
    for(int i=0 ; i<rows; i++)
        for(int j=0 ; j< cols ; j++)
        {
            array[i][j]=tempLevel.at(k++)-48;
            if(array[i][j]==9||array[i][j]==8)
            {
                a=i ; b =j;
            }
        }
    
    intlGame();
    myWalker.setPosition(a*xSize+xfactor, b*ySize+yfactor);

    
    cout <<"After undo the size is: " <<copies.size() << endl ;
    
}


Vector2f game::getP(){
    
    for(int i=0 ;i<rows;i++)
        for(int j=0 ;j<cols ;j++)
            if(array[i][j]==9){
                playerI=i;playerJ=j;
            }

    Vector2f pos ;
    pos.x=playerI*xSize+xfactor;
    pos.y=playerJ*ySize+yfactor;
    
    return pos;
    
    
    
}

bool game::checkLoss(int count)
{
	if (count <= 0 && checkwin() == false)
		return true;
	return false;



	/*
	char newDi;


	switch(direction){

	case 1: newDi='L';break;
	case 2: newDi='R';break;
	case 3: newDi='U';break;
	case 4: newDi='D';break;



	}*/
	//    if(count>0&&count<=sol.length()){
	//    if(newDi!=sol.at(count-1))
	//        cout<<"You lost"<<endl ;
	//     
	//        else
	//            cout <<"YOU can win"<< endl ;
	//    }

}

    

void game::updatelvl(int level){
    
    reset();
    if(level==1){
        myInput.open(resourcePath()+"lvl1.txt");
       
    }
    else if(level==2){
        myInput.open(resourcePath()+"lvl2.txt");
       

    }
    else if (level==3){
        myInput.open(resourcePath()+"lvl3.txt");
     

    }
    else if (level==4){
        myInput.open(resourcePath()+"lvl4.txt");
       
    }
    else if (level==5){
        myInput.open(resourcePath()+"lvl5.txt");
        
    }
    else if (level==6){
        myInput.open(resourcePath()+"lvl6.txt");
        
    }
    else if (level==7){
        myInput.open(resourcePath()+"lvl7.txt");
        
    }
    else if (level==8){
        myInput.open(resourcePath()+"lvl8.txt");
        
    }
    else if (level==9){
        myInput.open(resourcePath()+"lvl9.txt");
        
    }
    else if (level==10){
        myInput.open(resourcePath()+"lvl10.txt");
        
    }
    else if (level==11){
        myInput.open(resourcePath()+"lvl11.txt");
        
    }
    else if (level==12){
        myInput.open(resourcePath()+"lvl12.txt");
        
    }
    else if (level==13){
        myInput.open(resourcePath()+"lvl13.txt");
        
    }
    else if (level==14){
        myInput.open(resourcePath()+"lvl14.txt");
        
    }
    else if (level==15){
        myInput.open(resourcePath()+"lvl15.txt");
        
    }
    else if (level==16){
        myInput.open(resourcePath()+"lvl16.txt");
        
    }
    else if (level==17){
        myInput.open(resourcePath()+"lvl17.txt");
        
    }
    else if (level==18){
        myInput.open(resourcePath()+"lvl18.txt");
        
    }
    else if (level==19){
        myInput.open(resourcePath()+"lvl19.txt");
        
    }
    else if (level==20){
        myInput.open(resourcePath()+"lvl20.txt");
        
    }
    
    
    else if (level==21){
        myInput.open(resourcePath()+"lvl21.txt");
        
    }
    else if (level==22){
        myInput.open(resourcePath()+"lvl22.txt");
        
    }
    else if (level==23){
        myInput.open(resourcePath()+"lvl23.txt");
        
    }
    else if (level==24){
        myInput.open(resourcePath()+"lvl24.txt");
        
    }
    else if (level==25){
        myInput.open(resourcePath()+"lvl25.txt");
        
    }
    else if (level==26){
        myInput.open(resourcePath()+"lvl26.txt");
        
    }
    else if (level==27){
        myInput.open(resourcePath()+"lvl27.txt");
        
    }
    else if (level==28){
        myInput.open(resourcePath()+"lvl28.txt");
        
    }
    else if (level==29){
        myInput.open(resourcePath()+"lvl29.txt");
        
    }
    else if (level==30){
        myInput.open(resourcePath()+"lvl30.txt");
        
    }
    
    
    // displayArray();
    
    
    if(myInput.fail())
        return -1;
    myInput>>rows;myInput>>cols;

    for(int i=0;i<rows;i++)
        for(int j=0 ;j<cols ; j++){
            myInput>>array[j][i];
            
        }
    myInput>>sol;
    myInput.close();
    
    count=sol.length();
    currentlvl=level;
    intlGame();
    cout << currentlvl << endl ;
    copies.clear();
    copyArray();
}

int game::getCount(){
    return count ;
}


void game::movePlayer(int currentI,int currentJ ,int nextI,int nextJ){
    
    int currentPlayer = array[currentI][currentJ];
    int goalOrNot = array[currentI+nextI][currentJ+nextJ];
    
    if(goalOrNot==0)
        array[currentI+nextI][currentJ+nextJ]=9;
    else if (goalOrNot==7||goalOrNot==5)
        array[currentI+nextI][currentJ+nextJ]=8;
    
    if(currentPlayer==9)
        array[currentI][currentJ]=0;
    else if(currentPlayer==8)
        array[currentI][currentJ]=7;

	if (checkwin())
		cout << "you winnnnn";
    
}

bool game::is_goal(State &cur_state)
{
    bool goal = false;
    
    //if there are no empty goals
    if ((cur_state.state_str.find_first_of('7')) == string::npos)
    {
        //check if there are boxes not on goal
        if ((cur_state.state_str.find_first_of('2')) == string::npos)
        {
            if ((cur_state.state_str.find_first_of('8')) == string::npos)
                
                goal = true;
        }
    }
    return goal;
}


void game::print_level(State &currentState)
{
    int k=0 ;
    for(int i=0 ; i<currentState.lvlSize ;i++){
        for(int j=0 ; j<currentState.lvlSize ; j++)
            cout<< currentState.state_str.at(k++);
        
        cout<<endl ;
    }
    
    
}

int game::heuristics(const State& cur_state){
    
    position box ;
    int lvlSize = cur_state.lvlSize;
    int score=0 ;
    vector<position>boxes ;
    string map = cur_state.state_str;
    
    for(int i=0 ; i<map.length();i++)
    {
        if(map.at(i)=='2')
        {
            box.pos=i;
            box.y=i/lvlSize;
            box.x= i - box.y*lvlSize ;
            boxes.push_back(box);
            
        }
    }
    
    
    for(int i=0 ; i < boxes.size() ; i++ )
    {
        position currentBox = boxes[i];
        
        bool northWall = false;
        bool eastWall = false;
        bool southWall = false;
        bool westWall = false;
        bool cornered = false;
        
        
        
        if(map.at(currentBox.pos-lvlSize)=='1')
            northWall=true ;
        if(map.at(currentBox.pos+lvlSize)=='1')
            southWall=true ;
        if(map.at(currentBox.pos-1)=='1')
            westWall=true ;
        if(map.at(currentBox.pos+1)=='1')
            eastWall=true ;
        
        
        
        if (northWall && eastWall)
        {
            cornered = true;
        }
        
        else if (northWall && westWall)
        {
            cornered = true;
        }
        
        else if (southWall && eastWall)
        {
            cornered = true;
        }
        
        else if (southWall && westWall)
        {
            cornered = true;
        }
        
        
        if (cornered)
        {
            score += 1000;
        }
        
        else
        {
            
            
            if(northWall){
                
                bool safe = false;
                bool eastCorner = false;
                bool westCorner = false;
                
                
                
                for(int i= (currentBox.pos+1) ; i < ((currentBox.y+1)*lvlSize) ; i++)
                {
                    
                    if(map.at(i)=='7'||map.at(i)=='5'||map.at(i)=='8')
                    {    safe=true ;
                        break;
                    }
                    
                    if(map.at(i)=='1'&&map.at(i-lvlSize)=='1')
                    {
                        eastCorner=true;
                        break;
                    }
                    
                }
                
                
                
                for(int i= (currentBox.pos-1) ; i >= ((currentBox.y)*lvlSize) ; i--)
                {
                    
                    if(map.at(i)=='7'||map.at(i)=='5'||map.at(i)=='8')
                    {    safe=true ;
                        break;
                    }
                    
                    if(map.at(i)=='1'&&map.at(i-lvlSize)=='1')
                    {
                        westCorner=true;
                        break;
                    }
                    
                }
                
                
                if(!safe){
                    
                    if(eastCorner&&westCorner)
                        score+=1000 ;
                    
                }
                
                
            }
            
            
            if(southWall){
                bool safe = false;
                bool eastCorner = false;
                bool westCorner = false;
                
                
                
                
                for(int i= (currentBox.pos+1) ; i < ((currentBox.y+1)*lvlSize) ; i++)
                {
                    
                    if(map.at(i)=='7'||map.at(i)=='5'||map.at(i)=='8')
                    {    safe=true ;
                        break;
                    }
                    
                    if(map.at(i)=='1'&&map.at(i+lvlSize)=='1')
                    {
                        eastCorner=true;
                        break;
                    }
                    
                }
                
                
                
                for(int i= (currentBox.pos-1) ; i >= ((currentBox.y)*lvlSize) ; i--)
                {
                    
                    if(map.at(i)=='7'||map.at(i)=='5'||map.at(i)=='8')
                    {    safe=true ;
                        break;
                    }
                    
                    if(map.at(i)=='1'&&map.at(i+lvlSize)=='1')
                    {
                        westCorner=true;
                        break;
                    }
                    
                }
                
                
                if(!safe){
                    
                    if(eastCorner&&westCorner)
                        score+=1000 ;
                    
                }
                
                
            }
            
            if(eastWall){
                
                
                bool safe = false;
                bool northCorner = false;
                bool southCorner = false;
                
                
                
                for(int i= box.pos-lvlSize ; i >= 0 ; i-=lvlSize){
                    
                    
                    if(map.at(i)=='7'||map.at(i)=='5'||map.at(i)=='8')
                    {    safe=true ;
                        break;
                    }
                    
                    if(map.at(i)=='1'&&map.at(i+1)=='1')
                    {
                        northCorner=true;
                        break;
                    }
                    
                    
                }
                
                
                for(int i= box.pos+lvlSize ; i < map.length() ; i+=lvlSize){
                    
                    
                    if(map.at(i)=='7'||map.at(i)=='5'||map.at(i)=='8')
                    {    safe=true ;
                        break;
                    }
                    
                    if(map.at(i)=='1'&&map.at(i+1)=='1')
                    {
                        southCorner=true;
                        break;
                    }
                    
                    
                }
                
                
                
                if(!safe){
                    
                    if(northCorner&&southCorner)
                        score+=1000;
                    
                }
                
                
            }
            
            if(westWall){
                
                bool safe = false;
                bool northCorner = false;
                bool southCorner = false;
                
                
                
                for(int i= box.pos-lvlSize ; i >= 0 ; i-=lvlSize){
                    
                    
                    if(map.at(i)=='7'||map.at(i)=='5'||map.at(i)=='8')
                    {    safe=true ;
                        break;
                    }
                    
                    if(map.at(i)=='1'&&map.at(i-1)=='1')
                    {
                        northCorner=true;
                        break;
                    }
                    
                    
                }
                
                
                for(int i= box.pos+lvlSize ; i < map.length() ; i+=lvlSize){
                    
                    
                    if(map.at(i)=='7'||map.at(i)=='5'||map.at(i)=='8')
                    {    safe=true ;
                        break;
                    }
                    
                    if(map.at(i)=='1'&&map.at(i-1)=='1')
                    {
                        southCorner=true;
                        break;
                    }
                    
                    
                }
                
                
                
                if(!safe){
                    
                    if(northCorner&&southCorner)
                        score+=1000;
                }
                
            }
            
            
        }
        
        
        
    }
    
    return score;
    
    
}


queue<game::State> game::gen_valid_states (const State &cur_state)
{
    queue<State> valid_moves;
    stringstream ss(cur_state.state_str);
    vector< std::vector<char> > new_level_map;
    State new_state;
    std::string line;
    bool found = true;
    char player, box_move;
    int x, y, counter = 0, MOVE_COST = 1, PUSH_COST = 1;
    int playerPosition ;
    int lvlSize = cur_state.lvlSize;
    
    string Map=cur_state.state_str ;
    string newMap ;
    
    
    std::vector< std::vector<char> > level_map;
    
    playerPosition=cur_state.state_str.find('9');
    if(playerPosition==string::npos)
    {
        playerPosition=cur_state.state_str.find('8');
        if(playerPosition==string::npos)
            found=false;
        
    }
    
    if(found){
        y=playerPosition/cur_state.lvlSize;
        x= playerPosition - (y*cur_state.lvlSize);
        player=Map.at(playerPosition);
        
    }
    
    
    
    
    char north = Map.at(playerPosition-lvlSize);
    
    switch (north)
    {
            
        case '0':
            
            newMap=Map;
            newMap.replace(playerPosition-lvlSize, 1, "9");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            //update state stats
            new_state.move_list.append("u, ");
            new_state.depth++;
            new_state.moves++;
            
            new_state.total_cost += MOVE_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            valid_moves.push(new_state);
            break;
            
            
        case '7':
            newMap=Map;
            newMap.replace(playerPosition-lvlSize, 1, "8");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            
            
            new_state = cur_state;
            new_state.state_str = newMap;
            
            
            
            new_state.move_list.append("u, ");
            new_state.depth++;
            new_state.moves++;
            
            new_state.total_cost += MOVE_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            valid_moves.push(new_state);
            break;
            
            
        case '2':
            
            newMap=Map;
            newMap.replace(playerPosition-lvlSize, 1, "9");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            
            
            box_move = newMap.at(playerPosition - 2*lvlSize);
            
            
            if (box_move == '1')
                break;
            else if (box_move == '2')
                break;
            else if (box_move == '5')
                break;
            
            else if (box_move == '0')
            {
                newMap.replace(playerPosition-2*lvlSize, 1, "2");
                
            }
            
            else if (box_move == '7')
            {
                newMap.replace(playerPosition-2*lvlSize, 1, "5");
                
            }
            else
                break;
            
            
            new_state = cur_state;
            new_state.state_str = newMap;
            
            
            
            new_state.move_list.append("u, ");
            new_state.depth++;
            new_state.pushes++;
            
            new_state.total_cost += PUSH_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            valid_moves.push(new_state);
            break;
            
            
            
        case '5':
            
            newMap=Map;
            newMap.replace(playerPosition-lvlSize, 1, "8");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            box_move = newMap.at(playerPosition - 2*lvlSize);
            
            
            
            //if north of box is a wall or another box
            if (box_move == '1')
                break;
            else if (box_move == '2')
                break;
            else if (box_move == '5')
                break;
            //if north of box is an empty floor
            else if (box_move == '0')
            {
                newMap.replace(playerPosition-2*lvlSize, 1, "2");
            }
            //if north of box is an empty goal
            else if (box_move == '7')
            {
                newMap.replace(playerPosition-2*lvlSize, 1, "5");
            }
            else
                break;
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            
            //update state stats
            new_state.move_list.append("u, ");
            new_state.depth++;
            new_state.pushes++;
            
            new_state.total_cost += PUSH_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            
            valid_moves.push(new_state);
            break;
            //move to wall
        case '1':
            break;
        default:
            break;
    }
    
    
    char east = Map.at(playerPosition+1);
    
    switch (east)
    {
            //move to empty spot
        case '0':
            
            newMap=Map;
            newMap.replace(playerPosition+1, 1, "9");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            //update state stats
            new_state.move_list.append("r, ");
            new_state.depth++;
            new_state.moves++;
            
            new_state.total_cost += MOVE_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            
            valid_moves.push(new_state);
            break;
            
            //move to empty goal
        case '7':
            newMap=Map;
            newMap.replace(playerPosition+1, 1, "8");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            
            //update state stats
            new_state.move_list.append("r, ");
            new_state.depth++;
            new_state.moves++;
            
            new_state.total_cost += MOVE_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            valid_moves.push(new_state);
            break;
            
            //move to box on floor
        case '2':
            
            newMap=Map;
            newMap.replace(playerPosition+1, 1, "9");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            
            //adjusting for box tile and tile north of box
            box_move = newMap.at(playerPosition +2);
            
            //if north of box is a wall or another box
            if (box_move == '1')
                break;
            else if (box_move == '2')
                break;
            else if (box_move == '5')
                break;
            //if north of box is an empty floor
            else if (box_move == '0')
            {
                newMap.replace(playerPosition+2, 1, "2");
                
            }
            //if north of box is an empty goal
            else if (box_move == '7')
            {
                newMap.replace(playerPosition+2, 1, "5");
                
            }
            else
                break;
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            
            //update state stats
            new_state.move_list.append("r, ");
            new_state.depth++;
            new_state.pushes++;
            
            new_state.total_cost += PUSH_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            valid_moves.push(new_state);
            break;
            
            
            //move to box on goal
        case '5':
            
            newMap=Map;
            newMap.replace(playerPosition+1, 1, "8");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            box_move = newMap.at(playerPosition +2);
            
            
            //if north of box is a wall or another box
            if (box_move == '1')
                break;
            else if (box_move == '2')
                break;
            else if (box_move == '5')
                break;
            //if north of box is an empty floor
            else if (box_move == '0')
            {
                newMap.replace(playerPosition+2, 1, "2");
            }
            //if north of box is an empty goal
            else if (box_move == '7')
            {
                newMap.replace(playerPosition+2, 1, "5");
            }
            else
                break;
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            
            //update state stats
            new_state.move_list.append("r, ");
            new_state.depth++;
            new_state.pushes++;
            
            new_state.total_cost += PUSH_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            
            valid_moves.push(new_state);
            break;
            //move to wall
        case '1':
            break;
        default:
            break;
            
    }
    
    
    
    char south = Map.at(playerPosition+lvlSize);
    switch (south)
    {
            //move to empty spot
        case '0':
            
            newMap=Map;
            newMap.replace(playerPosition+lvlSize, 1, "9");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            //update state stats
            new_state.move_list.append("d, ");
            new_state.depth++;
            new_state.moves++;
            
            new_state.total_cost += MOVE_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            valid_moves.push(new_state);
            break;
            
            //move to empty goal
        case '7':
            newMap=Map;
            newMap.replace(playerPosition+lvlSize, 1, "8");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            
            //update state stats
            new_state.move_list.append("d, ");
            new_state.depth++;
            new_state.moves++;
            
            new_state.total_cost += MOVE_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            valid_moves.push(new_state);
            break;
            
            //move to box on floor
        case '2':
            
            newMap=Map;
            newMap.replace(playerPosition+lvlSize, 1, "9");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            
            //adjusting for box tile and tile north of box
            box_move = newMap.at(playerPosition + 2*lvlSize);
            
            //if north of box is a wall or another box
            if (box_move == '1')
                break;
            else if (box_move == '2')
                break;
            else if (box_move == '5')
                break;
            //if north of box is an empty floor
            else if (box_move == '0')
            {
                newMap.replace(playerPosition+2*lvlSize, 1, "2");
                
            }
            //if north of box is an empty goal
            else if (box_move == '7')
            {
                newMap.replace(playerPosition+2*lvlSize, 1, "5");
                
            }
            else
                break;
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            
            //update state stats
            new_state.move_list.append("d, ");
            new_state.depth++;
            new_state.pushes++;
            
            new_state.total_cost += PUSH_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            valid_moves.push(new_state);
            break;
            
            
            //move to box on goal
        case '5':
            
            newMap=Map;
            newMap.replace(playerPosition+lvlSize, 1, "8");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            box_move = newMap.at(playerPosition + 2*lvlSize);
            
            
            
            
            //if north of box is a wall or another box
            if (box_move == '1')
                break;
            else if (box_move == '2')
                break;
            else if (box_move == '5')
                break;
            //if north of box is an empty floor
            else if (box_move == '0')
            {
                newMap.replace(playerPosition+2*lvlSize, 1, "2");
            }
            //if north of box is an empty goal
            else if (box_move == '7')
            {
                newMap.replace(playerPosition+2*lvlSize, 1, "5");
            }
            else
                break;
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            
            //update state stats
            new_state.move_list.append("d, ");
            new_state.depth++;
            new_state.pushes++;
            
            new_state.total_cost += PUSH_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            valid_moves.push(new_state);
            break;
            //move to wall
        case '1':
            break;
        default:
            break;
    }
    
    
    
    char west = Map.at(playerPosition-1);
    switch (west)
    {
            //move to empty spot
        case '0':
            
            newMap=Map;
            newMap.replace(playerPosition-1, 1, "9");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            //update state stats
            new_state.move_list.append("l, ");
            new_state.depth++;
            new_state.moves++;
            
            new_state.total_cost += MOVE_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            valid_moves.push(new_state);
            break;
            
            //move to empty goal
        case '7':
            newMap=Map;
            newMap.replace(playerPosition-1, 1, "8");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            
            //update state stats
            new_state.move_list.append("l, ");
            new_state.depth++;
            new_state.moves++;
            
            new_state.total_cost += MOVE_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            
            valid_moves.push(new_state);
            break;
            
            //move to box on floor
        case '2':
            
            newMap=Map;
            newMap.replace(playerPosition-1, 1, "9");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            
            //adjusting for box tile and tile north of box
            box_move = newMap.at(playerPosition - 2 );
            
            //if north of box is a wall or another box
            if (box_move == '1')
                break;
            else if (box_move == '2')
                break;
            else if (box_move == '5')
                break;
            //if north of box is an empty floor
            else if (box_move == '0')
            {
                newMap.replace(playerPosition-2, 1, "2");
                
            }
            //if north of box is an empty goal
            else if (box_move == '7')
            {
                newMap.replace(playerPosition-2, 1, "5");
                
            }
            else
                break;
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            
            //update state stats
            new_state.move_list.append("l, ");
            new_state.depth++;
            new_state.pushes++;
            
            new_state.total_cost += PUSH_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            
            valid_moves.push(new_state);
            break;
            
            
            //move to box on goal
        case '5':
            
            newMap=Map;
            newMap.replace(playerPosition-1, 1, "8");
            (player == '9') ? newMap.replace(playerPosition, 1, "0") : newMap.replace(playerPosition, 1, "7") ;
            
            box_move = newMap.at(playerPosition - 2 );
            
            
            //if north of box is a wall or another box
            if (box_move == '1')
                break;
            else if (box_move == '2')
                break;
            else if (box_move == '5')
                break;
            //if north of box is an empty floor
            else if (box_move == '0')
            {
                newMap.replace(playerPosition-2, 1, "2");
            }
            //if north of box is an empty goal
            else if (box_move == '7')
            {
                newMap.replace(playerPosition-2, 1, "5");
            }
            else
                break;
            
            //create and update new state
            new_state = cur_state;
            new_state.state_str = newMap;
            
            
            //update state stats
            new_state.move_list.append("l, ");
            new_state.depth++;
            new_state.pushes++;
            
            new_state.total_cost += PUSH_COST;
            new_state.hscore = heuristics(new_state);
            new_state.hscore += new_state.total_cost;
            
            
            
            valid_moves.push(new_state);
            break;
            //move to wall
        case '1':
            break;
        default:
            break;
    }
    return valid_moves;
}


string game::as(State &initial_state)
{
    deque<State> open;
    vector<State> closed;
    
    State current_state;
    string solution ;
    //push first state into queue
    open.push_back(initial_state);
    while (!open.empty())
    {
        //take N from OPEN
        current_state = open.front();
        open.pop_front();
        //push N onto CLOSED
        closed.push_back(current_state);
        
        //print out in case a long time is taken and wondering if it froze
        if ((closed.size() % 5000) == 0)
            std::cout << "...explored "<< closed.size() <<" nodes..."<<std::endl;
        
        //if found, set report node to current node, set explored count to closed list size
        if (is_goal(current_state))
        {
            solution = current_state.move_list;
            
            open.pop_front();
            break;
        }
        
        //generate valid states
        queue<State> valid_states;
        valid_states = gen_valid_states(current_state);
        deque<State>::iterator it;
        vector<State>::iterator itr;
        
        //while queue is not empty of states
        while (!valid_states.empty())
        {
            bool already_seen = false;
            bool inserted = false;
            State temp_state = valid_states.front();
            //check if state has already been seen on open list
            for (it = open.begin(); it != open.end(); it++)
            {
                if (it->state_str == temp_state.state_str)
                {
                    already_seen = true;
                    break;
                }
            }
            //check if state has already been seen on closed list
            for (itr = closed.begin(); itr != closed.end(); itr++)
            {
                if (itr->state_str == temp_state.state_str)
                {
                    already_seen = true;
                    break;
                }
            }
            //if not duplicate, then add state to open queue
            if (!already_seen)
            {
                
                //add to beginning of node with greater total cost
                //used to maintain generated node order
                for (it = open.begin(); it != open.end(); it++)
                {
                    //priority of lowest hscore first
                    if (it->hscore > temp_state.hscore)
                    {
                        open.insert(it, temp_state);
                        inserted = true;
                        break;
                    }
                }
                //if no node has greater priority, push back
                if (!inserted)
                    open.push_back(temp_state);
            }
            
            
            valid_states.pop();
        }
    }
    
    return solution;
} //SearchStat as(State &initial_state, int hfchoice)

string game::displaySolution(){
    
    timeval start, end;
    long sec, microsec;
    int level_size;
    string input_level= "";
    
    
    
    level_size=rows;
    
    for(int i=0 ; i< level_size ; i++)
        for(int j=0 ; j<level_size ; j++)
            input_level+=to_string(array[j][i]);
    
    
    State init_state;
    init_state.state_str = input_level;
    init_state.move_list = "";
    init_state.moves = init_state.pushes = 0;
    init_state.lvlSize = level_size;
    
    
    print_level(init_state); cout << endl ;
    gettimeofday(&start, NULL);
    solution = as(init_state);
    gettimeofday(&end, NULL);
    
    cout << solution << endl ;
    
    cout << "  Actual run time: ";
    sec = end.tv_sec - start.tv_sec;
    microsec = end.tv_usec - start.tv_usec;
    cout << (sec + (microsec/1000000.0))<< " seconds" << endl;
	return solution;
    
}
bool game::checkwin()
{
	bool flag = true;
	for (int y = 0; y < rows; y++)
	for (int x = 0; x < cols; x++)
	{
		if (array[y][x] == 7 || array[y][x] == 8 || array[y][x] == 2)
			flag = false;
	}

	return flag;
}


void game::buttonsGame(RenderWindow& window , Clock& clock, int xWindow , int yWindow,int& buttonOptions,RectangleShape mouse,Text& words, Sprite& speechBubble, music& myMusic,int gameCount){
    
    
    RectangleShape hintsRect;
    RectangleShape replayRect;
    RectangleShape resetRect ;
    RectangleShape soundRect ;
    
    RectangleShape replayWinRect;
    RectangleShape nextRect;

    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        cout <<"NO"<< endl;
    }
    
    Text winText ;
    winText.setString("You Won!");
    winText.setFont(font);
    winText.setCharacterSize(60);
    winText.setPosition(20, 300);
    
    
    Text loseText ;
    loseText.setString("You Lost!");
    loseText.setFont(font);
    loseText.setCharacterSize(60);
    loseText.setPosition(20, 300);
    
    hintsRect.setSize(Vector2f(90,90));
    replayRect.setSize(Vector2f(75,75));
    resetRect.setSize(Vector2f(75,75));
    soundRect.setSize(Vector2f(80,80));
    
    
    replayWinRect.setSize(Vector2f(75,75));
    nextRect.setSize(Vector2f(75,75));

    
    sf::Texture test;
    if (!test.loadFromFile(resourcePath() + "hints.png")) {
        cout << "NO" << endl ;
    }
    
    sf::Sprite testSprite(test);
    testSprite.setPosition(xWindow-100, yWindow-100);
    
    
    
    
    sf::Texture replayTexture;
    if (!replayTexture.loadFromFile(resourcePath() + "replay.png")) {
        cout << "NO" << endl ;
    }
    
    sf::Sprite replay(replayTexture);
    replay.setPosition(xWindow-180, yWindow-90);
    
    
    sf::Texture restartTexture;
    if (!restartTexture.loadFromFile(resourcePath() + "reset.png")) {
        cout << "NO" << endl ;
    }
    
    sf::Sprite restart(restartTexture);
    restart.setPosition(xWindow-276, yWindow-90);
    
    
    sf::Texture sound;
    if (!sound.loadFromFile(resourcePath() + "soundOn.png")) {
        cout << "NO" << endl ;
    }
    
    sf::Sprite soundB;
    soundB.setPosition(xWindow-374, yWindow-90);
    
    
    sf::Texture soundoff;
    if (!soundoff.loadFromFile(resourcePath() + "soundOff.png")) {
        cout << "NO" << endl ;
    }
    
   
    
    sf::Texture nextTexture;
    if (!nextTexture.loadFromFile(resourcePath() + "next.png")) {
        cout << "NO" << endl ;
    }
    
    sf::Sprite next(nextTexture);
    next.setPosition(150, 400);
    
    
    sf::Sprite replayWin(replayTexture);
    replayWin.setPosition(50, 400);
    

    
    hintsRect.setPosition(testSprite.getPosition());
    replayRect.setPosition(replay.getPosition());
    resetRect.setPosition(restart.getPosition());
    soundRect.setPosition(soundB.getPosition());
    replayWinRect.setPosition(replayWin.getPosition());
    nextRect.setPosition(next.getPosition());
    
    
    if(myMusic.volume>0)
        mute=false;
    
    else
        mute=true;
    
    if(mute)
    {
        soundB.setTexture(soundoff);
    }
    else
        soundB.setTexture(sound);
    
    
    if(mouse.getGlobalBounds().intersects(hintsRect.getGlobalBounds())){
        
        speechBubble.setPosition(170, yWindow-200);
        words.setPosition(230, yWindow-180);
        window.draw(speechBubble);
        words.setString("Want Hints?");
        words.setCharacterSize(90);

        window.draw(words);
    }
   
    if(mouse.getGlobalBounds().intersects(replay.getGlobalBounds())){
       
        speechBubble.setPosition(170, yWindow-200);
        words.setPosition(220, yWindow-200);
        window.draw(speechBubble);
        words.setString("Restart level?");
        words.setCharacterSize(90);

        window.draw(words);

        
    }

    if(mouse.getGlobalBounds().intersects(restart.getGlobalBounds())){
        
        speechBubble.setPosition(170, yWindow-200);
        words.setPosition(220, yWindow-200);
        window.draw(speechBubble);
        words.setString("Initialize all?");
        words.setCharacterSize(90);

        window.draw(words);

        
    }

    if(mouse.getGlobalBounds().intersects(soundRect.getGlobalBounds())){
       
        speechBubble.setPosition(170, yWindow-200);
        words.setPosition(220, yWindow-200);
        window.draw(speechBubble);
        if(!mute){
        words.setString("Click to mute");
            words.setCharacterSize(90);
        }
        else{
            words.setString("Click to Umnute");
            words.setCharacterSize(80);
        }
        window.draw(words);

    
    
    }

    if(checkwin())
    {
        
        
        window.draw(next);
        window.draw(replayWin);
        window.draw(winText);
        if(mouse.getGlobalBounds().intersects(nextRect.getGlobalBounds())){
            
            speechBubble.setPosition(170, yWindow-200);
            words.setPosition(220, yWindow-200);
            window.draw(speechBubble);
            words.setString("Next Level");
            words.setCharacterSize(120);
            window.draw(words);
            
            
        }
        
        
        if(mouse.getGlobalBounds().intersects(replayWinRect.getGlobalBounds())){
            speechBubble.setPosition(170, yWindow-200);
            words.setPosition(220, yWindow-180);
            window.draw(speechBubble);
            words.setString("Restart Level");
            words.setCharacterSize(90);
            window.draw(words);
            
        }
        
        
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&clock.getElapsedTime().asSeconds()>0.5){
            clock.restart();
            if(mouse.getGlobalBounds().intersects(nextRect.getGlobalBounds())){
                buttonOptions=5;
                
            }
            
            if(mouse.getGlobalBounds().intersects(replayWinRect.getGlobalBounds())){
                buttonOptions=2;
            }
            
            
            
            
        }
        
    }

    
    if(checkLoss(gameCount))
    {
        
        
        //window.draw(next);
        window.draw(replayWin);
        window.draw(loseText);
        
        
        if(mouse.getGlobalBounds().intersects(replayWinRect.getGlobalBounds())){
            speechBubble.setPosition(170, yWindow-200);
            words.setPosition(220, yWindow-180);
            window.draw(speechBubble);
            words.setString("Restart Level");
            words.setCharacterSize(90);
            window.draw(words);
            
        }
        
        
        
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&clock.getElapsedTime().asSeconds()>0.5){
            clock.restart();
            
            if(mouse.getGlobalBounds().intersects(replayWinRect.getGlobalBounds())){
                buttonOptions=2;
            }
            
            
            
            
        }
        
    }
    

    
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&clock.getElapsedTime().asSeconds()>0.5){
        
       // cout << "IN MOUSE" << endl ;
        clock.restart();
        
        if(mouse.getGlobalBounds().intersects(hintsRect.getGlobalBounds())){
            buttonOptions=1;
        }
        
        if(mouse.getGlobalBounds().intersects(replay.getGlobalBounds())){
            buttonOptions=2;

        }
        
        if(mouse.getGlobalBounds().intersects(restart.getGlobalBounds())){
            buttonOptions=3;

        }
        
        if(mouse.getGlobalBounds().intersects(soundRect.getGlobalBounds())){
            
            buttonOptions=4;

        }
        
        
        
    }
 
    
    
    window.draw(testSprite);
    window.draw(replay);
    window.draw(restart);
    window.draw(soundB);
    //window.draw(soundO);

    
    
    
    
}



