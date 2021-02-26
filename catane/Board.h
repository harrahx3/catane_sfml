#ifndef PLATEAU_H_INCLUDED
#define PLATEAU_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "inc.h"

/*class Player
{
public:
    Player(Players player, std::string, int points=0);
    bool buyElement(Elements*, std::vector<Ressources>);
    Players getPlayer();
    void collectRessource(Ressources);
    bool loseResource(Ressources, int=1);
    bool hasRessources(std::vector<Ressources>);
    void printRessources();
private:
    std::list<Ressources> m_ressources;
    Players m_player;
    std::string m_name;
    int m_points;
};
*/

class Market : public sf::Drawable, public sf::Transformable
{
public :
    //  Market(std::vector<Player> players, sf::Button tradeButton, sf::Button acceptButton, std::string texturePath="res/tilea.png", std::string fontPath="res/Fipps-Regular.otf");
    Market(std::string texturePath="res/tiles.png", std::string fontPath="res/Fipps-Regular.otf");
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    //sf::Text drawText(std::string text, int x, int y);
    void trade(std::vector<Player>::iterator m_currentPlayer);
    void update(int x, int y);

    //std::vector<Player*>::iterator m_selectedPlayer;
    int m_selectedPlayer;
    int m_givenRes;
    int m_receivedRes;
    std::vector<Player*> m_players;
    // Ressources m_givenRes;
    //Ressources m_receivedRes;

private :
    // sf::Button m_tradeButton;
    // sf::Button m_acceptButton;
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::Font m_font;
    sf::Text m_text;
};

class Board : public sf::Drawable, public sf::Transformable
{
public :
    Board(std::vector<Player> m_players, Market market);
    ~Board();
    // void play(sf::RenderWindow&);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    Elements* getElement(int, int);
    void product();
    //Player* getCP();    //get m_currentPlayer
    int throwDice();
    void building(int, int);
    void nextPlayer();

    void trade();
    void updateMarket(int x, int y);

    Market m_market;


private :
    static const int m_bHeight = 5;
    static const int m_bWidth = 5;
    static const int m_width = m_bWidth*3+m_bWidth+1     +4; //=21 +4
    static const int m_height = ((m_bHeight+1)/2*5+((m_bHeight+1)/2-1)*3+2)+4*((m_bHeight+1)%2)    +2; //=23 +2

    Elements* m_elements [m_width][m_height];

    std::vector<std::vector<Tile> > m_tiles;
    std::vector<Player> m_players;

    std::vector<Player>::iterator m_currentPlayer;
    //Player* m_currentPlayer;

    sf::RenderWindow* m_app;

    //std::vector<Road*> roads;
    // [m_width*3+m_width+1][((m_height+1)/2*5+((m_height+1)/2-1)*3+2)+4*((m_height+1)%2]
};



/*

//namespace sf{
class Button : public sf::Drawable, public sf::Transformable
{
public:
    Button(std::string text, std::string fontePath);
    Button(sf::Text text);
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    bool isButtonClicked(sf::RenderWindow&);
    sf::Text getText();
    void setText(sf::Text val);
    void setText(std::string newText, sf::Font newFonte );
private:
    sf::Text m_text;
    sf::Font m_fonte;
    sf::RectangleShape m_rect;
};
*/



#endif // PLATEAU_H_INCLUDED
