#include "player.h"

#include <Qt3DCore/QCamera>
#include <Qt3DCore/QCameraLens>

#include <QtCore/QDebug>

Barbel::Player::Player(Qt3D::QEntity *parent)
    : Barbel::Object(parent)
    , m_camera(new Qt3D::QCamera(this))
    , m_cameraHeight(1.0f)
{
    m_camera->setProjectionType(Qt3D::QCameraLens::PerspectiveProjection);
    m_camera->setPosition(QVector3D(0.0f, m_cameraHeight, 0.0f));
    m_camera->setUpVector(QVector3D(0, 1, 0));
    m_camera->lens()->setFieldOfView(45.0f);
    m_camera->lens()->setNearPlane(0.1f);
    m_camera->lens()->setFarPlane(1000.0f);
    m_camera->setViewCenter(QVector3D(1.0f, 0.0f, 0.0f) + m_camera->position());

    connect(m_camera, SIGNAL(positionChanged()), this, SLOT(cameraDebug()));
}

Barbel::Player::~Player()
{

}

Qt3D::QCamera *Barbel::Player::camera()
{
    return m_camera;
}

float Barbel::Player::cameraHeight() const
{
    return m_cameraHeight;
}

void Barbel::Player::setCameraHeight(float cameraHeight)
{
    if (m_cameraHeight == cameraHeight)
        return;

    m_cameraHeight = cameraHeight;
    m_camera->setPosition(QVector3D(0.0f, m_cameraHeight, 0.0f));
    emit cameraHeightChanged(cameraHeight);
}

void Barbel::Player::cameraDebug()
{
    qDebug() << m_camera->position();
}
