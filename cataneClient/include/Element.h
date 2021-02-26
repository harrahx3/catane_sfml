#ifndef ELEMENT_H
#define ELEMENT_H

#include "inc.h"



class Ressource_graph : public sf::Widget//public sf::Transformable, public sf::Drawable
{
public :
    Ressource_graph (Ressources res, int x=0, int y=0, std::string texturePath="res/tilea.png");
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    static sf::Color getResColor(Ressources);


private :
    Ressources m_res;
    sf::Texture m_texture;
    sf::Sprite m_sprite;


};

////////////////////////

class Tile
{
public :
    Tile(Tiles =SEA, int =0);
    Tiles getTile() const;
    int getNum() const;
    static sf::Color getTileColor(Tiles);

private:
    Tiles m_tile;
    int m_num;
};

class Elements : public sf::Transformable, public sf::Drawable
{
public :
    Elements(std::string, sf::Texture);
    virtual ~Elements();
//    virtual sf::Sprite draw() = 0;
    virtual bool setPlayer(Player*);
    virtual bool canBeBought();
    virtual bool collectProduct(Board*, int, int, int);
    virtual Tile* getTile() const;
    virtual std::vector<Ressources> getPrice();
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void update()=0;

    //static sf::Texture m_texture;


protected :

    sf::Texture m_texture;
    sf::Sprite m_sprite;
};

class SubTile : public Elements
{
public :
    SubTile(Tile*, bool isCenter=false, std::string ="res/tile.png", std::string fontPath ="res/Fipps-Regular.otf");
    ~SubTile();
    //virtual sf::Sprite draw();
    virtual Tile* getTile() const;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void update();

    static sf::Texture m_texture;
    static sf::Font m_font;

private :
    Tile* m_tile;
    bool m_isCenter;
    sf::Text m_text;
};

class Buyable : public Elements
{
public :
    Buyable(Player*, std::vector<Ressources>, std::string, sf::Texture);
    virtual std::vector<Ressources> getPrice();
    virtual bool canBeBought();
    virtual bool setPlayer(Player*);
    virtual void update()=0;
    // virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected :
    Player* m_player;
    std::vector<Ressources> m_price;
};

class Road : public Buyable
{
public :
    Road(Player*, std::vector<Ressources> price, std::string ="res/road.png");
    //virtual sf::Sprite draw();
    // void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void update();
    static sf::Texture m_texture;

private :
};

class Intersection : public Buyable
{
public :
    Intersection (Player*, std::vector<Ressources>, std::string = "res/intersection.png");
    // virtual sf::Sprite draw();
    // void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    virtual void update();
    static sf::Texture m_texture;

private :
};


#endif // ELEMENT_H
