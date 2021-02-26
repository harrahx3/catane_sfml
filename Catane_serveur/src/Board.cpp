#include <SFML/Network.hpp>

#include "C:\Users\Hyacinthe\Documents\projetsCodeblock\Catane_serveur\inc.h"

using namespace std;
using namespace sf;

Board::Board(std::vector<Player> players, Market market) :  m_market(market), m_players(players)
{
    std::cout<<"Board()\n";

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

    for (unsigned int i=0; i<m_players.size(); i++)
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
    m_givenRes = 0;
    m_receivedRes = 0;
    //  m_givenRes = Ressources(0);
    //m_receivedRes = Ressources(0);
    m_selectedPlayer = 0;
    // m_selectedPlayer = m_players.begin();
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
