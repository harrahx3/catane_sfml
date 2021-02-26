#ifndef PLAYER_H
#define PLAYER_H

#include "inc.h"

class Player : public sf::Widget//public sf::Drawable, public sf::Transformable
{
public:
    Player(Players player=EMPTY, std::string name="", int points=0, std::string texturePath="res/tilea.png", std::string fontPath="res/Fipps-Regular.otf");
    Players getPlayer();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    std::string getName() const;

    static sf::Color getPlColor(Players);
    static sf::Texture m_texture;
    static sf::Font m_font;

    void receivePacket(sf::Packet &packet);

private:
    std::list<Ressources> m_ressources;
    Players m_player;
    std::string m_name;
    int m_points;
    sf::Sprite m_sprite;
    sf::Text m_text;


};

#endif // PLAYER_H
