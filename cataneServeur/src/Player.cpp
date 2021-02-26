#include "inc.h"

using namespace std;
using namespace sf;

Player::Player(Players player, string name, int points, string texturePath, string fontPath) : m_player(player), m_name(name), m_points(points)
{
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
        cout << "Player " << m_name << "can't buy this element" << endl;
        return false;
    }
    if (!this->hasRessources(ressourcesAPayees))
    {
        cout << "Player " << m_name << " doesn't have required resources to buy element" << endl;
        return false;
    }

    for (int unsigned i=0; i<ressourcesAPayees.size(); i++)
        this->loseResource(ressourcesAPayees[i]);

    if (element->setPlayer(this))
    {
        cout<<"Player "<< m_name << " bought element"<<endl;
        return true;
    }
    return false;
}
void Player::collectRessource(Ressources ressource)
{
    //m_ressources.push_back(WOOL);
    cout <<"collectRessource()\n";
    m_ressources.push_back(ressource);
    cout << "Player " << m_name << " got resource " << ressource << std::endl;
//    this->printRessources();
}

bool Player::loseResource(Ressources ressource, int quantity )
{
    cout << "Player " << m_name << " lost resource " << ressource << std::endl;
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

void Player::toPacket(sf::Packet &packet) const
{
    packet << "player";
    packet << ((sf::Uint32) m_player) << m_name << (sf::Uint32) m_points;
    packet << m_ressources.size();
    std::list<Ressources> liste = m_ressources;
    for(typename std::list<Ressources>::iterator it = liste.begin(); it!=liste.end(); ++it)
    {
        packet << (sf::Uint32)*it;
    }
}
