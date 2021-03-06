/*
 * Copyright (c) 2015 Andy Nichols
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef SCENE_H
#define SCENE_H

#include <QtCore/QObject>
#include <QtCore/QSize>

namespace Qt3D {
    class QEntity;
    class QFrameGraph;
    class QForwardRenderer;
    class QCamera;
}

namespace Barbel {

class Scene : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSize viewportSize READ viewportSize WRITE setViewportSize NOTIFY viewportSizeChanged)
    Q_PROPERTY(Qt3D::QCamera* activeCamera READ activeCamera WRITE setActiveCamera NOTIFY activeCameraChanged)
public:
    explicit Scene(QObject *parent = 0);
    ~Scene();

    Qt3D::QEntity *rootEnity();
    QSize viewportSize() const;
    Qt3D::QCamera *activeCamera() const;

public slots:
    void setViewportSize(QSize viewportSize);
    void setActiveCamera(Qt3D::QCamera *activeCamera);

signals:
    void viewportSizeChanged(QSize viewportSize);
    void activeCameraChanged(Qt3D::QCamera *activeCamera);

private:
    void initScene();

    Qt3D::QEntity *m_rootEntity;
    Qt3D::QFrameGraph *m_frameGraph;
    Qt3D::QForwardRenderer *m_forwardRenderer;
    Qt3D::QCamera *m_activeCamera;

    float m_cameraAspectRatio;
    QSize m_viewportSize;
};

}

#endif // SCENE_H
