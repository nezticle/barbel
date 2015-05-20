#include "object.h"

#include <Qt3DCore/QTranslateTransform>
#include <Qt3DCore/QRotateTransform>
#include <Qt3DCore/QScaleTransform>
#include <Qt3DCore/QTransform>

Barbel::Object::Object(Qt3D::QEntity *parent)
    : Qt3D::QEntity(parent)
    , m_translation(QVector3D(0.0, 0.0, 0.0))
    , m_rotation(QVector3D(0.0, 0.0, 0.0))
    , m_scale(QVector3D(1.0, 1.0, 1.0))
    , m_translateTransform(new Qt3D::QTranslateTransform())
    , m_rotateTransformX(new Qt3D::QRotateTransform())
    , m_rotateTransformY(new Qt3D::QRotateTransform())
    , m_rotateTransformZ(new Qt3D::QRotateTransform())
    , m_scaleTransform(new Qt3D::QScaleTransform())
{
    //Create Transforms Components
    Qt3D::QTransform *transformComponent = new Qt3D::QTransform();
    addComponent(transformComponent);

    transformComponent->addTransform(m_translateTransform);
    m_translateTransform->setTranslation(m_translation);

    transformComponent->addTransform(m_rotateTransformX);
    m_rotateTransformX->setAxis(QVector3D(1.0f, 0.0f, 0.0f));
    m_rotateTransformX->setAngleDeg(m_rotation.x());

    transformComponent->addTransform(m_rotateTransformY);
    m_rotateTransformY->setAxis(QVector3D(0.0f, 1.0f, 0.0f));
    m_rotateTransformY->setAngleDeg(m_rotation.y());

    transformComponent->addTransform(m_rotateTransformZ);
    m_rotateTransformZ->setAxis(QVector3D(0.0f, 0.0f, 1.0f));
    m_rotateTransformZ->setAngleDeg(m_rotation.z());

    transformComponent->addTransform(m_scaleTransform);
    m_scaleTransform->setScale3D(m_scale);

    //Give the object a decent default name
    static quint64 objectCounter;
    this->setObjectName(QString("object" + QString::number(objectCounter)));
}

QString Barbel::Object::name() const
{
    return objectName();
}

QVector3D Barbel::Object::translation() const
{
    return m_translation;
}

QVector3D Barbel::Object::scale() const
{
    return m_scale;
}

QVector3D Barbel::Object::rotation() const
{
    return m_rotation;
}

void Barbel::Object::setName(QString name)
{
    if (objectName() == name)
        return;

    setObjectName(name);
    emit nameChanged(name);
}

void Barbel::Object::setTranslation(QVector3D translation)
{
    if (m_translation == translation)
        return;

    m_translation = translation;
    m_translateTransform->setTranslation(m_translation);
    emit translationChanged(translation);
}

void Barbel::Object::setScale(QVector3D scale)
{
    if (m_scale == scale)
        return;

    m_scale = scale;
    m_scaleTransform->setScale3D(m_scale);
    emit scaleChanged(scale);
}

void Barbel::Object::setRotation(QVector3D rotation)
{
    if (m_rotation == rotation)
        return;

    m_rotation = rotation;
    m_rotateTransformX->setAngleDeg(m_rotation.x());
    m_rotateTransformY->setAngleDeg(m_rotation.y());
    m_rotateTransformZ->setAngleDeg(m_rotation.z());
    emit rotationChanged(rotation);
}
