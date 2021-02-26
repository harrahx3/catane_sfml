#include "inc.h"

using namespace std;
using namespace sf;

sf::Texture Player::m_texture;
sf::Font Player::m_font;

Player::Player(Players player,string name, int points, string texturePath, string fontPath) : m_player(player), m_name(name), m_points(points)
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

   /* if (!m_texture.loadFromFile(texturePath))
        cout<<"erreur chargement sprite Player"<<endl;*/
    m_sprite = Sprite(m_texture);

   /* if (!m_font.loadFromFile(fontPath))       ///load the font
        std::cout<<"erreur chargement fonte Player\n";
    else*/
        m_text.setFont(m_font);
    m_text.setPosition(0,0);
    m_text.setColor(sf::Color::Blue);
    m_text.setCharacterSize(10);
    m_text.setString("a");
    m_text.setFont(m_font);

}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *=  getTransform();
    int i = 150;
    int j = 0;
    int inc = 15;

    std::list<Ressources> ressources = m_ressources;
    ressources.sort();
    for(std::list<Ressources>::iterator it = ressources.begin(); it!=ressources.end(); ++it)
    {
        i += inc;
        target.draw(Ressource_graph(*it, i, j), states);
    }

    sf::Text text;
    text.setFont(m_font);
    text.setString(m_name + " (" + toString(m_points) + " pts)");
    text.setColor(getPlColor(m_player));
    text.setPosition(0,0);
    text.setCharacterSize(10);
    target.draw(text, states);
}
std::string Player::getName() const
{
    return m_name;
}

Players Player::getPlayer()
{
    return m_player;
}

void Player::receivePacket(sf::Packet &packet)
{
        sf::Uint32 pl;
        std::string name;
        std::list<Ressources> ressources;
        sf::Uint32 pt;
        sf::Uint32 nb;
        packet >> pl >> name >> pt >> nb;
        m_player = Players(pl);
        m_name = name;
        m_points = pt;
      //  std::cout << pl <<" " << name << " " << pt << "\n";
        for (unsigned int i=0; i<nb; i++)
        {
            sf::Uint32 rc;
            packet >> rc;
            ressources.push_back(Ressources(rc));
            //std::cout << rc << std::endl;
        }
        m_ressources = ressources;

}

sf::Color Player::getPlColor(Players player)
{
        if (player==0)
        return Color::Cyan;
    else
        switch(player)
        {
        case BLUE :
            return Color::Blue;
            break;
        case RED :
            return Color::Red;
            break;
        case WHITE :
            return Color::White;
            break;
        case YELLOW :
            return Color::Yellow;
            break;
        default :
            return Color::Cyan;
        }
}
