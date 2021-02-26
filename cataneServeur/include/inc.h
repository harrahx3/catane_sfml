#ifndef INC_H_INCLUDED
#define INC_H_INCLUDED

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

enum Tiles {SEA=0, FOREST, HILL, MEADOW, FIELD, MOUNTAIN, DESERT};
enum Ressources {FISH=0, WOOD, CLAY, WOOL, WHEAT, STONE, SAND};
enum Players {EMPTY=0, RED, BLUE, YELLOW, WHITE};

class Player;
class Elements;
class Buyable;
class Road;
class Intersection;
class Board;
class Tile;
class Client;

template <typename T>
bool eraseListElements(std::list<T>& liste, T elementToErase )
{
    std::cout <<"eraseListElements()\n";
    for(typename std::list<T>::iterator it = liste.begin(); it!=liste.end(); ++it)
    {
        if (*it == elementToErase)
        {
            liste.erase(it);
            std::cout << "ressource payee" << std::endl;
            return true;
        }
    }
    return false;
}

/*sf::Packet &operator<<( sf::Packet &packet, std::list<Ressources> const& liste)
{
    packet << liste.size();
    for(typename std::list<Ressources>::iterator it = liste.begin(); it!=liste.end(); ++it)
    {
        packet << *it;
    }
    return packet;
}*/


template <typename T>
sf::Packet &operator<<( sf::Packet &packet, T const& obj)
{
    obj.toPacket(packet);
    return packet;
}

template <typename T>
std::string toString(T a)
{
    std::stringstream ss;
    ss << a;
    std::string str = ss.str();
    return str;
}






#include "Player.h"
#include "Board.h"
#include "Elements.h"
#include "Client.h"

#endif // INC_H_INCLUDED
