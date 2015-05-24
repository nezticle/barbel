#ifndef OBJECT_H
#define OBJECT_H

#include <Qt3DCore/QNode>
#include <Qt3DCore/QEntity>
#include <QtGui/QVector3D>

namespace Qt3D {
    class QTranslateTransform;
    class QRotateTransform;
    class QScaleTransform;
}

namespace Barbel {

class Object : public Qt3D::QEntity
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QVector3D translation READ translation WRITE setTranslation NOTIFY translationChanged)
    Q_PROPERTY(QVector3D scale READ scale WRITE setScale NOTIFY scaleChanged)
    Q_PROPERTY(QVector3D rotation READ rotation WRITE setRotation NOTIFY rotationChanged)

public:
    Object(Qt3D::QEntity *parent = 0);

    QString name() const;
    QVector3D translation() const;
    QVector3D scale() const;
    QVector3D rotation() const;

public slots:
    void setName(QString name);
    void setTranslation(QVector3D translation);
    void setScale(QVector3D scale);
    void setRotation(QVector3D rotation);

signals:
    void nameChanged(QString name);
    void translationChanged(QVector3D translation);
    void scaleChanged(QVector3D scale);
    void rotationChanged(QVector3D rotation);

private:
    QVector3D m_translation;
    QVector3D m_rotation;
    QVector3D m_scale;

    Qt3D::QTranslateTransform *m_translateTransform;
    Qt3D::QRotateTransform *m_rotateTransformX;
    Qt3D::QRotateTransform *m_rotateTransformY;
    Qt3D::QRotateTransform *m_rotateTransformZ;
    Qt3D::QScaleTransform *m_scaleTransform;
};

}

#endif // OBJECT_H
