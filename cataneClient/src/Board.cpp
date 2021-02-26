#include "inc.h"

using namespace std;
using namespace sf;

sf::Text drawText(sf::Text m_text, std::string text, int x, int y)
{
    m_text.setPosition(x,y);
    m_text.setString(text);
    return m_text;
}


int Board::tileSize = 15;

Board::Board()
{
    cout<<"Board()\n";

}

void Board::dest()
{
    //std::cout << "des\n";
    for (unsigned int i=0; i<m_elements.size(); i++)
        for (unsigned int j=0; j<m_elements[i].size(); j++)
        {
            delete m_elements[i][j];
            m_elements[i][j] = 0;
        }
}

Elements* Board::getElement(int i, int j)
{
    return m_elements[i][j];
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *=  getTransform();

    for (unsigned int i=0; i<m_elements.size(); i++)
        for (unsigned int j=0; j<m_elements[i].size(); j++)
        {
            m_elements[i][j]->setPosition(i*tileSize, j*tileSize);
            m_elements[i][j]->update();
            target.draw(*m_elements[i][j], states);
        }
    //target.draw(*m_currentPlayer, states);

}


void Board::receivePacket(sf::Packet &packet)
{
    std::cout<<"board receiving\n";
    std::vector< std::vector< Elements*> > elmts;

    std::string kind;
    // while (kind!= "endt")
    // {
    std::vector< Elements*> v;

    // while (kind != "endl")
    while (!packet.endOfPacket())
        //for (int i=0; i<2; i++)
    {
        packet >> kind;
        //if (kind != "")
        //std::cout << kind << std::endl;

        if (kind == "subTile")
        {
            sf::Uint32 tile;
            sf::Uint32 num;
            bool isCenter = false;
            sf::Uint32 center;
            packet >> tile >> num >> center;
            if (center != 0)
                isCenter = true;
            v.push_back(new SubTile(new Tile(Tiles(tile), num), isCenter));
            //   std::cout << "sub tile : "<< tile <<"   "<< num<<"  " << isCenter << std::endl;

        }
        else if (kind == "Intersection")
        {
            //sf::Uint32 player;
            //std::string name;
            Player player;
            std::string str;
            // packet >> player;
            packet >> str >> player;
            std::vector<Ressources> price;
            price.push_back(CLAY);
            price.push_back(WOOD);
            v.push_back(new Intersection(new Player(player), price));
            // v.push_back(new Intersection(new Player(Players(player), name), price));
        }
        else if (kind == "Road")
        {
            //sf::Uint32 player;
            //std::string name;
            Player player;
            std::string str;
            // packet >> player;
            packet >> str >> player;// >> name;
            std::vector<Ressources> price;
            price.push_back(CLAY);
            price.push_back(WOOD);
            v.push_back(new Road(new Player(player), price));
        }
        else if (kind == "endl")
        {
            elmts.push_back(v);
            v.clear();

        }
        else
            std::cout << "autre !!\n" << kind << std::endl;

    }
    elmts.push_back(v);
    //}

    dest();
    m_elements = elmts;

}

///////

