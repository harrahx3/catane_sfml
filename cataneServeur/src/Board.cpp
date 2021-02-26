#include "inc.h"

using namespace std;
using namespace sf;

Board::Board(std::vector<Client*> players) :  m_players(players)
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
                do
                {
                    a = rand()%nbbag.size();
                }
                while(nbbag[a]==0);
                tilesBag[Tiles(r)]--;

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

}

/*Board::~Board()
{
    std::cout << "des\n";
    for (int i=0; i<m_width; i++)
        for (int j=0; j<m_height; j++)
        {
            std::cout << "des2\n";
            delete m_elements[i][j];
            m_elements[i][j] = 0;
        }
}*/

void Board::dest()
{
    std::cout << "des\n";
    for (int i=0; i<m_width; i++)
        for (int j=0; j<m_height; j++)
        {
            delete m_elements[i][j];
            m_elements[i][j] = 0;
        }
    for (unsigned int i=0; i<m_players.size(); i++)
    {
        delete m_players[i];
        m_players[i] = 0;
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

        (*m_currentPlayer)->buyElement(this->getElement(x,y), this->getElement(x,y)->getPrice());
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

void Board::toPacket(sf::Packet &packet) const
{
    packet << "board";
    for (int i=0; i<m_width; i++)
    {
        for (int j=0; j<m_height; j++)
        {
            if (m_elements[i][j] != 0)
            {
                packet << *m_elements[i][j];
                // packet << "e";
            }
        }
        packet << "endl";
    }
    packet << "endt";
}

void Board::play()
{
    std::cout << "Board::play()\n";

    for(typename std::vector<Client*>::iterator it = m_players.begin(); it!=m_players.end(); ++it)
    {
        sf::Uint32 nbPlayers = m_players.size();
        (*it)->send(nbPlayers);
        for(unsigned int i=0; i<m_players.size(); i++)
            (*it)->send(*m_players[i]);
    }
    std::cout << "begining loop\n";
    bool go = true;
    while (go)
    {
       // std::cout << "loop it\n";

        for(typename std::vector<Client*>::iterator it = m_players.begin(); it!=m_players.end(); ++it)
        {
            (*it)->send(*this);
            (*it)->send(*(*it));
            std::string name = (*m_currentPlayer)->getName();
            go = (*it)->send(name, "currentPlayer") == sf::TcpSocket::Disconnected ? false : go;
        }

        std::string msg = (*m_currentPlayer)->receive<std::string>();
        if (msg == "clic")
        {
            std::vector<sf::Uint32> r = (*m_currentPlayer)->receiveT<sf::Uint32>();
            int x = r[0];
            int y = r[1];
            building(x, y);
        }
        else if (msg == "nextPlayerButton")
        {
            nextPlayer();
            product();
        }
    }
    for(typename std::vector<Client*>::iterator it = m_players.begin(); it!=m_players.end(); ++it)
    {
        (*it)->disconnect();
    }

}
