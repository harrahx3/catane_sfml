#include "inc.h"

using namespace std;
using namespace sf;

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

    if (!m_texture.loadFromFile(texturePath))
        cout<<"erreur chargement sprite Player"<<endl;
    m_sprite = Sprite(m_texture);

    if (!m_font.loadFromFile(fontPath))       ///load the font
        std::cout<<"erreur chargement fonte Player\n";
    else
        m_text.setFont(m_font);
    m_text.setPosition(400,10);
    m_text.setColor(sf::Color::Blue);
    m_text.setCharacterSize(10);
    m_text.setString("a");
    m_text.setFont(m_font);

    m_state = NOTPLAYING;

}

Players Player::getPlayer()
{
    return m_player;
}

State Player::getState()
{
    return m_state;
}
void Player::setState(State state)
{
    m_state = state;
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

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *=  getTransform();
    int i = 500;
    int j = 10;
    int inc = 15;
    //m_ressources.sort();
    /*cout<<m_name<<" : r= ";
    for(list<Ressources>::iterator it = m_ressources.begin(); it!=m_ressources.end(); ++it)
        cout<<*it<<" ; ";
    cout<<endl;*/
    std::list<Ressources> ressources = m_ressources;
    for(std::list<Ressources>::iterator it = ressources.begin(); it!=ressources.end(); ++it)
    {
        i += inc;
        target.draw(Ressource_graph(*it, i, j), states);
    }

    sf::Text text;
    text.setFont(m_font);
    text.setString(m_name);
    text.setPosition(400,10);
    text.setCharacterSize(10);
    target.draw(text, states);
}
std::string Player::getName() const
{
    return m_name;
}


/**
Player::Player(Players player,string name, int points) : m_player(player), m_name(name), m_points(points)
{
    m_ressources.push_back(WOOD);
    m_ressources.push_back(WOOD);
    m_ressources.push_back(CLAY);
    m_ressources.push_back(CLAY);
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

    for (int i=0; i<ressourcesAPayees.size(); i++)
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
    this->printRessources();
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
    for (int i=0; i<ressources.size(); i++)
        if (!eraseListElements(m_ressources_copie, ressources[i]))
            return false;
    cout <<"hasRessources() true\n";
    return true;
}
void Player::printRessources()
{
    cout<<m_name<<" : r= ";
    for(list<Ressources>::iterator it = m_ressources.begin(); it!=m_ressources.end(); ++it)
        cout<<*it<<" ; ";
    cout<<endl;
}

Tile::Tile(Tiles tile, int num) : m_tile(tile), m_num(num)
{

}
Tiles Tile::getTile()
{
    return m_tile;
}
int Tile::getNum()
{
    return m_num;
}

Board::Board()
{
    std::vector<Ressources> roadPrice;
    roadPrice.push_back(WOOD);
    roadPrice.push_back(CLAY);

    std::vector<Ressources> intersectionPrice;
    intersectionPrice.push_back(WOOD);
    intersectionPrice.push_back(CLAY);
    intersectionPrice.push_back(WHEAT);
    intersectionPrice.push_back(WOOL);

    int test = 1;
    //int width = 5;
    //int height = 5;

    Tiles tiles [m_bWidth][m_bHeight] = {{SEA,FIELD,FOREST,FIELD,SEA},{FOREST,FIELD,FOREST,FIELD,HILL},{FOREST,HILL,FOREST,HILL,HILL},{FOREST,FIELD,FOREST,FIELD,HILL},{SEA,SEA,FOREST,SEA,SEA}};

    for (int i=0; i<m_bWidth; i++)
    {
        vector<Tile> v;
        for (int j=0; j<m_bHeight; j++)
        {
            v.push_back(Tile(tiles[i][j]));
        }
        m_tiles.push_back(v);
    }
**/
/*m_tiles.push_back(vector<Tile>(5,Tile(FOREST, 3)));
m_tiles.push_back(vector<Tile>(5,Tile(HILL, 4)));
m_tiles.push_back(vector<Tile>(5,Tile(SEA, 5)));
m_tiles.push_back(vector<Tile>(5,Tile(FIELD, 6)));
m_tiles.push_back(vector<Tile>(5,Tile(MOUNTAIN, 7)));*/


/*
Player redPlayer = Player(RED, "redP");
Player bluePlayer = Player(BLUE, "blueP");
Player yellowPlayer = Player(YELLOW, "yellowP");
Player whitePlayer = Player(WHITE, "whiteP");

vector<Player> players({redPlayer, bluePlayer, yellowPlayer, whitePlayer});
m_players = players;
*/

//  m_players = vector<Player> {Player(RED,"redP"), Player(BLUE,"blueP"), Player(YELLOW,"yellowP"), Player(WHITE,"whiteP

/**  Player players[] = {Player(RED,"redP"), Player(BLUE,"blueP"), Player(YELLOW,"yellowP"), Player(WHITE,"whiteP")};

  for (int i=0; i<4; i++)
      m_players.push_back(players[i]);
**/
/* m_players.push_back(Player(RED,"redP"));
 m_players.push_back(Player(BLUE, "blueP"));
 m_players.push_back(Player(YELLOW, "yellowP"));
 m_players.push_back(Player(WHITE,"whiteP"));*/

/**  m_currentPlayer = m_players.begin();

  for (int i=0; i<m_width; i++)
      for (int j=0; j<m_height; j++)
          m_elements[i][j] = new SubTile(0);

  for (int i=0; i<m_bWidth; i++)
  {
      for (int j=0; j<m_bHeight; j++)
      {
          for (int a=1; a<4; a++)
              for (int b=2; b<5; b++)
              {
                  if ((4*i+2*(j%2)+a) < m_width)
                  {
                      cout<<"a"<<endl;
                      delete m_elements[4*i+2*(j%2)+a +test][4*j+b    +test];
                      m_elements[4*i+2*(j%2)+a    +test][4*j+b    +test] = new SubTile(&m_tiles[i][j]);
                      cout<<"a"<<endl;
                  }
              }
          delete  m_elements[4*i+2*(j%2)+2    +test][4*j+1    +test];
          m_elements[4*i+2*(j%2)+2    +test][4*j+1    +test] = new SubTile(&m_tiles[i][j]);
          delete m_elements[4*i+2*(j%2)+2    +test][4*j+5    +test];
          m_elements[4*i+2*(j%2)+2    +test][4*j+5    +test] = new SubTile(&m_tiles[i][j]);

          if (m_tiles[i][j].getTile() != SEA)
          {
              for (int a=0; a<7; a+=2)
              {
                  if (a == 0 || a == 6)
                  {
                      delete m_elements[4*i+2+2*(j%2) +test][4*j+a    +test];
                      m_elements[4*i+2+2*(j%2)    +test][4*j+a    +test] = new Intersection(0, intersectionPrice);
                  }
                  else
                      for (int b=0; b<5; b+=4)
                      {
                          delete m_elements[4*i+b+2*(j%2) +test][4*j+a    +test];
                          m_elements[4*i+b+2*(j%2)    +test][4*j+a+   test] = new Intersection(0, intersectionPrice);
                      }
              }

              for (int b=1; b<6; b+=2)
              {
                  if (b == 3)
                      for (int a=0; a<5; a+=4)
                      {
                          delete m_elements[4*i+a+2*(j%2) +test][4*j+b    +test];
                          m_elements[4*i+a+2*(j%2)    +test][4*j+b    +test] = new Road (0, roadPrice);
                      }
                  else
                      for (int a=1; a<4; a+=2)
                      {
                          delete m_elements[4*i+a+2*(j%2) +test][4*j+b    +test];
                          m_elements[4*i+a+2*(j%2)    +test][4*j+b   +test] = new Road(0, roadPrice);
                      }
              }
          }
      }
  }
}

Board::~Board()
{
  for (int i=0; i<m_width; i++)
      for (int j=0; j<m_height; j++)
      {
          delete m_elements[i][j];
          m_elements[i][j] = 0;
      }
}

void Board::draw(sf::RenderWindow& app, int tileSize)
{
  for (int i=0; i<m_width; i++)
      for (int j=0; j<m_height; j++)
      {
          sf::Sprite sprite = m_elements[i][j]->draw();
          sprite.setPosition(Vector2f(i*tileSize, j*tileSize));
          app.draw(sprite);
      }
}

Elements* Board::getElement(int i, int j)
{
  return m_elements[i][j];
}

void Board::product()
{
  cout <<"Board::product()\n";
  int randNum = this->throwDice();
  cout<<"randnum= "<<randNum<<endl;
  for (int i=1; i<m_width-1; i++)
      for (int j=1; j<m_height-1; j++)
      {
          m_elements[i][j]->collectProduct(this, i, j, randNum);
      }
}

int Board::throwDice()
{
  return rand()%6 + rand()%6 + 2;
}
void Board::building(int x, int y)
{
  if (x>0 && x<m_width && y>0 && y<m_height)
  {
      m_currentPlayer->buyElement(this->getElement(x,y), this->getElement(x,y)->getPrice());
      m_currentPlayer->printRessources();
  }
}
void Board::nextPlayer()
{
  m_currentPlayer++;
  if (m_currentPlayer == m_players.end())
      m_currentPlayer = m_players.begin();
  cout<<endl<<"new player = ";
  m_currentPlayer->printRessources();
}**/
/*
void Board::play(sf::RenderWindow& app)
{
    int tileSize = 15;
    vector<Ressources> roadPrice;
    roadPrice.push_back(WOOD);
    roadPrice.push_back(CLAY);

    //production
    this->product();

    //commerce

    //construction
    m_currentPlayer->printRessources();
    while (!sf::Mouse::isButtonPressed(Mouse::Right))
    {
        app.clear();
        this->draw(app, tileSize);
        app.display();
        if (sf::Mouse::isButtonPressed(Mouse::Left))
        {
            int x = ((sf::Mouse::getPosition(app).x - (sf::Mouse::getPosition(app).x % tileSize)) / tileSize);
            int y = ((sf::Mouse::getPosition(app).y  - (sf::Mouse::getPosition(app).y % tileSize)) / tileSize);
            if (x>0 && x<m_width && y>0 && y<m_height)
            {
                m_currentPlayer->buyElement(this->getElement(x,y), this->getElement(x,y)->getPrice());
                m_currentPlayer->printRessources();
            }
            while(sf::Mouse::isButtonPressed(Mouse::Left))
            {

            }
        }
    }

    //next player
    m_currentPlayer++;
    if (m_currentPlayer == m_players.end())
        m_currentPlayer = m_players.begin();

}
*/
