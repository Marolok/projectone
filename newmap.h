#ifndef NEWMAP_H
#define NEWMAP_H

#include <QWidget>
#include "mapeditor.h"

namespace Ui {
class NewMap;
}

class NewMap : public QWidget
{
    Q_OBJECT

public:
    explicit NewMap(MapEditor *me, QWidget *parent = 0);
    ~NewMap();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::NewMap *ui;
    MapEditor* me;
};

#endif // NEWMAP_H
