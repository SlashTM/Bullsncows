#include "records.h"
#include "QLayout"
#include "QMessageBox"
#include "QHeaderView"
#include "QTextStream"

Records::Records(QWidget *parent) :
    QWidget(parent)
{
    recordlist = new QTableWidget(0,2,this);
    recordlist->setEditTriggers(QAbstractItemView::NoEditTriggers);
    recordlist->setSelectionMode(QAbstractItemView::NoSelection);
    recordlist->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    recordlist->setHorizontalHeaderLabels(QStringList{"Попыток", "Имя"});

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(recordlist);

    QFile file("recordlist.txt");
    if(file.open(QIODevice::ReadOnly)){
        QTextStream input(&file);
        while (!input.atEnd()){
            QTableWidgetItem *att = new QTableWidgetItem();
            att->setData(Qt::DisplayRole, input.readLine().toInt());

            recordlist->setRowCount((recordlist->rowCount()+1));
            recordlist->setItem(recordlist->rowCount()-1,0,att);
            recordlist->setItem(recordlist->rowCount()-1,1,new QTableWidgetItem(input.readLine()));
        }
    }
    file.close();
}

Records::~Records(){}

void Records::addResult(QString name, int attempts){
    QTableWidgetItem *item = new QTableWidgetItem();
    item->setData(Qt::DisplayRole, attempts);

    recordlist->setRowCount(recordlist->rowCount()+1);
    recordlist->setItem(recordlist->rowCount()-1,0,item);
    recordlist->setItem(recordlist->rowCount()-1,1,new QTableWidgetItem(name));
    recordlist->sortItems(0, Qt::AscendingOrder);

    if(recordlist->rowCount()>10)
        recordlist->setRowCount((10));

    QFile file("recordlist.txt");
    if(file.open(QIODevice::WriteOnly)){
        QTextStream output(&file);
        for(int i=0;i<recordlist->rowCount();i++)
            for(int j=0;j<recordlist->columnCount();j++)
                output << recordlist-> item(i,j)->text() << endl;
    }
    file.close();
}
