#include "object.h"

Barbel::Server::Object::Object(QObject *parent)
    : QObject(parent)
{

}

QVector3D Barbel::Server::Object::position() const
{
    return m_position;
}

void Barbel::Server::Object::setPosition(QVector3D position)
{
    if (m_position == position)
        return;

    m_position = position;
    emit positionChanged(position);
}
