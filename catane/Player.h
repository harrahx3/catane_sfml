#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "inc.h"
#include <SFML/Graphics.hpp>

class Player : public sf::Drawable, public sf::Transformable
{
public:
    Player(Players player, std::string name, int points=0, std::string texturePath="res/tilea.png", std::string fontPath="res/Fipps-Regular.otf");
    bool buyElement(Elements*, std::vector<Ressources>);
    Players getPlayer();
    void collectRessource(Ressources);
    bool loseResource(Ressources, int=1);
    bool hasRessources(std::vector<Ressources>);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    State getState();
    void setState(State state);
    std::string getName() const;


private:
    std::list<Ressources> m_ressources;
    Players m_player;
    std::string m_name;
    int m_points;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Font m_font;
    sf::Text m_text;
    State m_state;
};

#endif // PLAYER_H_INCLUDED
