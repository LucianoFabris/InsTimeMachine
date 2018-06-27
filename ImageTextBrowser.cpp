#include "ImageTextBrowser.h"

#include <QImage>
#include <QUrl>

ImageTextBrowser::ImageTextBrowser(QWidget *parent) :
    QTextBrowser(parent)
{

}

QVariant ImageTextBrowser::loadResource(int type, const QUrl &name)
{
    if(type == QTextDocument::ImageResource) {
        QImage i(":/"+name.path());
        return i;
    } else {
        return QTextBrowser::loadResource(type, name);
    }
}
