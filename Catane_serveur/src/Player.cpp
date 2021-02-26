#include <SFML/Network.hpp>

#include "C:\Users\Hyacinthe\Documents\Code\Cpp_Projects\Catane\Catane_serveur\inc.h"
#include <SFML/Network.hpp>
using namespace std;
using namespace sf;

Player::Player(Players player, string name, int points, string texturePath, string fontPath) : m_player(player), m_name(name), m_points(points)
{
   // int comPort = 53000;
    /*sf::TcpListener listener;
    listener.listen(53000);
    Connection(listener);
    listener.accept(m_socket);*/

    m_ressources.push_back(WOOD);
    m_ressources.push_back(WHEAT);
    m_ressources.push_back(CLAY);
    m_ressources.push_back(WOOL);
    m_ressources.push_back(WOOD);
    m_ressources.push_back(WHEAT);
    m_ressources.push_back(CLAY);
    m_ressources.push_back(WOOL);
    m_ressources.push_back(STONE);

}

Players Player::getPlayer()
{
    return m_player;
}


bool Player::buyElement(Elements* element, vector<Ressources> ressourcesAPayees)
{
    cout <<"buyElement()\n";
    if(!element->canBeBought())
    {
        cout <<"erreur achat : canBeBought\n";
        return false;
    }
    if (!this->hasRessources(ressourcesAPayees))
    {
        cout <<"erreur achat : hasRessources\n";
        return false;
    }

    for (int unsigned i=0; i<ressourcesAPayees.size(); i++)
        this->loseResource(ressourcesAPayees[i]);

    if (element->setPlayer(this))
    {
        cout<<"element achete"<<endl;
        return true;
    }
    return false;
}
void Player::collectRessource(Ressources ressource)
{
    //m_ressources.push_back(WOOL);
    cout <<"collectRessource()\n";
    m_ressources.push_back(ressource);
//    this->printRessources();
}

bool Player::loseResource(Ressources ressource, int quantity )
{
    cout <<"loseRessource()\n";
    return eraseListElements<Ressources>(m_ressources, ressource);
}

bool Player::hasRessources(std::vector<Ressources> ressources)
{
    cout <<"hasRessources()\n";
    list<Ressources> m_ressources_copie = m_ressources;
    for (int unsigned i=0; i<ressources.size(); i++)
        if (!eraseListElements(m_ressources_copie, ressources[i]))
            return false;
    cout <<"hasRessources() true\n";
    return true;
}

std::string Player::getName() const
{
    return m_name;
}

/*
bool Player::Connection(sf::TcpListener& listener)
{
    if (listener.accept(m_socket) == sf::Socket::Done)
        return true;
    return false;
}

template <typename T>
void Player::send (T message)
{
    sf::Packet packet;
    packet << message;
    m_socket.send(packet);
}

template <typename T>
T Player::receive ()
{
    sf::Packet packet;
    T data;
    m_socket.receive(packet);
    packet >> data;
    ///return atoi( data.c_str() );
    return data;
}*/

