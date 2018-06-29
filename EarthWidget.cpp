#include "EarthWidget.h"

#include <QVBoxLayout>
#include <Qt3DCore>
#include <Qt3DExtras>
#include <Qt3DRender>
#include <QColor>
#include <QMatrix4x4>
#include <stdlib.h>
#include <QPropertyAnimation>

#include "EventDescriptionView.h"

using namespace Qt3DCore;
using namespace Qt3DRender;
using namespace Qt3DExtras;

EarthWidget::EarthWidget(QWidget *parent) : QWidget(parent)
{
    Qt3DWindow *window = new Qt3DWindow();
    QWidget *windowWidget = QWidget::createWindowContainer(window);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->addWidget(windowWidget);
    setLayout(layout);
    setFocusPolicy(Qt::NoFocus);

    auto scene = new QEntity;
    window->setRootEntity(scene);

    auto camera = window->camera();
    auto cameraLight = new QPointLight();
//    auto cameraController = new QOrbitCameraController(scene);

    camera->setPosition(QVector3D(0, 0,500));
    camera->setViewCenter(QVector3D(-85.0f,0.0f,0.0f));
    camera->setFarPlane(100000);

//    QMatrix4x4 translationMatrix;
//    translationMatrix.setToIdentity();
//    translationMatrix.translate(200,0,0)|
//    camera->transform()->setMatrix(translationMatrix);

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
    const double moonRadius = 15;
    const double moonDistanceToEarth = 100;

    earth = new Planet(earthRadius, QStringLiteral("qrc:/volcanic-texture.png"), 0, scene);
    moon = new Planet(moonRadius, QStringLiteral("qrc:/moon-texture.jpg"), moonDistanceToEarth, earth);
}

void EarthWidget::setEarthPeriod(const QModelIndex &index) {
    earth->setTexture(index.data(GeologicalPeriodsModel::TextureRole).toString());
}
