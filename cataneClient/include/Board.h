#ifndef BOARD_H
#define BOARD_H

#include "inc.h"

class Board : public sf::Drawable, public sf::Transformable
{
public :
    Board();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    Elements* getElement(int, int);
    void dest();

    std::vector< std::vector< Elements*> > m_elements;

    void  receivePacket(sf::Packet &packet);

    static int tileSize;

private :
    static const int m_bHeight = 5;
    static const int m_bWidth = 5;
    static const int m_width = m_bWidth*3+m_bWidth+1     +4; //=21 +4
    static const int m_height = ((m_bHeight+1)/2*5+((m_bHeight+1)/2-1)*3+2)+4*((m_bHeight+1)%2)    +2; //=23 +2

    sf::RenderWindow* m_app;

};



#endif // BOARD_H
