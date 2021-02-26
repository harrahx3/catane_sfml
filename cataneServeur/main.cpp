#include "inc.h"

/*std::string toString(int a)
{
    std::stringstream ss;
    ss << a;
    std::string str = ss.str();
    return str;
}*/


int main()
{
    const int comPort = 53000;

    std::cout<<"conection...\n";
    std::vector<Client*> clients;
   // Client client (RED, "redP", comPort);
    clients.push_back(new Client(RED, "redP", comPort));
    std::cout<<" 1 connected !\n";
    clients.push_back(new Client(BLUE, "blueP", comPort));
    clients.push_back(new Client(YELLOW, "yellowP", comPort));
   // clients.push_back(new Client(WHITE, "whiteP", comPort));
    std::cout<<"connected !\n";
    //client.send("hello welcome in this app!");
    std::cout<<"sent !\n";

    /*std::vector<Player> players;
    players.push_back(client);
    players.push_back(Player(BLUE, "blueP"));
    players.push_back(Player(YELLOW, "yellowP"));
    players.push_back(Player(WHITE, "whiteP"));*/

    Board board (clients);

    std::cout<<"sending !\n";

    board.play();

    //  Board b1 (board);

    //client.send(board);
    // std::cout<<"sent !\n";

    /*  sf::sleep(sf::milliseconds(100));
          Board b2 (players);

      client.send(b2);
          std::cout<<"sent2 !\n";

      sf::sleep(sf::milliseconds(100));
          Board b3 (players);

      client.send(b3);
      sf::sleep(sf::milliseconds(100));
      std::cout<<"end !\n";*/

    // for (int i=0; i<1; i++)
  /*  while (true)//client.send(board) != sf::Socket::Disconnected)   // Start the game loop
    {

        //client.send("hello welcome in this app!");
        //sf::sleep(sf::milliseconds(100));

        client.send(board);
        client.send(client);
        std::cout<<"sent !\n";

        std::string msg = client.receive<std::string>();
        if (msg == "clic")
        {
            std::vector<sf::Uint32> r = client.receiveT<sf::Uint32>();
            int x = r[0];
            int y = r[1];
            board.building(x, y);
        }
        else if (msg == "nextPlayerButton")
        {
            board.nextPlayer();
            board.product();
        }
    }*/

    board.dest();

    return EXIT_SUCCESS;
}

