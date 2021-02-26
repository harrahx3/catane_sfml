#include "inc.h"

using namespace std;

class Pl
{
public:
    Pl(bool isIA = false) : m_isIA(isIA)
    {
        if (m_isIA==false)
        {
            sf::TcpListener listener;
            listener.listen(53000);
            Connection(listener);
        }
    }

    bool Connection(sf::TcpListener& listener)
    {
        if (listener.accept(m_socket) == sf::Socket::Done)
            return true;
        return false;
    }

    template <typename T>
    void send (T message)
    {
        if (m_isIA==false)
        {
            sf::Packet packet;
            packet << message;
            m_socket.send(packet);
        }
    }

    template <typename T>
    T receive ()
    {
        if (m_isIA==false)
        {
            sf::Packet packet;
            T data;
            m_socket.receive(packet);
            packet >> data;
            ///return atoi( data.c_str() );
            return data;
        }
        else
        {
            return this->playAuto();
        }
    }

    int playAuto ( )
    {

        return 1;
    }

private:
    sf::TcpSocket m_socket;
    bool m_isIA;
};

int main()
{
    srand(time(0));
    /*cout << "wait for a connection" << endl;
    Player client1 (RED, "redPlayer");
    cout << "one player connected" << endl;
   // UINT32 nbPlayers = client1.receive<UINT32>(grid);
    cout << "wait for a connection" << endl;
    Player client2 (BLUE, "bluePlayer");
    cout << "one player connected" << endl;
    cout << "wait for a connection" << endl;
    Player client3 (WHITE, "whitePlayer");
    cout << "one player connected" << endl;
    cout << "wait for a connection" << endl;
    Player client4 (YELLOW, "yellowPlayer");
    cout << "one player connected" << endl;*/

/*    client1.send<std::string>("connection OK. game begin\n");
    client2.send("connection OK. game begin\n");
    client3.send("connection OK. game begin\n");
    client4.send("connection OK. game begin\n");
*/

    while (1)   // Start the game loop
    {

    }

    return EXIT_SUCCESS;
}
