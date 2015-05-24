#ifndef BARBEL_SERVER_SCENE_H
#define BARBEL_SERVER_SCENE_H

#include <QtCore/QObject>

namespace Barbel {
namespace Server {

class Scene : public QObject
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = 0);

signals:

public slots:
};

}
}

#endif // BARBEL_SERVER_SCENE_H
