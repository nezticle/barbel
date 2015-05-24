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

#ifndef SCENEVIEWITEM_H
#define SCENEVIEWITEM_H

#include <QtQuick/QQuickFramebufferObject>

namespace Qt3D {
    class QAspectEngine;
    class QEntity;
    class QRenderAspect;
}

namespace Barbel {

class Scene;

class SceneViewItem : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(Barbel::Scene* scene READ scene WRITE setScene NOTIFY sceneChanged)
public:
    SceneViewItem(QQuickItem *parent = 0);
    ~SceneViewItem();

    Barbel::Scene *scene() const;

public slots:
    void setScene(Barbel::Scene* scene);

private slots:
    void applyRootEntityChange();

signals:
    void sceneChanged(Barbel::Scene* scene);

protected:
    Renderer *createRenderer() const Q_DECL_OVERRIDE;
    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *nodeData) Q_DECL_OVERRIDE;

private:
    Barbel::Scene *m_scene;

    Qt3D::QAspectEngine *m_aspectEngine;
    Qt3D::QRenderAspect *m_renderAspect;
};

}

#endif // SCENEVIEWITEM_H
