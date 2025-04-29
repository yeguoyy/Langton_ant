#pragma once
#include "map.h"
#include "ant.h"
int chooseMap(Map*&,Ant &,S_Map&,S_Ant&, sf::RenderWindow &);
void creatMap(Map*&, Ant &,S_Map&, S_Ant&, sf::RenderWindow&);
void GoldenFingerMode_creatMap(Map*&, Ant&, S_Map&, S_Ant&, sf::RenderWindow&);
int player_try(Map&,Map*& const,S_Map&, S_Ant& ,int ,int);
int GoldenFingerMode_player_try(Map*&, Map*& const, S_Map&, S_Ant&, int, int);
void introduction(sf::Text&);
void Sports_process(int step, Map*&, Ant&);
void Show_process(Map*, Ant&,S_Map &,S_Ant &, sf::RenderWindow&);
void pause(sf::RenderWindow&);
sf::Angle Way_to_Degree(Direction direction);
