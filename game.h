#pragma once
#include "map.h"
#include "ant.h"
#include "prop.h"


int chooseMode(Map*&, Ant&, S_Map&, S_Ant&, sf::RenderWindow&);
void creatMap(Map*&, Ant&, S_Map&, S_Ant&, sf::RenderWindow&, int x, int y);

void GoldenFingerMode_creatMap(Map*&, Ant&, S_Map&, S_Ant&, sf::RenderWindow&);
int player_try(Map&, Map*& const, S_Map&, S_Ant&, int, int);
int GoldenFingerMode_player_try(const Ant&,Map*&, S_Map&, S_Ant&, int, int,int & if_line);
int GoldenFinger_move(Ant&, Map*&, S_Map&, S_Ant&, std::vector<Prop>&, sf::RenderWindow&);
void GoldenFinger_moveProcess(Ant&, Map*&, S_Map&, S_Ant&, std::vector<Prop>&, sf::RenderWindow&,int step,int & process, int& if_line,int & best_source,int & best_roundsNum,int & best_destroyNum);

void Sports_process(int step, Map*&, Ant&);
void Show_process(Map*, Ant&, S_Map&, S_Ant&, sf::RenderWindow&);

void pause(sf::RenderWindow&);
sf::Angle Way_to_Degree(Direction direction);

void creatProp(std::vector<Prop>& prop_list, const Map&,int type);

void rocket(Ant& ant, Map*& head_map, S_Map& s_map, S_Ant& s_ant, std::vector<Prop>& prop_list, sf::RenderWindow& window, sf::Vector2f Position);//小火箭
void big_rocket(Ant& ant, Map*& head_map, S_Map& s_map, S_Ant& s_ant, std::vector<Prop>& prop_list, sf::RenderWindow& window, sf::Vector2f Position);//小火箭
void Confirm_line(sf::VertexArray& line, Map head_map);//确认激光指示器坐标
void falcula(Ant& ant, Map*& head_map, S_Map& s_map, S_Ant& s_ant, std::vector<Prop>& prop_list, sf::RenderWindow& window, sf::Vector2f Position);//钩爪


void Confirm_line(sf::VertexArray&,Map );

int gameOver_GoldenFinger(sf::RenderWindow& window, const S_Map& s_map, const S_Ant& s_ant, const std::vector<Prop>& prop_list,const Ant& ant, int& best_source, int& best_roundsNum, int& best_destroyNum);