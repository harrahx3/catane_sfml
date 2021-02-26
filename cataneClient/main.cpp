#include "inc.h"

using namespace std;
using namespace sf;

std::vector<Player> receicePlayers(sf::TcpSocket& servor)
{
    cout << "receicePlayers()\n";
    std::vector<Player> players;
    sf::Uint32 nbPlayers;
    sf::Packet packet;
    servor.receive(packet);
    packet >> nbPlayers;
    cout << "receiced Players() : nb = " << nbPlayers <<std::endl;

    for (unsigned int i=0; i<nbPlayers; i++)
    {
        std::cout << "loop pl\n";
        sf::Packet pack;
        servor.receive(pack);
        Player player;
        std::string str;
        pack >> str;
        std::cout << "str pl\n";
        if (str == "player")
        {
            std::cout << "cond pl\n";
            pack >> player;
            std::cout << "received pl\n";
           // player.setPosition(600, 50*i+10);
            players.push_back(player);
        }
        pack.clear();
    }
    return players;
}

void setFonts()
{
    if (!SubTile::m_texture.loadFromFile("res/tile.png"))
        std::cout<<"erreur chargement texture SubTile \n";
    if (!Road::m_texture.loadFromFile("res/road.png"))
        std::cout<<"erreur chargement texture Road \n";
    if (!Intersection::m_texture.loadFromFile("res/intersection.png"))
        std::cout<<"erreur chargement texture Intersection \n";
    if (!SubTile::m_font.loadFromFile("res/Fipps-Regular.otf"))       ///load the font
        std::cout<<"erreur chargement fonte SubTile \n";
    if (!Player::m_texture.loadFromFile("res/tilea.png"))
        cout<<"erreur chargement texture Player"<<endl;
    if (!Player::m_font.loadFromFile("res/Fipps-Regular.otf"))       ///load the font
        std::cout<<"erreur chargement fonte Player\n";
}

int main()
{
    const std::string fontPath = "res/Fipps-Regular.otf";
    setFonts();

    sf::Text text("Catane", Player::m_font);
    text.setPosition(400, 20);
    text.setCharacterSize(15);

    sf::Button nextPlayerButton ("next player", fontPath);
    nextPlayerButton.setPosition(400,200);
    sf::Button tradeButton ("trade", fontPath);
    tradeButton.setPosition(400,300);
    std::vector<sf::Button> buttons;
    buttons.push_back(nextPlayerButton);
    buttons.push_back(tradeButton);


    sf::TcpSocket servor;
    const sf::IpAddress servorAdress = "127.0.0.1";
    ///const sf::IpAddress servorAdress = "192.168.1.51";

    const unsigned short servorPort = 53000;
    std::cout << "connection..\n";
    servor.connect(servorAdress, servorPort);   /// on se connecte au serveur
    std::cout << "connected !\n";
    servor.setBlocking(true);

    Board board;
    Player player;
    player.setPosition(400, 100);
    std::cout << "waiting..\n";
    std::vector<Player> players = receicePlayers(servor);

    sf::VerticalBox plBox;
    for (unsigned int i=0; i<players.size(); i++)
        plBox.m_elmts.push_back(&players[i]);
    plBox.setPosition(700, 10);

    Ressources receivedRessource = Ressources(0);
    Ressources givenRessource = Ressources(0);
    std::vector<Player>::iterator selectedPlayer = players.begin();

    sf::GridLayout grid;

    /* std::vector<sf::Widget*> v;
     sf::Label l1 = sf::Label("You want : ", fontPath);
     v.push_back(&l1);
    //   sf::Icon i1 = Icon();
     Ressource_graph r1 = Ressource_graph(receivedRessource);
     v.push_back(&r1);
     grid.m_elmts.push_back(v);
     std::vector<sf::Widget*> v2;
     sf::Label l2 = sf::Label("From : ", fontPath);
     v2.push_back(&l2);
     v2.push_back(&(*selectedPlayer));
     grid.m_elmts.push_back(v2);
     std::vector<sf::Widget*> v3;
     sf::Label l3 = sf::Label("You give : ", fontPath);
     v3.push_back(&l3);
     Ressource_graph r2 = Ressource_graph(givenRessource);
     v3.push_back(&r2);
     grid.m_elmts.push_back(v3);*/

    grid.setPosition(50, 400);

    /* sf::Uint32 nbPlayers = -1;
     sf::Packet pack;
     servor.receive(pack);
     std::cout << "pack received\n";

     pack >> nbPlayers;*/

    std::cout << "done : " << players.size() << std::endl;

    servor.setBlocking(false);

    sf::RenderWindow app(sf::VideoMode(1000, 600), "SFML window");    // Create the main window

    std::cout << "window created\n";

    std::cout << "begining loop\n";

    while (app.isOpen())    // Start the game loop
    {
        //std::cout << "loop\n";

        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)          // Close window : exit
            {
                servor.disconnect();
                app.close();
            }
            if (event.type == sf::Event::Resized)
            {
                // on met à jour la vue, avec la nouvelle taille de la fenêtre
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                app.setView(sf::View(visibleArea));
            }
            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Packet packet;

                if (nextPlayerButton.isButtonClicked(app))
                {
                    packet << "nextPlayerButton";
                }
                else
                {
                    sf::Uint32 X = sf::Mouse::getPosition(app).x - board.getPosition().x;
                    sf::Uint32 Y = sf::Mouse::getPosition(app).y - board.getPosition().y;
                    sf::Uint32 x = (X - (X % Board::tileSize) ) / Board::tileSize;
                    sf::Uint32 y = (Y - (Y % Board::tileSize) ) / Board::tileSize;
                    std::cout << "clic " << x << " : " << y << std::endl;
                    packet << "clic";
                    servor.send(packet);
                    packet.clear();
                    packet << x << y;
                }

                servor.send(packet);
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::S)
                {
                    selectedPlayer++;
                    if (selectedPlayer == players.end())
                        selectedPlayer = players.begin();
                }

                if (event.key.code == sf::Keyboard::X)
                {
                    givenRessource = Ressources((givenRessource+1) % Ressources(SIZE));
                    cout<<givenRessource<<endl;
                }
                else if (event.key.code == sf::Keyboard::Z)
                {
                    receivedRessource = Ressources((receivedRessource+1) % Ressources(SIZE));
                    cout<<receivedRessource<<endl;

                }
            }
        }

        sf::Packet packet;
        // std::cout<<" receiving\n";

        servor.receive(packet); /// on recoit et affiche les infos du serveur a chque tour
        //std::cout<<"received\n";



        /*  while (!packet.endOfPacket())
          {
          packet >> str;
          //if (str != "")
              std::cout << str << std::endl;
           }
        */

        std::string str;
        if (!packet.endOfPacket())
        {
            packet >> str;
            if (str != "")
                std::cout << str << std::endl;
        }

        if (str == "board")
        {
            packet >> board;
        }
        else if (str == "player")
        {
            packet >> player;
        }
        else if (str == "currentPlayer")
        {
            std::string name;
            packet >> name;
            text.setString("Current player : " + name);
        }
        packet.clear();


        grid.m_elmts.clear();
        std::vector<sf::Widget*> v;
        sf::Label l1 = sf::Label("You want : ", fontPath);
        v.push_back(&l1);
//   sf::Icon i1 = Icon();
        Ressource_graph r1 = Ressource_graph(receivedRessource);
        v.push_back(&r1);
        grid.m_elmts.push_back(v);
        std::vector<sf::Widget*> v2;
        sf::Label l2 = sf::Label("From : ", fontPath);
        v2.push_back(&l2);
        v2.push_back(&(*selectedPlayer));
        grid.m_elmts.push_back(v2);
        std::vector<sf::Widget*> v3;
        sf::Label l3 = sf::Label("You give : ", fontPath);
        v3.push_back(&l3);
        Ressource_graph r2 = Ressource_graph(givenRessource);
        v3.push_back(&r2);
        grid.m_elmts.push_back(v3);


        app.clear();        // Clear screen
        app.draw(board);
        app.draw(nextPlayerButton);
        app.draw(tradeButton);
        app.draw(player);
        app.draw(text);
        /*for(typename std::vector<Player>::iterator it = players.begin(); it!=players.end(); ++it)
        {
            app.draw(*it);
        }*/
        app.draw(plBox);
        app.draw(grid);
        app.display();        // Update the window
        //board.dest();
    }
    board.dest();

    return EXIT_SUCCESS;
}
