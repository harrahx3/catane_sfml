#include "Board.h"

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

int Board::throwDice()
{
    return rand()%6 + rand()%6 + 2;
}
void Board::building(int x, int y)
{
    if (x>0 && x<m_width && y>0 && y<m_height)
    {
        m_currentPlayer->buyElement(this->getElement(x,y), this->getElement(x,y)->getPrice());
    }
}
void Board::nextPlayer()
{
    m_currentPlayer++;
    if (m_currentPlayer == m_players.end())
        m_currentPlayer = m_players.begin();
    cout<<endl<<"new player = ";
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
