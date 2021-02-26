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
class Tile
{
public :
    Tile(Tiles =SEA, int =0);
    Tiles getTile();
    int getNum();

private:
    Tiles m_tile;
    int m_num;
};

class Elements
{
public :
    Elements(std::string);
    virtual ~Elements();
    virtual sf::Sprite draw() = 0;
    virtual bool setPlayer(Player*);
    virtual bool canBeBought();
    virtual bool collectProduct(Board*, int, int, int);
    virtual Tile* getTile();
    virtual std::vector<Ressources> getPrice();

protected :
    sf::Texture m_texture;
    sf::Sprite m_sprite;
};

class Buyable : public Elements
{
public :
    Buyable(Player*, std::vector<Ressources>, std::string);
    virtual std::vector<Ressources> getPrice();
    virtual bool canBeBought();
    virtual bool setPlayer(Player*);

protected :
    Player* m_player;
    std::vector<Ressources> m_price;
};

class Road : public Buyable
{
public :
    Road(Player*, std::vector<Ressources> price, std::string ="res/road.png");
    virtual sf::Sprite draw();

private :
};

class Intersection : public Buyable
{
public :
    Intersection (Player*, std::vector<Ressources>, std::string = "res/intersection.png");
    virtual sf::Sprite draw();
    virtual bool collectProduct(Board*, int, int, int);

private :
};

class SubTile : public Elements
{
public :
    SubTile(Tile*, std::string ="res/tile.png");
    virtual sf::Sprite draw();
    virtual Tile* getTile();

private :
    Tile* m_tile;
};

class Board
{
public :
    Board();
    ~Board();
    // void play(sf::RenderWindow&);
    void draw(sf::RenderWindow&, int =15);
    Elements* getElement(int, int);
    void product();
    //Player* getCP();    //get m_currentPlayer
    int throwDice();
    void building(int, int);
    void nextPlayer();

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
