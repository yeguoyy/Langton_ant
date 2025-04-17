#pragma once
#include "map.h"
#include "ant.h"
bool chooseMap(Map*&,Ant &,S_Map&, sf::RenderWindow &);
void creatMap(Map*&, Ant &);
void player_try(Map&,Map*& const);
void introduction();
