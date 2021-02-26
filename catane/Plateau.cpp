#include "inc.h"

using namespace std;
using namespace sf;

Elements::Elements(string path)
{
    if (!m_texture.loadFromFile(path))
        cout<<"erreur chargement sprite"<<endl;
    m_sprite = Sprite(m_texture);      //m_sprite.setScale(5,5);
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
Tile* Elements::getTile()
{
    return 0;
}
vector<Ressources> Elements::getPrice()
{
    vector<Ressources> v;
    return v;
}

Buyable::Buyable(Player* player, std::vector<Ressources> price, string path) : Elements(path), m_player(player), m_price(price)
{
    /* m_price.push_back(WOOD);
     m_price.push_back(CLAY);*/
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
    return true;
}

Road::Road(Player* player, std::vector<Ressources> price, string path) : Buyable(player, price, path)
{

}
sf::Sprite Road::draw()
{
    if (m_player==0)
        m_sprite.setColor(Color::Cyan);
    else
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
        }
    return m_sprite;
}

Intersection::Intersection(Player* player, std::vector<Ressources>price, string path) : Buyable(player, price, path)
{

}
sf::Sprite Intersection::draw()
{
    if (m_player==0)
        m_sprite.setColor(Color::Cyan);
    else
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
        }
    return m_sprite;
}

bool Intersection::collectProduct(Board* board, int i, int j, int num)
{
    if (m_player!=0)
    {
        // m_player.collectRessource(WHEAT);
        if (board->getElement(i-1,j)->getTile() != 0 && board->getElement(i-1,j)->getTile()->getNum() == num)
            m_player->collectRessource(Ressources(board->getElement(i-1,j)->getTile()->getTile()));
        if (board->getElement(i+1,j)->getTile() != 0 && board->getElement(i+1,j)->getTile()->getNum() == num)
            m_player->collectRessource(Ressources(board->getElement(i+1,j)->getTile()->getTile()));
        if (board->getElement(i,j-1)->getTile() != 0 && board->getElement(i,j-1)->getTile()->getNum() == num)
            m_player->collectRessource(Ressources(board->getElement(i,j-1)->getTile()->getTile()));
        if (board->getElement(i,j+1)->getTile() != 0 && board->getElement(i,j+1)->getTile()->getNum() == num)
            m_player->collectRessource(Ressources(board->getElement(i,j+1)->getTile()->getTile()));
       // m_player->printRessources();
    }
    return true;
}

SubTile::SubTile(Tile* tile, string path) : Elements(path), m_tile(tile)
{

}
sf::Sprite SubTile::draw()
{
    if(m_tile==0)
        m_sprite.setColor(Color(50,50,200));
    else
        switch(m_tile->getTile())
        {
        case FOREST :
            m_sprite.setColor(Color(50, 200, 50));
            break;
        case MOUNTAIN :
            m_sprite.setColor(Color(127,127,127));
            break;
        case HILL :
            m_sprite.setColor(Color(200,50,50));
            break;
        case FIELD :
            m_sprite.setColor(Color(200,200,50));
            break;
        case MEADOW :
            m_sprite.setColor(Color::Green);
            break;
        case SEA :
            m_sprite.setColor(Color::Blue);
            break;
        default :
            m_sprite.setColor(Color::Cyan);
        }
    return m_sprite;
}

Tile* SubTile::getTile()
{
    return m_tile;
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
    cout<<"Board()\n";
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

    Player players[] = {Player(RED,"redP"), Player(BLUE,"blueP"), Player(YELLOW,"yellowP"), Player(WHITE,"whiteP")};

    for (int i=0; i<4; i++)
        m_players.push_back(players[i]);

    /* m_players.push_back(Player(RED,"redP"));
     m_players.push_back(Player(BLUE, "blueP"));
     m_players.push_back(Player(YELLOW, "yellowP"));
     m_players.push_back(Player(WHITE,"whiteP"));*/

    m_currentPlayer = m_players.begin();

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
                        delete m_elements[4*i+2*(j%2)+a +test][4*j+b    +test];
                        m_elements[4*i+2*(j%2)+a    +test][4*j+b    +test] = new SubTile(&m_tiles[i][j]);
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
    m_currentPlayer->drawRessources(app);
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
/*Player* Board::getCP()
{
    return m_currentPlayer;
}*/
int Board::throwDice()
{
    return rand()%6 + rand()%6 + 2;
}
void Board::building(int x, int y)
{
    if (x>0 && x<m_width && y>0 && y<m_height)
    {
        m_currentPlayer->buyElement(this->getElement(x,y), this->getElement(x,y)->getPrice());
//        m_currentPlayer->printRessources();
    }
}
void Board::nextPlayer()
{
    m_currentPlayer++;
    if (m_currentPlayer == m_players.end())
        m_currentPlayer = m_players.begin();
    cout<<endl<<"new player = ";
//    m_currentPlayer->printRessources();
}



/*
//#include "SFML/Graphics/Button.cpp"
Button::Button(std::string text, std::string fontePath)
{
    if (!m_fonte.loadFromFile(fontePath))       ///charger la fonte
        std::cout<<"erreur chargement fonte \n";
    else
        m_text.setFont(m_fonte);
    m_text.setString(text);
    // text.setPosition(10,350);
    //text.setColor(sf::Color::Black);
    //text.setCharacterSize(10);
    m_rect = sf::RectangleShape(sf::Vector2f(m_text.getGlobalBounds().width,m_text.getGlobalBounds().height));
    m_rect.setFillColor(sf::Color::Red);
}
Button::Button(sf::Text text) : m_text(text)
{

}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *=  getTransform();
    target.draw(m_rect, states);
    target.draw(m_text, states);
   // m_rect.transform *= getTransform();
}

sf::Text Button::getText()
{
    return m_text;
}
void Button::setText(sf::Text val)
{
    m_text = val;
}
void Button::setText(std::string newText, sf::Font newFonte)
{
    m_text.setFont(newFonte);
    m_text.setString(newText);
}
bool Button::isButtonClicked(sf::RenderWindow& window)
{
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
        if (mouse.x > this->getPosition().x && mouse.x < (this->getScale().x)*m_rect.getSize().x+this->getPosition().x)
            if (mouse.y > this->getPosition().x && mouse.y < this->getScale().y*m_rect.getSize().y+this->getPosition().x)
                return true;
    }
    return false;
}
*/
