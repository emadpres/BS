#include "thumbnailiconprovider.h"

ThumbnailIconProvider::ThumbnailIconProvider()
{
}

QIcon ThumbnailIconProvider::icon(const QFileInfo & info) const
{
    QIcon realIcon =  QFileIconProvider::icon(info);

    QIcon dummyIcon;
    //QPixmap comboPixmap(32, 32,);
    QPixmap firstImage = realIcon.pixmap(32,32);

    QPixmap secondImage(":/pic/qml/add_pic.png"); //qrc path
    secondImage = secondImage.scaled(16,16);

    QPainter painter(&firstImage);
    //painter.drawPixmap(0, 0, firstImage);
    painter.drawPixmap(0, 0, secondImage);


    //painter.end();

    dummyIcon.addPixmap(firstImage);

    return dummyIcon;
}
