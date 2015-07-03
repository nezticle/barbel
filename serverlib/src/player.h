#ifndef BARBEL_SERVER_PLAYER_H
#define BARBEL_SERVER_PLAYER_H

#include "object.h"

namespace Barbel {
namespace Server {

class Player : public Barbel::Server::Object
{
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    Player();
    QString name() const;
public slots:
    void setName(QString name);
signals:
    void nameChanged(QString name);
private:
    QString m_name;
};

}
}

#endif // BARBEL_SERVER_PLAYER_H
