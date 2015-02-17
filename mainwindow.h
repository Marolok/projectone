#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPicture>
#include <QImage>
#include <QPainter>
#include <QFileDialog>
#include <QIcon>
#include <QDebug>
#include <QTreeView>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#include "mapeditor.h"
#include "showmap.h"
#include "objectinfo.h"
#include "newmap.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void paintEvent(QPaintEvent *); // пееопределение виртуальной функции
    virtual void mouseMoveEvent(QMouseEvent* pe);
    bool eventFilter(QObject * obj, QEvent *event);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QString backError();

private slots:
    void on_action_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();
    void on_pushButton_5_clicked();
    void on_treeView_activated(const QModelIndex &index);
    void on_treeView_clicked(const QModelIndex &index);
    void on_treeView_doubleClicked(const QModelIndex &index);
    void on_action_4_triggered();
    void on_action_5_triggered();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    MapEditor* me;
    BD_API* bd_api;
    int H;

    QString endActiveObj;
    QString endActiveObjParent;

    int activ_x;
    int activ_y;

    int koord_y;
    int koord_x;
};

#endif // MAINWINDOW_H
