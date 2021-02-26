#ifndef ELEMENT_H_INCLUDED
#define ELEMENT_H_INCLUDED

#include <SFML/Network.hpp>
//#include "inc.h"

class Tile
{
public :
    Tile(Tiles =SEA, int =0);
    Tiles getTile() const;
    int getNum() const;

private:
    Tiles m_tile;
    int m_num;
};

class Elements
{
public :
    Elements(std::string);
    virtual ~Elements();
    virtual bool setPlayer(Player*);
    virtual bool canBeBought();
    virtual bool collectProduct(Board*, int, int, int);
    virtual Tile* getTile() const;
    virtual std::vector<Ressources> getPrice();
   // virtual void update()=0;

protected :

};

class SubTile : public Elements
{
public :
    SubTile(Tile*, bool isCenter=false, std::string ="res/tile.png", std::string fontPath ="res/Fipps-Regular.otf");
    ~SubTile();
    virtual Tile* getTile() const;
    //void update();

private :
    Tile* m_tile;
    bool m_isCenter;
};

class Buyable : public Elements
{
public :
    Buyable(Player*, std::vector<Ressources>, std::string);
    virtual std::vector<Ressources> getPrice();
    virtual bool canBeBought();
    virtual bool setPlayer(Player*);
    //virtual void update()=0;

protected :
    Player* m_player;
    std::vector<Ressources> m_price;
};

class Road : public Buyable
{
public :
    Road(Player*, std::vector<Ressources> price, std::string ="res/road.png");
    //virtual void update();

private :

};

class Intersection : public Buyable
{
public :
    Intersection (Player*, std::vector<Ressources>, std::string = "res/intersection.png");
    virtual bool collectProduct(Board*, int, int, int);
  //  virtual void update();

private :

};

#endif // ELEMENT_H_INCLUDED
