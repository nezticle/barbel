#include "testcube.h"

#include <Qt3DRenderer/QCuboidMesh>

Barbel::TestCube::TestCube(const QVector3D &position, const QVector3D &size, Qt3D::QEntity *parent)
    : Object(parent)
{
    setTranslation(position);

    //Add mesh
    Qt3D::QCuboidMesh *cube = new Qt3D::QCuboidMesh();
    cube->setXExtent(size.x());
    cube->setYExtent(size.y());
    cube->setZExtent(size.z());
    addComponent(cube);
}
