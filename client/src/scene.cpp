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

#include <Qt3DCore/QEntity>
#include <Qt3DCore/QCamera>

#include <Qt3DRenderer/qframegraph.h>
#include <Qt3DRenderer/qforwardrenderer.h>

#include "object.h"
#include "player.h"
#include "testcube.h"

//Networking
#include "Barbel/clientmanager.h"
#include "Barbel/servermanager.h"
#include <QtNetwork/QHostInfo>

//Debugging
#include <Qt3DCore/QTransform>
#include <Qt3DCore/QTranslateTransform>
#include <Qt3DRenderer/QCylinderMesh>
#include <QtCore/QPropertyAnimation>
#include <QtCore/QSequentialAnimationGroup>
#include <QtCore/QParallelAnimationGroup>
#include <Qt3DRenderer/QPhongMaterial>

Barbel::Scene::Scene(QObject *parent)
    : QObject(parent)
    , m_rootEntity(new Qt3D::QEntity())
    , m_frameGraph(Q_NULLPTR)
    , m_forwardRenderer(Q_NULLPTR)
    , m_activeCamera(Q_NULLPTR)
    , m_player(Q_NULLPTR)
    , m_cameraAspectRatio(3.0 / 4.0)
    , m_serverManager(Q_NULLPTR)
    , m_clientManager(new Barbel::ClientManager(this))

{
    initScene();
    //initTestData();
}

Barbel::Scene::~Scene()
{
    m_rootEntity->deleteLater();
}

Qt3D::QEntity *Barbel::Scene::rootEnity()
{
    return m_rootEntity;
}

QSize Barbel::Scene::viewportSize() const
{
    return m_viewportSize;
}

Qt3D::QCamera* Barbel::Scene::activeCamera() const
{
    return m_activeCamera;
}

Barbel::ClientManager *Barbel::Scene::clientManager() const
{
    return m_clientManager;
}

void Barbel::Scene::setViewportSize(QSize viewportSize)
{
    if (m_viewportSize == viewportSize)
        return;

    m_viewportSize = viewportSize;
    m_cameraAspectRatio = (float)viewportSize.width() / (float)viewportSize.height();

    if (m_activeCamera != Q_NULLPTR) {
        m_activeCamera->lens()->setAspectRatio(m_cameraAspectRatio);
    }

    emit viewportSizeChanged(viewportSize);
}

void Barbel::Scene::setActiveCamera(Qt3D::QCamera *activeCamera)
{
    if (m_activeCamera == activeCamera)
        return;

    m_activeCamera = activeCamera;
    m_activeCamera->lens()->setAspectRatio(m_cameraAspectRatio);
    m_forwardRenderer->setCamera(m_activeCamera);
    emit activeCameraChanged(activeCamera);
}

void Barbel::Scene::startSinglePlayerSession()
{
    //Start both the client and server locally only
    if (m_serverManager != Q_NULLPTR)
        delete m_serverManager;

    m_serverManager = new Barbel::ServerManager(this);
    if (m_serverManager->listen(QHostAddress::LocalHost)) {
        quint16 localPort = m_serverManager->serverPort();
        m_clientManager->connectToHost(QHostAddress::LocalHost, localPort);
    } else {
        //Could not create a server
        qDebug() << "Something is busted, couldn't start a local-player session";
    }
}

void Barbel::Scene::hostMultiPlayerSession(quint16 port)
{
    //Start both the client and server (Open)
    if (m_serverManager != Q_NULLPTR)
        delete m_serverManager;

    m_serverManager = new Barbel::ServerManager(this);
    if (m_serverManager->listen(QHostAddress::Any, port)) {
        quint16 localPort = m_serverManager->serverPort();
        m_clientManager->connectToHost(QHostAddress::LocalHost, localPort);
    } else {
        //Could not create a server
        qDebug() << "Something is busted, couldn't start a local-player session";
    }
}

void Barbel::Scene::joinMultiPlayerSession(const QString &address, quint16 port)
{
    if (m_serverManager != Q_NULLPTR)
        delete m_serverManager;

    QHostInfo hostInfo = QHostInfo::fromName(address);

    //Start only the client manager
    m_clientManager->connectToHost(hostInfo.addresses().first(), port);
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

    //Test Objects
    m_player = new Barbel::Player(m_rootEntity);
    m_player->setTranslation(QVector3D(0.0f, 0.0f, 0.0f));
    setActiveCamera(m_player->camera());
    activeCamera()->lens()->setAspectRatio(m_cameraAspectRatio);
}

void Barbel::Scene::initTestData()
{
    QVector3D startPostion(0.0f, 0.0f, 0.0f);
    QVector3D secondPosition(10.0f, 10.0f, 10.0f);
    QVector3D thirdPosition(-10.0f, 0.0f, 10.0f);

    QVector3D startAngles(0.0f, 0.0f, 0.0f);
    QVector3D secondAngles(45.0f, 150.0f, 0.0f);
    QVector3D thirdAngles(0.0f, 200.0f, 0.0f);
    QVector3D finalAngles(0.0f, 360.0f, 0.0f);


    QSequentialAnimationGroup *animationGroup = new QSequentialAnimationGroup(this);

    QParallelAnimationGroup *parallelAnimationGroup1 = new QParallelAnimationGroup(this);

    QPropertyAnimation *animation = new QPropertyAnimation(m_player, "translation", this);
    animation->setDuration(5000);
    animation->setStartValue(startPostion);
    animation->setEndValue(secondPosition);
    parallelAnimationGroup1->addAnimation(animation);

    QPropertyAnimation *rotationAnimation = new QPropertyAnimation(m_player, "rotation", this);
    rotationAnimation->setDuration(5000);
    rotationAnimation->setStartValue(startAngles);
    rotationAnimation->setEndValue(secondAngles);
    parallelAnimationGroup1->addAnimation(rotationAnimation);

    animationGroup->addAnimation(parallelAnimationGroup1);

    QParallelAnimationGroup *parallelAnimationGroup2 = new QParallelAnimationGroup(this);

    animation = new QPropertyAnimation(m_player, "translation", this);
    animation->setDuration(5000);
    animation->setStartValue(secondPosition);
    animation->setEndValue(thirdPosition);
    parallelAnimationGroup2->addAnimation(animation);

    rotationAnimation = new QPropertyAnimation(m_player, "rotation", this);
    rotationAnimation->setDuration(5000);
    rotationAnimation->setStartValue(secondAngles);
    rotationAnimation->setEndValue(thirdAngles);
    parallelAnimationGroup2->addAnimation(rotationAnimation);

    animationGroup->addAnimation(parallelAnimationGroup2);
    QParallelAnimationGroup *parallelAnimationGroup3 = new QParallelAnimationGroup(this);

    animation = new QPropertyAnimation(m_player, "translation", this);
    animation->setDuration(5000);
    animation->setStartValue(thirdPosition);
    animation->setEndValue(startPostion);
    parallelAnimationGroup3->addAnimation(animation);

    rotationAnimation = new QPropertyAnimation(m_player, "rotation", this);
    rotationAnimation->setDuration(5000);
    rotationAnimation->setStartValue(thirdAngles);
    rotationAnimation->setEndValue(finalAngles);
    parallelAnimationGroup3->addAnimation(rotationAnimation);

    animationGroup->addAnimation(parallelAnimationGroup3);
    animationGroup->setLoopCount(-1);
    animationGroup->start();

    //Test Cubes
    Qt3D::QPhongMaterial *phongMaterial1 = new Qt3D::QPhongMaterial();
    phongMaterial1->setDiffuse(QColor(94, 141, 25));
    phongMaterial1->setSpecular(Qt::white);
    Qt3D::QPhongMaterial *phongMaterial2 = new Qt3D::QPhongMaterial();
    phongMaterial2->setDiffuse(QColor(129, 23, 71));
    phongMaterial2->setSpecular(Qt::white);

    for (int z = -5; z < 5; z++) {
        for (int y = -5; y < 5; y++) {
            for (int x = -5; x < 5; x++) {
                float xSize = (rand() % 10000) / 10000.0;
                float ySize = (rand() % 10000) / 10000.0;
                float zSize = (rand() % 10000) / 10000.0;
                Barbel::TestCube *cube = new TestCube(QVector3D(x, y, z), QVector3D(xSize, ySize, zSize), m_rootEntity);
                if (y % 2)
                    cube->addComponent(phongMaterial1);
                else
                    cube->addComponent(phongMaterial2);
            }
        }
    }

    this->startSinglePlayerSession();
}

