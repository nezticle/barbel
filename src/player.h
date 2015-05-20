#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"

namespace Qt3D {
    class QCamera;
    class QCylidenrMesh;
}

namespace Barbel {

class Player : public Object
{
    Q_OBJECT
    Q_PROPERTY(Qt3D::QCamera* camera READ camera CONSTANT)
    Q_PROPERTY(float cameraHeight READ cameraHeight WRITE setCameraHeight NOTIFY cameraHeightChanged)
public:
    Player(Qt3D::QEntity *parent = 0);
    ~Player();

    Qt3D::QCamera *camera();

    float cameraHeight() const;

public slots:
    void setCameraHeight(float cameraHeight);

private slots:
    void cameraDebug();

signals:
    void cameraHeightChanged(float cameraHeight);

private:
    Qt3D::QCamera *m_camera;
    float m_cameraHeight;
};

}

#endif // PLAYER_H
