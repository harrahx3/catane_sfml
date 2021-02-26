#include "inc.h"

Client::Client(Players player, std::string name, int comPort) :Player(player, name)
{
    sf::TcpListener listener;
    listener.listen(comPort);
    Connection(listener);
}

bool Client::Connection(sf::TcpListener& listener)
{
    if (listener.accept(m_socket) == sf::Socket::Done)
        return true;
    return false;

}
