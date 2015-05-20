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

#include "scene.h"

#include <Qt3DCore/qentity.h>

#include <Qt3DRenderer/qframegraph.h>
#include <Qt3DRenderer/qforwardrenderer.h>

Barbel::Scene::Scene(QObject *parent)
    : QObject(parent)
    , m_rootEntity(new Qt3D::QEntity())
    , m_frameGraph(Q_NULLPTR)
    , m_forwardRenderer(Q_NULLPTR)
{
    initScene();
}

Barbel::Scene::~Scene()
{
    m_rootEntity->deleteLater();
}

Qt3D::QEntity *Barbel::Scene::rootEnity()
{
    return m_rootEntity;
}

void Barbel::Scene::initScene()
{
    //Setup Framegraph
    if (m_frameGraph == Q_NULLPTR)
        m_frameGraph = new Qt3D::QFrameGraph();
    if (m_forwardRenderer == Q_NULLPTR)
        m_forwardRenderer = new Qt3D::QForwardRenderer();

    m_forwardRenderer->setClearColor(Qt::black);
    m_frameGraph->setActiveFrameGraph(m_forwardRenderer);
    m_rootEntity->addComponent(m_frameGraph);
}

