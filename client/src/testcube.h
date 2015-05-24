#ifndef TESTCUBE_H
#define TESTCUBE_H

#include "object.h"

namespace Barbel {

class TestCube : public Barbel::Object
{
public:
    TestCube(const QVector3D &position, const QVector3D &size = QVector3D(1.0f, 1.0f, 1.0f), Qt3D::QEntity *parent = 0);

};

}
#endif // TESTCUBE_H
