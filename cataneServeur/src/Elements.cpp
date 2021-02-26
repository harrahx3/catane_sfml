#include "inc.h"

using namespace std;
using namespace sf;


Elements::Elements(string path)
{

}
Elements::~Elements()
{

}
bool Elements::canBeBought()
{
    return false;
}

bool Elements::setPlayer(Player*)
{
    return false;
}
bool Elements::collectProduct(Board* board, int i, int j, int num)
{
    return false;
}
Tile* Elements::getTile() const
{
    return 0;
}
vector<Ressources> Elements::getPrice()
{
    vector<Ressources> v;
    return v;
}

void Elements::toPacket(sf::Packet &packet) const
{
    packet << "elments";//sf::Uint32(42);
}

Buyable::Buyable(Player* player, std::vector<Ressources> price, string path) : Elements(path), m_player(player), m_price(price)
{

}
vector<Ressources> Buyable::getPrice()
{
    return m_price;
}
bool Buyable::canBeBought()
{
    return m_player == 0;
}
bool Buyable::setPlayer(Player* newPlayer)
{
    m_player = newPlayer;
    return true;
}

Road::Road(Player* player, std::vector<Ressources> price, string path) : Buyable(player, price, path)
{
}
void Road::toPacket(sf::Packet &packet) const
{
    packet << "Road";
    std::vector<Ressources> price;
    if (m_player != 0)
        packet << *m_player;
    else
        packet << Player();
}


Intersection::Intersection(Player* player, std::vector<Ressources>price, string path) : Buyable(player, price, path)
{
}

bool Intersection::collectProduct(Board* board, int i, int j, int num)
{
    if (m_player!=0)
    {
        // m_player.collectRessource(WHEAT);
        if (board->getElement(i-1,j)->getTile() != 0 && board->getElement(i-1,j)->getTile()->getNum() == num)
            m_player->collectRessource(Ressources(board->getElement(i-1,j)->getTile()->getTile()));
        if (board->getElement(i+1,j)->getTile() != 0 && board->getElement(i+1,j)->getTile()->getNum() == num)
            m_player->collectRessource(Ressources(board->getElement(i+1,j)->getTile()->getTile()));
        if (board->getElement(i,j-1)->getTile() != 0 && board->getElement(i,j-1)->getTile()->getNum() == num)
            m_player->collectRessource(Ressources(board->getElement(i,j-1)->getTile()->getTile()));
        if (board->getElement(i,j+1)->getTile() != 0 && board->getElement(i,j+1)->getTile()->getNum() == num)
            m_player->collectRessource(Ressources(board->getElement(i,j+1)->getTile()->getTile()));
        // m_player->printRessources();
        return true;
    }
    return false;
}

void Intersection::toPacket(sf::Packet &packet) const
{
    packet << "Intersection";
    if (m_player != 0)
        packet << *m_player;
    else
        packet << Player();
}

SubTile::SubTile(Tile* tile, bool isCenter, string path, string fontPath) : Elements(path), m_tile(tile), m_isCenter(isCenter)
{

}
SubTile::~SubTile()
{

}
void SubTile::toPacket(sf::Packet &packet) const
{
    packet << "subTile";
    if (m_tile != 0)
        packet << *m_tile << ((sf::Uint32)(m_isCenter));
    else
        packet << Tile() << ((sf::Uint32)(false));
}

Tile* SubTile::getTile() const
{
    return m_tile;
}

Tile::Tile(Tiles tile, int num) : m_tile(tile), m_num(num)
{

}
Tiles Tile::getTile() const
{
    return m_tile;
}
int Tile::getNum() const
{
    return m_num;
}
void Tile::toPacket(sf::Packet &packet) const
{
    //packet << "Tile" << Uint32(0) << Uint32(0) ;
    packet << ((Uint32)m_tile) << ((sf::Uint32) m_num) ;

}
