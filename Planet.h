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

const double frameRate = 60;

class Planet : public QEntity {

public:
    void setupRotation()
    {
        mTransformTimer.setInterval((1000/(frameRate*mDistanceFromCenter)) * mDistanceFromCenter);
        mTransformTimer.setSingleShot(false);
        mTransformTimer.start();
        QObject::connect(&mTransformTimer, &QTimer::timeout, [this] {
            mMatrix.setToIdentity();
            mMatrix.rotate(mOrbitRotation, QVector3D(0, 1, 0));
            mMatrix.translate(mDistanceFromCenter, 0, 0);
            mTransform->setMatrix(mMatrix);
            mOrbitRotation = ((mOrbitRotation == 360) ? 0 : mOrbitRotation + 1);
        });
    }

    void setupMaterial(const QString &texture)
    {
        mTexture->setSource(QUrl(texture));
        mMaterial->diffuse()->addTextureImage(mTexture);
        mMaterial->setShininess(50);
        mMaterial->setAmbient(QColor(Qt::white));
    }

    Planet(const double radius, QString texture, const double distanceFromCenter, QNode *parent = Q_NULLPTR) :
        QEntity(parent),
        mTransform(new Qt3DCore::QTransform),
        mPicker(new QObjectPicker),
        mMesh(new QSphereMesh),
        mMaterial(new QDiffuseMapMaterial),
        mSelected(false),
        mTexture(new QTextureImage),
        mOrbitRotation(0),
        mDistanceFromCenter(distanceFromCenter)
    {
        mMesh->setRadius(radius);
        setupMaterial(texture);
        setupRotation();

        addComponent(mTransform);
        addComponent(mPicker);
        addComponent(mMaterial);
        addComponent(mMesh);
    }

    QDiffuseMapMaterial *material() const { return mMaterial; }

private:
    Qt3DCore::QTransform *mTransform;
    QObjectPicker *mPicker;
    QSphereMesh *mMesh;
    QDiffuseMapMaterial *mMaterial;
    bool mSelected;
    QTextureImage *mTexture;
    QMatrix4x4 mMatrix;
    double mOrbitRotation;
    QTimer mTransformTimer;
    QPropertyAnimation nPreviousTextureAnimation;
    QPropertyAnimation mNextTextureAnimation;
    const double mDistanceFromCenter;
};

#endif // PLANET_H
