#ifndef PLAYER_H
#define PLAYER_H

#include "inc.h"

class Player
{
public:
    Player(Players player=EMPTY, std::string name="", int points=0, std::string texturePath="res/tilea.png", std::string fontPath="res/Fipps-Regular.otf");
    bool buyElement(Elements*, std::vector<Ressources>);
    Players getPlayer();
    void collectRessource(Ressources);
    bool loseResource(Ressources, int=1);
    bool hasRessources(std::vector<Ressources>);
    std::string getName() const;

    void toPacket(sf::Packet &packet) const;


protected:
    std::list<Ressources> m_ressources;
    Players m_player;
    std::string m_name;
    int m_points;

};


#endif // PLAYER_H
