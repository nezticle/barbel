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

#include "sceneviewitem.h"
#include "scene.h"

#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFramebufferObject>
#include <QtGui/QOpenGLFramebufferObjectFormat>
#include <QtGui/QSurface>

#include <QtQuick/QQuickWindow>
#include <QtQuick/QSGSimpleTextureNode>

#include <Qt3DCore/QAspectEngine>
#include <Qt3DCore/QEntity>

#include <Qt3DRenderer/QRenderAspect>

class ContextSaver
{
public:
    explicit ContextSaver(QOpenGLContext *context = QOpenGLContext::currentContext())
        : m_context(context)
        , m_surface(context ? context->surface() : Q_NULLPTR)
    {
    }

    ~ContextSaver()
    {
        if (m_context)
            m_context->makeCurrent(m_surface);
    }

    QOpenGLContext *context() const { return m_context; }
    QSurface *surface() const { return m_surface; }

private:
    QOpenGLContext * const m_context;
    QSurface * const m_surface;
};

class FrameBufferObjectRenderer : public QQuickFramebufferObject::Renderer
{
public:
    FrameBufferObjectRenderer(Barbel::SceneViewItem *item,
                              Qt3D::QAspectEngine *aspectEngine,
                              Qt3D::QRenderAspect *renderAspect)
        : m_item(item)
        , m_aspectEngine(aspectEngine)
        , m_renderAspect(renderAspect)
    {
        ContextSaver saver;

        QVariantMap data;
        data.insert(QStringLiteral("surface"), QVariant::fromValue(saver.surface()));
        m_aspectEngine->setData(data);

        m_renderAspect->renderInitialize(saver.context());
        scheduleRootEnityChange();
    }

    void render() Q_DECL_OVERRIDE
    {
        if (m_item->scene() != Q_NULLPTR && m_aspectEngine->rootEntity() != m_item->scene()->rootEnity())
            scheduleRootEnityChange();

        ContextSaver saver;
        Q_UNUSED(saver)

        m_renderAspect->renderSynchronous();

        // We may have called doneCurrent() so restore the context.
        saver.context()->makeCurrent(saver.surface());

        // Reset the state used by the Qt Quick scenegraph to avoid any
        // interference when rendering the rest of the UI.
        m_item->window()->resetOpenGLState();

        update();
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) Q_DECL_OVERRIDE
    {
        QOpenGLFramebufferObjectFormat format;
        format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
        format.setSamples(4);
        return new QOpenGLFramebufferObject(size, format);
    }

    void scheduleRootEnityChange()
    {
        QMetaObject::invokeMethod(m_item, "applyRootEntityChange", Qt::QueuedConnection);
    }

    Barbel::SceneViewItem *m_item;
    Qt3D::QAspectEngine *m_aspectEngine;
    Qt3D::QRenderAspect *m_renderAspect;
};

Barbel::SceneViewItem::SceneViewItem(QQuickItem *parent)
    : QQuickFramebufferObject(parent)
    , m_scene(Q_NULLPTR)
    , m_aspectEngine(new Qt3D::QAspectEngine(this))
    , m_renderAspect(new Qt3D::QRenderAspect(Qt3D::QRenderAspect::Synchronous))
{
    setFlag(ItemHasContents, true);
    m_aspectEngine->registerAspect(m_renderAspect);
    m_aspectEngine->initialize();
}

Barbel::SceneViewItem::~SceneViewItem()
{
    m_renderAspect->renderShutdown();
}

Barbel::Scene *Barbel::SceneViewItem::scene() const
{
    return m_scene;
}

void Barbel::SceneViewItem::setScene(Barbel::Scene *scene)
{
    if (m_scene == scene)
        return;

    m_scene = scene;
    emit sceneChanged(scene);

    update();
}

void Barbel::SceneViewItem::applyRootEntityChange()
{
    if (m_scene != Q_NULLPTR && m_scene->rootEnity() != m_aspectEngine->rootEntity())
        m_aspectEngine->setRootEntity(m_scene->rootEnity());
}

QQuickFramebufferObject::Renderer *Barbel::SceneViewItem::createRenderer() const
{
    Barbel::SceneViewItem *self = const_cast<Barbel::SceneViewItem*>(this);
    return new FrameBufferObjectRenderer(self, m_aspectEngine, m_renderAspect);
}

QSGNode *Barbel::SceneViewItem::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *nodeData)
{
    if (!node) {
        node = QQuickFramebufferObject::updatePaintNode(node, nodeData);
        QSGSimpleTextureNode *textureNode = static_cast<QSGSimpleTextureNode *>(node);
        if (textureNode)
            textureNode->setTextureCoordinatesTransform(QSGSimpleTextureNode::MirrorVertically);
        return node;
    }
    return QQuickFramebufferObject::updatePaintNode(node, nodeData);
}
