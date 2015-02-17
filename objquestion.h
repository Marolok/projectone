#ifndef OBJQUESTION_H
#define OBJQUESTION_H

#include <QWidget>
#include <QMessageBox>

#include "bd_api.h"
#include "BDObjects/objects.h"
#include "BDObjects/Error.h"

namespace Ui {
class ObjQuestion;
}

class ObjQuestion : public QWidget
{
    Q_OBJECT

public:
    explicit ObjQuestion(BD_API* bd_api, Objects* obj, QWidget *parent = 0);
    ~ObjQuestion();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ObjQuestion *ui;
    BD_API* bd_api;
    Objects* obj;
};

#endif // OBJQUESTION_H
