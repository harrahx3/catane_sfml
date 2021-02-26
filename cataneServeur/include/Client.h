#ifndef CLIENT_H
#define CLIENT_H

#include "inc.h"

class Client : public Player
{
public :
    Client(Players player, std::string name, int comPort=53000);

    bool Connection(sf::TcpListener& listener);

    template <typename T>
    sf::Socket::Status send (T& obj, std::string start="")
    {
        sf::Packet packet;
        if (start != "")
            packet << start;
        packet << obj;
        //std::cout << "b\n";
        return m_socket.send(packet);
    }

    template <typename T>
    std::vector<T> receiveT ()
    {
        sf::Packet packet;
        std::vector<T> data;
        m_socket.receive(packet);
        while (!packet.endOfPacket())
        {
            T d;
            packet >> d;
            data.push_back(d);
        }
        return data;
    }

    template <typename T>
    T receive ()
    {
        sf::Packet packet;
        m_socket.receive(packet);
        T data;
        if (!packet.endOfPacket())
            packet >> data;
        return data;
    }

    void disconnect()
    {
        m_socket.disconnect();
    }

private:
    sf::TcpSocket m_socket;
};


#endif // CLIENT_H
