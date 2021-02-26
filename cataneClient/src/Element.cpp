#include "inc.h"

using namespace std;
using namespace sf;

sf::Texture SubTile::m_texture;//.loadFromFile("res/tile.png");
sf::Texture Road::m_texture;
sf::Texture Intersection::m_texture;
sf::Font SubTile::m_font;

Elements::Elements(string path, sf::Texture texture) : m_texture(texture)
{
   /* if (!m_texture.loadFromFile(path))
        cout<<"erreur chargement sprite Element"<<endl;
    m_sprite = Sprite(m_texture);      //m_sprite.setScale(5,5);*/
    m_sprite = Sprite(m_texture);
}
Elements::~Elements()
{

}
bool Elements::canBeBought()
{
    return false;
}

bool Elements::setPlayer(Player*)
{
    return false;
}
bool Elements::collectProduct(Board* board, int i, int j, int num)
{
    return false;
}
Tile* Elements::getTile() const
{
    return 0;
}
vector<Ressources> Elements::getPrice()
{
    vector<Ressources> v;
    return v;
}

Buyable::Buyable(Player* player, std::vector<Ressources> price, string path, sf::Texture texture) : Elements(path, texture), m_player(player), m_price(price)
{

}
vector<Ressources> Buyable::getPrice()
{
    return m_price;
}
bool Buyable::canBeBought()
{
    return m_player == 0;
}
bool Buyable::setPlayer(Player* newPlayer)
{
    m_player = newPlayer;
    this->update();
    return true;
}

Road::Road(Player* player, std::vector<Ressources> price, string path) : Buyable(player, price, path, m_texture)
{
    this->update();
}
void Road::update()
{
    if (m_player==0)
        m_sprite.setColor(sf::Color::Cyan);

    m_sprite.setColor(Player::getPlColor(m_player->getPlayer()));

   /* else
        switch(m_player->getPlayer())
        {
        case BLUE :
            m_sprite.setColor(Color::Blue);
            break;
        case RED :
            m_sprite.setColor(Color::Red);
            break;
        case WHITE :
            m_sprite.setColor(Color::White);
            break;
        case YELLOW :
            m_sprite.setColor(Color::Yellow);
            break;
        default :
            m_sprite.setColor(Color::Cyan);
        }*/
    //return m_sprite;
}
void Elements::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *=  getTransform();

    target.draw(m_sprite, states);
}

Intersection::Intersection(Player* player, std::vector<Ressources>price, string path) : Buyable(player, price, path, m_texture)
{
    this->update();
}
void Intersection::update()
{
    if (m_player==0)
        m_sprite.setColor(Color::Cyan);

    m_sprite.setColor(Player::getPlColor(m_player->getPlayer()));

   /* else
        switch(m_player->getPlayer())
        {
        case BLUE :
            m_sprite.setColor(Color::Blue);
            break;
        case RED :
            m_sprite.setColor(Color::Red);
            break;
        case WHITE :
            m_sprite.setColor(Color::White);
            break;
        case YELLOW :
            m_sprite.setColor(Color::Yellow);
            break;
        default :
            m_sprite.setColor(Color::Cyan);
        }*/
    // return m_sprite;
}

SubTile::SubTile(Tile* tile, bool isCenter, string path, string fontPath) : Elements(path, m_texture), m_tile(tile), m_isCenter(isCenter)
{
    //string fontPath = "C:/Users/Hyacinthe/Documents/projetsCodeblock/catane/bin/Debug/Fipps-Regular.otf";
    if (isCenter)
    {
      /*  if (!m_font.loadFromFile(fontPath))       ///load the font
            std::cout<<"erreur chargement fonte SubTile \n";
        else*/
            m_text.setFont(m_font);
        m_text.setCharacterSize(10);
        m_text.setOrigin(2,0);
    }
}
SubTile::~SubTile()
{

}
void SubTile::update()
{
    m_text.setColor(sf::Color::Red);
    if (m_isCenter && m_tile!=0)
    {
        ostringstream tt;      ///convertir un int en texte affichable
        tt << getTile()->getNum();
        m_text.setString(tt.str());
        m_text.setColor(Tile::getTileColor(m_tile->getTile()));
    }
    if(m_tile==0)
        m_sprite.setColor(Color(50,50,200));
    else
        m_sprite.setColor(Tile::getTileColor(m_tile->getTile()));
}
void SubTile::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *=  getTransform();
    if (m_isCenter)
    {
        target.draw(m_text, states);
    }
    else
    {
        target.draw(m_sprite, states);
    }
}
Tile* SubTile::getTile() const
{
    return m_tile;
}

Tile::Tile(Tiles tile, int num) : m_tile(tile), m_num(num)
{

}
Tiles Tile::getTile() const
{
    return m_tile;
}
int Tile::getNum() const
{
    return m_num;
}
sf::Color Tile::getTileColor(Tiles tile)
{
    switch(tile)
    {
    case FOREST :
        return Color(50, 200, 50);
        break;
    case MOUNTAIN :
        return Color(127,127,127);
        break;
    case HILL :
        return Color(200,50,50);
        break;
    case FIELD :
        return Color(200,200,50);
        break;
    case MEADOW :
        return Color::Green;
        break;
    case SEA :
        return Color::Blue;
        break;
    default :
        return Color::Cyan;
    }
}

Ressource_graph::Ressource_graph (Ressources res, int x, int y, std::string texturePath) : m_res(res)
{
    if (!m_texture.loadFromFile(texturePath))
        cout<<"erreur chargement sprite res"<<endl;
    m_sprite = Sprite(m_texture);
    m_sprite.setPosition(x,y);
    m_sprite.setColor(getResColor(m_res));
}

void Ressource_graph::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *=  getTransform();
    target.draw(m_sprite, states);
}

sf::Color Ressource_graph::getResColor(Ressources res)
{
    switch(res)
    {
    case WOOD :
        return sf::Color(50, 200, 50);
        break;
    case STONE :
        return sf::Color(127,127,127);
        break;
    case CLAY :
        return sf::Color(200,50,50);
        break;
    case WHEAT :
        return sf::Color(200,200,50);
        break;
    case WOOL :
        return sf::Color::Green;
        break;
    case FISH :
        return sf::Color::Blue;
        break;
    default :
        return sf::Color::Cyan;
    }
}

