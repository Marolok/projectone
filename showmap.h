#ifndef SHOWMAP_H
#define SHOWMAP_H

#include <QWidget>
#include <QString>

namespace Ui {
class showmap;
}

class showmap : public QWidget
{
    Q_OBJECT

public:
    explicit showmap(QWidget *parent = 0);
    explicit showmap(QWidget *parent, QString str, QString file);
    ~showmap();

private slots:
    void on_pushButton_clicked();

private:
    Ui::showmap *ui;
};

#endif // SHOWMAP_H
