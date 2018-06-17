#ifndef PLANET_H
#define PLANET_H

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

const double frameRate = 30;

class Planet : public QEntity {
    Q_OBJECT
    Q_PROPERTY(double rotation READ rotation WRITE setRotation)

public:
    Planet(const double radius, QString texture, const double distanceFromCenter, QNode *parent = Q_NULLPTR);
    void setTexture(const QString &texture);

    double rotation() const { return mRotationAngle; }
    void setRotation(const double angle);

private:
    Qt3DCore::QTransform *mTransform;
    QSphereMesh *mMesh;
    QDiffuseMapMaterial *mMaterial;
    QTextureImage *mTexture;
    QMatrix4x4 mMatrix;
    double mRotationAngle;
    const double mDistanceFromCenter;
    QPropertyAnimation nPreviousTextureAnimation;
    QPropertyAnimation mNextTextureAnimation;
    QPropertyAnimation mRotationAnimation;
};

#endif // PLANET_H
