#include "EarthWidget.h"

#include <QVBoxLayout>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <QColor>
#include <QMatrix4x4>
#include <stdlib.h>
#include <QPropertyAnimation>

using namespace Qt3DCore;
using namespace Qt3DRender;
using namespace Qt3DExtras;

#include "Planet.h"

EarthWidget::EarthWidget(QWidget *parent) : QWidget(parent)
{
    Qt3DWindow *window = new Qt3DWindow();
    QWidget *windowWidget = QWidget::createWindowContainer(window);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(windowWidget);
    setLayout(layout);

    auto scene = new QEntity;
    window->setRootEntity(scene);

    auto camera = window->camera();
    auto cameraLight = new QPointLight();
    auto cameraController = new QOrbitCameraController(scene);

    camera->setPosition(QVector3D(0, 0,500)); //600.f, 600.0f, 600.0f
    camera->setViewCenter(QVector3D(0.0f,0.0f,0.0f));
    camera->setFarPlane(100000);

    cameraController->setCamera(camera);
    cameraController->setLinearSpeed(1000.0f);
    cameraController->setLookSpeed(1000.0f);

    cameraLight->setIntensity(3);
    cameraLight->setColor(QColor(Qt::white));

    auto galaxyTextureImage = new QTextureImage;
    auto galaxyTextureMaterial = new QTextureMaterial;
    auto galaxyTexture = new QTexture2D;

    galaxyTextureImage->setSource(QUrl(QStringLiteral("qrc:/galaxy-texture.jpg")));
    galaxyTexture->addTextureImage(galaxyTextureImage);
    galaxyTextureMaterial->setTexture(galaxyTexture);

    auto backgroundPlane = new QPlaneMesh;
    auto backgroundTranslation = new Qt3DCore::QTransform;
    auto background = new QEntity(scene);

    backgroundPlane->setWidth(3000);
    backgroundPlane->setHeight(3000);
    background->addComponent(backgroundPlane);
    background->addComponent(galaxyTextureMaterial);
    background->addComponent(backgroundTranslation);
    QMatrix4x4 backRotation;
    backRotation.setToIdentity();
    backRotation.rotate(90, QVector3D(1,0,0));
    backRotation.translate(0, -1000, 0);
    backgroundTranslation->setMatrix(backRotation);

    const double earthRadius = 50;
    const double moonRadius = 25;
    const double moonDistanceToEarth = 100;

    Planet *earth = new Planet(earthRadius, QStringLiteral("qrc:/volcanic-texture.png"), 0, scene); //earthRadius + sunRadius + 0.2579380583*neptuneDistance , sun
    Planet *moon = new Planet(moonRadius, QStringLiteral("qrc:/moon-texture.jpg"), moonDistanceToEarth, earth);  // 2*moonRadius + earthRadius

}
