#ifndef BOARD_H
#define BOARD_H

#include "inc.h"

class Board
{
public :
    Board(std::vector<Client*> m_players);
   // ~Board();

    Elements* getElement(int, int);
    void product();
    //Player* getCP();    //get m_currentPlayer
    int throwDice();
    void building(int, int);
    void nextPlayer();
    void play();

    void toPacket(sf::Packet &packet) const;
    void dest();

private :
    static const int m_bHeight = 5;
    static const int m_bWidth = 5;
    static const int m_width = m_bWidth*3+m_bWidth+1     +4; //=21 +4
    static const int m_height = ((m_bHeight+1)/2*5+((m_bHeight+1)/2-1)*3+2)+4*((m_bHeight+1)%2)    +2; //=23 +2

    Elements* m_elements [m_width][m_height];

    std::vector<std::vector<Tile> > m_tiles;
    std::vector<Client*> m_players;

    std::vector<Client*>::iterator m_currentPlayer;

};

/*
sf::Packet& operator <<(sf::Packet& packet, const Board& board)
{
    return packet << board.get << character.name << character.weight;
}

sf::Packet& operator >>(sf::Packet& packet, Character& character)
{
    return packet >> character.age >> character.name >> character.weight;
}
*/

#endif // BOARD_H
