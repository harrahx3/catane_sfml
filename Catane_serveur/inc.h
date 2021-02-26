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

/*emplate <typename T>
bool eraseListElements(typename std::list<T>& liste, T elementToErase );*/

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

enum Tiles {SEA=0, FOREST, HILL, MEADOW, FIELD, MOUNTAIN, DESERT};
enum Ressources {FISH=0, WOOD, CLAY, WOOL, WHEAT, STONE, SAND};
enum Players {EMPTY=0, RED, BLUE, YELLOW, WHITE};

class Player;
class Elements;
class Market;
class Buyable;
class Road;
class Intersection;
class Board;
class Tile;

//#include "main.cpp"
#include "Player.h"
#include "Board.h"
#include "Element.h"

#endif // INC_H_INCLUDED
