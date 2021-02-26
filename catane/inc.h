#ifndef INC_H_INCLUDED
#define INC_H_INCLUDED

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
bool eraseListElements(typename std::list<T>& liste, T elementToErase );

enum Tiles {SEA=0, FOREST, HILL, MEADOW, FIELD, MOUNTAIN, DESERT};
enum Ressources {FISH=0, WOOD, CLAY, WOOL, WHEAT, STONE, SAND};
enum Players {EMPTY=0, RED, BLUE, YELLOW, WHITE};
enum State {NOTPLAYING, PLAYING, BUILDING, TRADING};

class Player;
class Elements;
class Market;
class Buyable;
class Road;
class Intersection;
class Board;
class Tile;

#include "Player.h"
#include "Board.h"
#include "Element.h"
//#include "main.cpp"

#endif // INC_H_INCLUDED
