#ifndef DRAWBOARD_H
#define DRAWBOARD_H

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QVector>
#include <QWidget>

#include "paintdata.h"

#include "winclient.h"

class DrawBoardArea : public QWidget {
    Q_OBJECT

    WinSocket *client_ptr;

public:

    DrawBoardArea(QWidget *parent = 0);

    /*
     * Public functions:
     * openImage() loads an image from a file;
     * save() writes the currently displayed image to file;
     * clearImage() clears the image displayed in the drawboard area;
     * drawLineTo() does the actual drawing;
     * resizeImage() changes the size of a QImage;
     * print() handles printing.
     */


    bool openImage(const QString &fileName);
    bool saveImage(const QString &fileName, const char *fileFormat);
    void setPenColor(const QColor &newColor);
    void setPenWidth(int newWidth);


    bool isModified() const { return modified; }
    QColor penColor() const { return myPenColor; }
    int penWidth() const { return myPenWidth; }

    void setWinsockPtr(WinSocket *real_client){
        client_ptr = real_client;
    }

    WinSocket *getClientPtr(){
        return client_ptr;
    }

    WinSocket *getClientPtr_PD(){
        return myPaintData.client_ptr;
    }

    void setClientPtr(WinSocket *real_client){
        client_ptr = real_client;
    }

    PaintData myPaintData;

public slots:
    void clearImage();
    void print();


    /*
     * Reimplemented functions:
     *  mousePressEvent(), mouseMoveEvent() and mouseReleaseEvent() are reimplemented to do the drawing;
     *  paintEvent() reimplemented to update the drawboard area;
     *  resizeEvent() ensures that the QImage has at least the size of the widget.
     */


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void drawLineTo(const QPoint &endPoint);
    void recieveData(char *bufferFromServer, int bufferFromServerSize);
    void resizeImage(QImage *image, const QSize &newSize);


    /*
     * Variables' role:
     * modified is true if there are unsaved changes;
     * scribbling is true while the left mouse button is pressed within the drawboard area;
     * penWidth and penColor hold the currently set width and color for the pen;
     * image stores the image drawn by the user;
     * lastPoint holds the position of the cursor at the last mouse press or mouse move event.
     */


    bool modified;
    bool scribbling;
    int myPenWidth;
    QColor myPenColor;
    QImage image;
    QPoint lastPoint;
    QPoint temporaryPoint;

};


#endif // DRAWBOARD_H
