#ifndef IMAGETEXTBROWSER_H
#define IMAGETEXTBROWSER_H

#include <QTextBrowser>
#include <QWidget>

class ImageTextBrowser : public QTextBrowser
{
public:
    ImageTextBrowser(QWidget *parent =  Q_NULLPTR);


    // QTextEdit interface
public:
    QVariant loadResource(int type, const QUrl &name) override;
};

#endif // IMAGETEXTBROWSER_H
