#include "inc.h"

using namespace std;
using namespace sf;

sf::Text drawText(sf::Text m_text, std::string text, int x, int y)
{
    m_text.setPosition(x,y);
    m_text.setString(text);
    return m_text;
}

Board::Board(std::vector<Player> players, Market market) : m_players(players), m_market(market)
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

    std::map<Tiles, int> tilesBag;
    tilesBag[FIELD] = 4;
    tilesBag[FOREST] = 4;
    tilesBag[MEADOW] = 4;
    tilesBag[HILL] = 3;
    tilesBag[MOUNTAIN] = 4;
    // tilesBag[DESERT] = 1;

    int tab[] = {2,3,3,4,4,5,5,6,6,7,8,8,9,9,10,10,11,11,12,1,1,1,1};
    std::vector<int> nbbag;
    for (int unsigned i=0; i<19; i++)
        nbbag.push_back(tab[i]);

    int test = 1;
    //int width = 5;
    //int height = 5;

    // Tiles tiles [m_bWidth][m_bHeight] = {{SEA,FIELD,FOREST,FIELD,SEA},{FOREST,FIELD,FOREST,FIELD,HILL},{FOREST,HILL,FOREST,HILL,HILL},{FOREST,FIELD,FOREST,FIELD,HILL},{SEA,SEA,FOREST,SEA,SEA}};

    for (int i=0; i<m_bWidth; i++)
    {
        vector<Tile> v;
        for (int j=0; j<m_bHeight; j++)
        {
            if ((i==0 && (j==0 || j==m_bHeight-1)) || (i==m_bWidth-1 &&(j==m_bHeight-1 || j==m_bHeight-2 || j==0 || j==1)))
                v.push_back(Tile(Tiles(0)));
            else
            {
                int r;
                int a;
                do
                {
                    r = rand()%tilesBag.size();
                }
                while(tilesBag[Tiles(r)]==0);
                cout<<"a\n";
                do
                {
                    a = rand()%nbbag.size();
                }
                while(nbbag[a]==0);
                std::cout<<"b\n";
                tilesBag[Tiles(r)]--;
                std::cout<<Tiles(r)<<std::endl;
                cout<<nbbag[a]<<endl;

                v.push_back(Tile(Tiles(r),nbbag[a]));
                nbbag[a]=0;
            }
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

    /*Player players[] = {Player(RED,"redP"), Player(BLUE,"blueP"), Player(YELLOW,"yellowP"), Player(WHITE,"whiteP")};

    for (int i=0; i<4; i++)
        m_players.push_back(players[i]);*/

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
                        bool isCenter = (a==2 && b==3 && m_tiles[i][j].getTile()!=SEA);
                        m_elements[4*i+2*(j%2)+a    +test][4*j+b    +test] = new SubTile(&m_tiles[i][j], isCenter);
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

    //  m_market.m_players = &m_players;

    for (int i=0; i<m_players.size(); i++)
    {
        m_market.m_players.push_back(&m_players[i]);
    }
    // m_market.m_selectedPlayer = m_market.m_players[0];

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

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *=  getTransform();
    int tileSize = 15;
    for (int i=0; i<m_width; i++)
        for (int j=0; j<m_height; j++)
        {
            /*sf::Sprite sprite = m_elements[i][j]->draw();
            sprite.setPosition(Vector2f(i*tileSize, j*tileSize));
            target.draw(sprite, states);*/
            m_elements[i][j]->setPosition(i*tileSize, j*tileSize);
            m_elements[i][j]->update();
            target.draw(*m_elements[i][j], states);
        }
    target.draw(*m_currentPlayer, states);
    target.draw(m_market, states);
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
void Board::trade()
{
    m_market.trade(m_currentPlayer);
}
void Board::updateMarket(int x, int y)
{
    m_market.update(x,y);
}

Market::Market(std::string texturePath, std::string fontPath) //: m_players(players), m_tradeButton(tradeButton), m_acceptButton(acceptButton)
{
    // m_tradeButton = Button("Click to trade", fontPath);
    // m_acceptButton = Button("Click to accept the offer", fontPath);

    //  m_tradeButton.setPosition(0,100);
    //  m_acceptButton.setPosition(0,130);

    // m_players = players;

    if (!m_texture.loadFromFile(texturePath))
        cout<<"erreur chargement sprite Market"<<endl;
    m_sprite = Sprite(m_texture);

    if (!m_font.loadFromFile(fontPath))       ///load the font
        std::cout<<"erreur chargement fonte Market \n";
    else
        m_text.setFont(m_font);
    m_text.setColor(sf::Color::Blue);
    m_text.setCharacterSize(10);

    m_givenRes = 0;
    m_receivedRes = 0;
    //  m_givenRes = Ressources(0);
    //m_receivedRes = Ressources(0);
    m_selectedPlayer = 0;
    // m_selectedPlayer = m_players.begin();
}

void Market::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *=  getTransform();

    target.draw(drawText(m_text,"TRADE", 30, 0), states);
    target.draw(drawText(m_text,"You want :", 0, 30), states);

    target.draw(Ressource_graph(Ressources(m_receivedRes), 100, 30), states);

    target.draw(drawText(m_text,"From :", 0, 50), states);
    for(unsigned int i=0; i<m_players.size(); i++)
    {
        target.draw(drawText(m_text,m_players[i]->getName(), (i+1)*100, 50), states);
        //if (*m_selectedPlayer != 0)
        // Player* p= *m_selectedPlayer;
        if (i == m_selectedPlayer)
        {
            sf::RectangleShape rect = RectangleShape();
            rect.setPosition((i+1)*100, 50);
            rect.setFillColor(sf::Color(255,0,0,150));
            rect.setSize(sf::Vector2f(50,20));
            target.draw(rect, states);
        }
    }
    target.draw(drawText(m_text,"You give :", 0,70), states);

    target.draw(Ressource_graph(Ressources(m_givenRes), 100, 70), states);

    //  target.draw(m_tradeButton, states);
    //  target.draw(m_acceptButton, states);
}
void Market::trade(std::vector<Player>::iterator currentPlayer)
{
    std::cout << "trading\n";

    currentPlayer->loseResource(Ressources(m_givenRes));
    // (*m_selectedPlayer)->collectRessource(m_givenRes);
    (m_players[m_selectedPlayer])->collectRessource(Ressources(m_givenRes));
    currentPlayer->collectRessource(Ressources(m_receivedRes));
    (m_players[m_selectedPlayer])->loseResource(Ressources(m_receivedRes));

}
void Market::update(int x, int y)
{

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
