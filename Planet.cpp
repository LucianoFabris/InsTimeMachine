#include "Planet.h"

#include <QtConcurrent/QtConcurrent>
#include <functional>

Planet::Planet(const double radius, QString texture, const double distanceFromCenter, QNode *parent)  :
    QEntity(parent),
    mTransform(new Qt3DCore::QTransform),
    mMesh(new QSphereMesh),
    mMaterial(new QDiffuseMapMaterial),
    mTexture(new QTextureImage),
    mRotationAngle(0),
    mDistanceFromCenter(distanceFromCenter),
    mRotationAnimation(this, "rotation")
{
    mMesh->setRadius(radius);
    mMesh->setRings(50);
    mMesh->setSlices(50);
    setTexture(texture);

    mRotationAnimation.setLoopCount(-1);
    mRotationAnimation.setStartValue(0);
    mRotationAnimation.setEndValue(360);
    mRotationAnimation.setDuration(4000 * (1 + 20 * mDistanceFromCenter));
    mRotationAnimation.setEasingCurve(QEasingCurve::Linear);
    mRotationAnimation.start();

    mMaterial->setShininess(50);
    mMaterial->setAmbient(QColor(Qt::white));

    addComponent(mTransform);
    addComponent(mMaterial);
    addComponent(mMesh);
}

void Planet::setRotation(const double angle) {
    mRotationAngle = angle;
    mMatrix.setToIdentity();
    mMatrix.rotate(angle, QVector3D(0, 1, 0));
    mMatrix.translate(mDistanceFromCenter, 0, 0);
    mTransform->setMatrix(mMatrix);
}

void Planet::setTexture(const QString &texture) {
    mTexture->setSource(QUrl(texture));
    mMaterial->diffuse()->textureImages().clear();
    mMaterial->diffuse()->addTextureImage(mTexture);
}
