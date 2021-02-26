#ifndef PLAYER_H
#define PLAYER_H

#include "C:\Users\Hyacinthe\Documents\Code\Cpp_Projects\Catane\Catane_serveur\inc.h"
#include <SFML/Network.hpp>

class Player
{
public:
    Player(Players player, std::string name, int points=0, std::string texturePath="res/tilea.png", std::string fontPath="res/Fipps-Regular.otf");
    bool buyElement(Elements*, std::vector<Ressources>);
    Players getPlayer();
    void collectRessource(Ressources);
    bool loseResource(Ressources, int=1);
    bool hasRessources(std::vector<Ressources>);
    std::string getName() const;

/*bool Connection(sf::TcpListener& listener);

template <typename T>
void send (T message);

template <typename T>
T receive ();
*/

private:
    std::list<Ressources> m_ressources;
    Players m_player;
    std::string m_name;
    int m_points;

    sf::TcpSocket m_socket;

};

#endif // PLAYER_H
