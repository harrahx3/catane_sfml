#ifndef BOARD_H
#define BOARD_H

#include "C:\Users\Hyacinthe\Documents\Code\Cpp_Projects\Catane\Catane_serveur\inc.h"
/*
class Player;
class Elements;
class Tile;*/

class Market
{
public :
    Market(std::string texturePath="res/tiles.png", std::string fontPath="res/Fipps-Regular.otf");
    //sf::Text drawText(std::string text, int x, int y);
    void trade(std::vector<Player>::iterator m_currentPlayer);
    void update(int x, int y);

    //std::vector<Player*>::iterator m_selectedPlayer;
    int m_selectedPlayer;
    int m_givenRes;
    int m_receivedRes;
    std::vector<Player*> m_players;

private :

};

class Board
{
public :
    Board(std::vector<Player> m_players, Market market);
    ~Board();

    Elements* getElement(int, int);
    void product();
    //Player* getCP();    //get m_currentPlayer
    int throwDice();
    void building(int, int);
    void nextPlayer();

    void trade();
    void updateMarket(int x, int y);

    Market m_market;


private :
    static const int m_bHeight = 5;
    static const int m_bWidth = 5;
    static const int m_width = m_bWidth*3+m_bWidth+1     +4; //=21 +4
    static const int m_height = ((m_bHeight+1)/2*5+((m_bHeight+1)/2-1)*3+2)+4*((m_bHeight+1)%2)    +2; //=23 +2

    Elements* m_elements [m_width][m_height];

    std::vector<std::vector<Tile> > m_tiles;
    std::vector<Player> m_players;

    std::vector<Player>::iterator m_currentPlayer;
    //Player* m_currentPlayer;

};

#endif // BOARD_H
