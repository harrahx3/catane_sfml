#ifndef INC_H_INCLUDED
#define INC_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <time.h>
#include <ctime>
#include <fstream>
#include <map>
#include <sstream>



template <typename T>
sf::Packet &operator>>(sf::Packet &packet, T& obj)
{
    obj.receivePacket(packet);
    return packet;
}

template <typename T>
std::string toString(T obj)
{
    std::stringstream ss;
    ss << obj;
    std::string str = ss.str();
    return str;
}

enum Tiles {SEA=0, FOREST, HILL, MEADOW, FIELD, MOUNTAIN, DESERT};
enum Ressources {FISH=0, WOOD, CLAY, WOOL, WHEAT, STONE, SAND   , SIZE};
enum Players {EMPTY=0, RED, BLUE, YELLOW, WHITE};

class Player;
class Board;
class Ressource_graph;
class Elements;
class SubTile;
class Road;
class Intersection;


#include "Player.h"
#include "Board.h"
#include "Element.h"

#endif // INC_H_INCLUDED
