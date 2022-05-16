#ifndef RECORDS_H
#define RECORDS_H

#include <QWidget>
#include <QTableWidget>
#include <QFile>

namespace Ui {
class Records;
}

class Records : public QWidget
{
    Q_OBJECT
    friend class Bullsncows;
private:
    explicit Records(QWidget *parent = nullptr);
    ~Records();
    QTableWidget *recordlist;
private slots:
    void addResult(QString name, int attempts);
};

#endif // RECORDS_H
