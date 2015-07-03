#include "player.h"

Barbel::Server::Player::Player()
{

}

QString Barbel::Server::Player::name() const
{
    return m_name;
}

void Barbel::Server::Player::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(name);
}
