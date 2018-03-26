#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ui_mainwindow.h"

#include "winclient.h"
#include "request.h"

#include <QMainWindow>
#include <QModelIndex>
#include <QList>
#include <QTimer>

class DrawBoardArea;

class MainWindow : public QMainWindow, private Ui::MainWindow {
    Q_OBJECT

public:

    WinSocket client;

    MainWindow(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event) override;

    /*
    /// tree
    void insertChild(const char *filename);
    bool insertColumn();
    void insertRow(const char *filename);
    bool removeColumn();
    void removeRow();
    */

private slots:
    /// drawboard
    void open();
    void save();
    void penColor();
    void penWidth();
    void about();

    void on_view_clicked(const QModelIndex &index);

private:
    void createActions();
    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    QTimer timer;
    DrawBoardArea *drawboardArea;

    QMenu *saveAsMenu;
    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    QAction *newImageAct;
    QAction *openAct;
    QList <QAction *> saveAsActs;
    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *printAct;
    QAction *clearScreenAct;
    QAction *aboutAct;

public slots:
    void updateActions();
    void updateFrame();

public slots:
    void insertChild(const char *filename);
    bool insertColumn();
    void insertRow(const char *filename);
    bool removeColumn();
    void removeRow();


    void on_insertRowAction_triggered();

signals:
    void test();

};

#endif // MAINWINDOW_H
