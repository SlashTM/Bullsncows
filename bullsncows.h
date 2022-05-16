#ifndef BULLSNCOWS_H
#define BULLSNCOWS_H

#include <QMainWindow>
#include <QValidator>
#include <QRandomGenerator>
#include "records.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Bullsncows; }
QT_END_NAMESPACE

class Bullsncows : public QMainWindow
{
    Q_OBJECT
    friend class Records;
public:
    Bullsncows(QWidget *parent = nullptr);
    ~Bullsncows();


private slots:
    void on_startGame_clicked();

    void on_checkNumber_clicked();

    void on_showRecords_clicked();

signals:
    void playerInfo(QString name, int attempts);

private:
    Ui::Bullsncows *ui;
    QValidator *val;
    Records *record;
    int number = 0;
    int a(int num) const {return num/1000;};
    int b(int num) const {return num/100%10;};
    int c(int num) const {return num/10%10;};
    int d(int num) const {return num%10;};

    bool isPlayable(int number) const;
    int getBulls(int num) const {
        int bulls_ = 0;
        if (a(num) == a(number)) bulls_++;
        if (b(num) == b(number)) bulls_++;
        if (c(num) == c(number)) bulls_++;
        if (d(num) == d(number)) bulls_++;
        return bulls_;};

    int getCows(int num) const {
        int cows_ = 0;
        if (a(num) == b(number)) cows_++;
        if (a(num) == c(number)) cows_++;
        if (a(num) == d(number)) cows_++;
        if (b(num) == a(number)) cows_++;
        if (b(num) == c(number)) cows_++;
        if (b(num) == d(number)) cows_++;
        if (c(num) == a(number)) cows_++;
        if (c(num) == b(number)) cows_++;
        if (c(num) == d(number)) cows_++;
        if (d(num) == a(number)) cows_++;
        if (d(num) == b(number)) cows_++;
        if (d(num) == c(number)) cows_++;
        return cows_;};
};
#endif // BULLSNCOWS_H
