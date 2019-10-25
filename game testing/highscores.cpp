//
//  highscores.cpp
//  game testing
//
//  Created by Ahmad Refaat on 4/22/16.
//  Copyright © 2016 Ahmad Refaat. All rights reserved.
//

#include "highscores.hpp"

highScores::highScores(int x, int y)
{
    
    
    if(!easyTexture.loadFromFile(resourcePath()+"easybutton.png"))
        return EXIT_FAILURE;
    
    if(!mediumTexture.loadFromFile(resourcePath()+"mediumbutton.png"))
        return EXIT_FAILURE;
    
    if(!hardTexture.loadFromFile(resourcePath()+"hardbutton.png"))
        return EXIT_FAILURE;
    
    
    
    easyButton.setTexture(easyTexture);
    mediumButton.setTexture(mediumTexture);
    hardButton.setTexture(hardTexture);

    
    MediumRectangle.setPosition(x/2-220, y/2-50);
    MediumRectangle.setSize(Vector2f(436,148));
    MediumRectangle.setFillColor(Color::Black);
    
    easyRectangle.setPosition(x/2-220, y/2-250);
    HardRectangle.setPosition(x/2-220, y/2+150);
    HardRectangle.setSize(Vector2f(436,148));
    easyRectangle.setSize(Vector2f(436,148));
    easyRectangle.setFillColor(Color::Black);
    HardRectangle.setFillColor(Color::Black);
    
    
    
    easyButton.setPosition(easyRectangle.getPosition());
    mediumButton.setPosition(MediumRectangle.getPosition());
    hardButton.setPosition(HardRectangle.getPosition());
    
    

    
    
}
string highScores::assigndiff( string diff)
{
    string file;
    if ((diff == "easy") || (diff == "Easy") || (diff == "EASY"))
    {
        file = "easy.txt";
        return file;
    }
    else
        if ((diff == "hard") || (diff == "Hard") || (diff == "HARD"))
        {
            file = "hard.txt";
            return file;
        }
        else
            if ((diff == "medium") || (diff == "Medium") || (diff == "MEDIUM"))
            {
                file = "medium.txt";
                return file;
                
            }
            else
                cout << "Invalid difficulty";
}
void highScores::first(string name, int level, string diff)
{
    state.open((assigndiff(diff)).c_str());
    user x;
    x.name = name;
    x.level = level;
    list.push_back(x);
    
    state << list.at(0).name << ' ' << list.at(0).level << endl;
    state.close();
    
}
void highScores::addUser(string name, int level, string diff)
{
    int length;
    cout << name << endl ;
    //state.open((assigndiff(diff)).c_str());
    state.open((assigndiff(diff)).c_str());
    state.seekg(0, ios::end);
    length = state.tellg();
    state.close();
    
    if (length == 0)
        first(name, level, diff);
    else
    {
        transfer(diff);
        state.open((assigndiff(diff)).c_str());
        user x;
        bool flag=true;
        int i = 0;
        if(flag)
            while ((i<list.size())&&(flag))
            {
                cout << list.at(i).name << endl ;
                if (list.at(i).name == name)
                {
                    cout <<"Name already exists " << endl ;
                   if(list.at(i).level < level)
                   {
                    cout << list.at(i).level << endl << endl ;
                        list.at(i).level = level;
                    
                    cout << list.at(i).level << endl ;
                   }
                    flag = false;
                }
                else
                    i++;
            }
        if(flag)
        {
            cout << "Name doesn't exist! " << endl ;
            x.name = name;
            x.level = level;
            list.push_back(x);
            sort();
            
        }
            for (int i = 0; i < list.size(); i++)
            {
                cout << list.at(i).name << ' ' << list.at(i).level << endl;

                state << list.at(i).name << ' ' << list.at(i).level << endl;
            }
        }
        state.close();
    }

int highScores::search(string name,string diff)
{
    
    transfer(diff);
    int i = 0;
    while (i<list.size())
    {
        transform(list.at(i).name.begin(), list.at(i).name.end(),list.at(i).name.begin(), ::tolower) ;

        if (list.at(i).name == name){

            return list.at(i).level;
        }
        else
            i++;
    }
    return 1;
}
void highScores::sort()
{
    for (int i = 0; i < list.size() - 1; i++)
        for (int j = i + 1; j < list.size(); j++)
        {
            if ((list.at(i).level) < (list.at(j).level))
                swap(list.at(i), list.at(j));
        }
    
}
void highScores::swap(user& i, user& j)
{
    int tempLevel;
    tempLevel = i.level;
    i.level = j.level;
    j.level = tempLevel;
    
    string tempName;
    tempName = i.name;
    i.name = j.name;
    j.name = tempName;
}
void highScores::transfer(string diff)
{
    while (!list.empty())
        list.pop_back();
    state.open((assigndiff(diff)).c_str());
    string y;
    user x;
    int z;
    state >> y;
    while (!state.eof())
    {
        
        x.name =y;
        state >> z;
        x.level=z;
        list.push_back(x);
        state >> y;
    }
    state.close();
}
void highScores::display(int number, string diff,RenderWindow& window)
{
    
    
   // RenderWindow window(VideoMode(width, height), "High Scores");
    Texture t;
    //if (!t.loadFromFile(resourcePath()+ "facegfx-vector-wooden-floor-vector-background-01.jpg"))
      //  cout << "error image";
   
    if (!t.loadFromFile(resourcePath()+ "Hscore.png"))
     cout << "error image";
    RectangleShape board;
    board.setSize(Vector2f(boardw, boardh));
    board.setPosition((width - boardw)-130 , space);
    board.setTexture(&t);
    
    Texture s;
    if (!s.loadFromFile(resourcePath()+"imageedit_20_9679204724.png"))
        cout << "error image";
    RectangleShape box;
    box.setSize(Vector2f(boxw, boxh));
    box.setPosition(space * 5, boardh + space * 2);
    box.setTexture(&s);
    
    Text users[10];
    Text levels[10];
    
    Font x;
    if (!x.loadFromFile(resourcePath()+"kan.ttf"))
        cout << "error font";
    
    Text main;
    main.setString("High Scores");
    main.setColor(Color::Black);
    main.setCharacterSize(50);
    main.setFont(x);
    main.setPosition((width - boardw) / 2 +space+ 10, (boardh/2)+10 );
    
    string z, y;
    
    //cout <<"Before Transfer"<< endl ;

    transfer(diff);
    sort();
    if (number > list.size())
        number = list.size()+1;
    for (int i = 0; i < number - 1; i++)
    {
        if(list.at(i).level<10)
        y = " "+to_string(list.at(i).level);
        else
            y = to_string(list.at(i).level);

        z = list.at(i).name;// + "      " + y;
        users[i].setString(z);
        users[i].setColor(Color::Black);
        //users[i].setCharacterSize((boardh - 10) / (number/2));
        users[i].setCharacterSize(80);
        users[i].setFont(x);
        users[i].setPosition(space * 5 + 150 , (i*80)+340);// / (number/2)))+((boardh + space * 5)));

    
        levels[i].setString(y);
        levels[i].setColor(Color::Black);
        levels[i].setCharacterSize(80);
        levels[i].setFont(x);
        levels[i].setPosition(space * 12+ 150, (i*80)+340); // / (number/2)))+((boardh + space * 5)));

    }
    
        
       window.draw(board);
        window.draw(box);
        //window.draw(main);
    for (int j = 0; j < number - 1; j++){
            window.draw(users[j]);
        window.draw(levels[j]);
    }
    
}

void highScores::choose(int& n,RectangleShape mouse,RenderWindow& window,int& prev,Sprite& birdySprite,Clock& clock){
    
    window.draw(easyButton);
    window.draw(mediumButton);
    window.draw(hardButton);
    window.draw(birdySprite);
    
    
    if(mouse.getGlobalBounds().intersects(easyRectangle.getGlobalBounds())){
        birdySprite.setPosition(easyRectangle.getPosition().x-200, easyRectangle.getPosition().y-30);
    }
    
    else if(mouse.getGlobalBounds().intersects(MediumRectangle.getGlobalBounds())) {
        
        birdySprite.setPosition(MediumRectangle.getPosition().x-200, MediumRectangle.getPosition().y-30);
        
        
    }
    
    else if(mouse.getGlobalBounds().intersects(HardRectangle.getGlobalBounds())) {
        
        birdySprite.setPosition(HardRectangle.getPosition().x-200, HardRectangle.getPosition().y-30);
        
    }
    
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)&& clock.getElapsedTime().asSeconds()>0.5){
        clock.restart();
        if(mouse.getGlobalBounds().intersects(easyRectangle.getGlobalBounds())){
            prev=n;
            n=11;
        }
        
        
        if(mouse.getGlobalBounds().intersects(MediumRectangle.getGlobalBounds())){
            prev=n;
            n=12;
        }
        
        
        
        if(mouse.getGlobalBounds().intersects(HardRectangle.getGlobalBounds())){
            prev=n;
            n=13;
        }
        
    }
    
    
    
    
    
}
