#ifndef BARBEL_SERVER_OBJECT_H
#define BARBEL_SERVER_OBJECT_H

#include <QtCore/QObject>
#include <QtGui/QVector3D>

namespace Barbel {
namespace Server {

class Object : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector3D position READ position WRITE setPosition NOTIFY positionChanged)
public:
    explicit Object(QObject *parent = 0);

    QVector3D position() const;

signals:
    void positionChanged(QVector3D position);

public slots:
    void setPosition(QVector3D position);

private:
    QVector3D m_position;
};

}
}

#endif // BARBEL_SERVER_OBJECT_H
