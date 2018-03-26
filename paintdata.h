#ifndef PAINTDATA_H
#define PAINTDATA_H

#include <QByteArray>
#include <QColor>
#include <QDataStream>
#include <QPoint>
#include <QVector>
#include <QDebug>

#include "winclient.h"


class PaintData {

public:

    WinSocket *client_ptr;

    PaintData();

    class ShapeModel
    {
    public:
        int penWidth;
        QColor penColor;
        QVector <QPoint> shapeBuffer;
    }Shape;

    int bufferSize;

    QByteArray serializeByteArray;
    QByteArray deserializeByteArray;
    QPoint startPoint;
    QPoint finishPoint;
    QPoint tempPoint;

    void addPoint(const QPoint &newPoint);
    void serializeData();
    void sendData(); //to be coded by Matei
    bool mouseReleasePoint;

    void setClientPtr(WinSocket *real_client){
        client_ptr = real_client;
    }

};

#endif // PAINTDATA_H
