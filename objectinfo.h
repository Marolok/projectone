#ifndef OBJECTINFO_H
#define OBJECTINFO_H

#include <QWidget>
#include <QString>
#include <QFileDialog>
#include <QComboBox>
#include <QMessageBox>

#include <QTreeView>
#include <QStandardItemModel>
#include <QItemSelectionModel>

#include <QDebug>

#include "bd_api.h"
#include "BDObjects/objects.h"
#include "BDObjects/TypeConst.h"
#include "objquestion.h"

namespace Ui {
class ObjectInfo;
}

class ObjectInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ObjectInfo(BD_API* bd_api,
                        QString name,
                        QString type,
                        QWidget *parent = 0);
    explicit ObjectInfo(BD_API* bd_api, QWidget *parent = 0);

    ~ObjectInfo();

private slots:
    void on_pushButton_6_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_comboBox_activated(int index);

    void on_pushButton_3_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_4_clicked();

private:
    BD_API* bd_api;
    Objects* obj;
    Ui::ObjectInfo *ui;

    void initComboBox();
    void initValues();
    void initTree();

protected:
    void paintEvent(QPaintEvent *);
};

#endif // OBJECTINFO_H
