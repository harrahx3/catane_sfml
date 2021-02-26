#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

template <typename T>
bool eraseListElements(std::list<T>& liste, T elementToErase )
{
    cout <<"eraseListElements()\n";
    for(typename list<T>::iterator it = liste.begin(); it!=liste.end(); ++it)
    {
        if (*it == elementToErase)
        {
            liste.erase(it);
            cout << "ressource payee" <<endl;
            return true;
        }
    }
    return false;
}

int main()
{
    srand(time(0));
    std::list<Ressources> a;
    Ressources r = WOOD;
    eraseListElements(a, r);
    int tileSize = 15;
    vector<Ressources> roadPrice;
    roadPrice.push_back(WOOD);
    roadPrice.push_back(CLAY);

    std::vector<Player> players;
    players.push_back(Player(RED,"redP"));
    players.push_back(Player(BLUE, "blueP"));
    players.push_back(Player(YELLOW, "yellowP"));
    players.push_back(Player(WHITE,"whiteP"));

    Market market = Market();
    market.setPosition(20,400);
    Board board = Board(players, market);

    sf::Button nextPlayerButton ("next player","res/BebasNeue-Regular.ttf");
    nextPlayerButton.setPosition(400,100);
    nextPlayerButton.test();

    sf::Button buildButton ("Build","res/Fipps-Regular.otf");
    buildButton.setPosition(400,200);
    bool isBuilding = false;
    sf::Button tradeButton ("Trade","res/Fipps-Regular.otf");
    tradeButton.setPosition(400,300);
    bool isTrading = false;

    cout<<"a"<<endl;
    sf::RenderWindow app(sf::VideoMode(800, 600), "SFML window");
    //bluePlayer.printRessources();

    while (app.isOpen())
    {

        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                app.close();

            if (event.type == sf::Event::Resized)
            {
                // on met à jour la vue, avec la nouvelle taille de la fenêtre
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                app.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                cout<<"click\n";
                if (buildButton.isButtonClicked(app))
                {
                    isBuilding = isBuilding==true ? false : true;
                    cout<<"build : "<<isBuilding<<endl;
                }
                else if (tradeButton.isButtonClicked(app))
                {
                    //  isTrading = isTrading==true ? false : true;
                    board.trade();
                    cout<<"trade : "<<isTrading<<endl;;
                }
                else if (nextPlayerButton.isButtonClicked(app))
                {
                    board.nextPlayer();
                    board.product();
                }
                else //if (isBuilding)
                {
                    cout<<"b"<<endl;
                    int x = ((sf::Mouse::getPosition(app).x - (sf::Mouse::getPosition(app).x % tileSize)) / tileSize);
                    int y = ((sf::Mouse::getPosition(app).y  - (sf::Mouse::getPosition(app).y % tileSize)) / tileSize);
                    board.building(x,y);
                    board.updateMarket(x,y);
                }
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            {
                cout<<"right"<<endl;
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Z)
                {
                    board.m_market.m_selectedPlayer++;
                    //cout << market.m_selectedPlayer << " "<< market.m_players.size() << endl;
                    board.m_market.m_selectedPlayer %= board.m_market.m_players.size();
                    /*  if (market.m_selectedPlayer == market.m_players.end())
                          market.m_selectedPlayer = market.m_players.begin();*/
                }

                int nb = 7; //nb of ressources
                if (event.key.code == sf::Keyboard::X)
                {
                    board.m_market.m_givenRes++;
                    board.m_market.m_givenRes %= nb;
                }
                else if (event.key.code == sf::Keyboard::S)
                {
                    board.m_market.m_receivedRes++;
                    board.m_market.m_receivedRes %= nb;
                }
            }


            /* if (event.type == sf::Event::MouseButtonPressed)
             {
                 board.getCP()->printRessources();
                 int x = ((sf::Mouse::getPosition(app).x - (sf::Mouse::getPosition(app).x % tileSize)) / tileSize);
                 int y = ((sf::Mouse::getPosition(app).y  - (sf::Mouse::getPosition(app).y % tileSize)) / tileSize);
                 board.getCP()->buyElement(board.getElement(x,y), roadPrice);
                 board.getCP()->printRessources();

             }
             if (event.type == sf::Event::KeyPressed)
             {
                 board.getCP()->printRes sources();
                 board.product();
                 board.getCP()->printRessources();

             }*/
        }

        app.clear();

        //board.draw(app, tileSize);
        app.draw(board);
        //  app.draw(market);
        app.draw(nextPlayerButton);
        app.draw(buildButton);
        app.draw(tradeButton);
        app.display();
    }

    return EXIT_SUCCESS;
}
