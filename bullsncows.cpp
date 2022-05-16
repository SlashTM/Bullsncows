#include "bullsncows.h"
#include "ui_bullsncows.h"
#include "QMessageBox"
#include "QInputDialog"

Bullsncows::Bullsncows(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Bullsncows)
{
    ui->setupUi(this);

    record = new Records();
    record->resize(400,500);

    ui->gameField->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->checkNumber->setDisabled(true);
    ui->inputLine->setReadOnly(true);

    QStringList labels_;
    labels_ << "Число" << "Быки" << "Коровы";
    ui->gameField->setHorizontalHeaderLabels(labels_);

    val = new QRegExpValidator(QRegExp("^[0-9]{4}$"));
    ui->inputLine->setValidator(val);

    connect(this,&Bullsncows::playerInfo, record, &Records::addResult);
}

Bullsncows::~Bullsncows()
{
    delete ui;
}


void Bullsncows::on_startGame_clicked()
{
    QRandomGenerator *number_ = QRandomGenerator::global();
    while(!isPlayable(number)){
        number = number_->bounded(10000);
    }
    ui->statusLabel->setText("Игра началась!");
    ui->checkNumber->setDisabled(false);
    ui->inputLine->setReadOnly(false);
    ui->gameField->setRowCount(0);
}

bool Bullsncows::isPlayable(int number) const {
    if (number/1000 == number/100%10 || number/1000 == number/10%10 || number/1000 == number%10 ||
            number/100%10 == number/10%10 || number/100%10 == number%10 || number/10%10 == number%10)
            return false;
        else return true;
}

void Bullsncows::on_checkNumber_clicked()
{
    if (isPlayable(ui->inputLine->text().toInt())){
        ui->gameField->setRowCount(ui->gameField->rowCount()+1);
        ui->gameField->setItem(ui->gameField->rowCount()-1, 0, new QTableWidgetItem(ui->inputLine->text()));
        ui->gameField->setItem(ui->gameField->rowCount()-1, 1, new QTableWidgetItem(QString::number(getBulls(ui->inputLine->text().toInt()))));
        ui->gameField->setItem(ui->gameField->rowCount()-1, 2, new QTableWidgetItem(QString::number(getCows(ui->inputLine->text().toInt()))));
        ui->gameField->scrollToBottom();
        if(number == ui->inputLine->text().toInt()){
            QMessageBox::information(this, "Вы победили!", "Искомое число - " + QString::number(number)
                                     + "\nПопыток - " + QString::number(ui->gameField->rowCount()));
            ui->inputLine->setReadOnly(true);
            ui->checkNumber->setDisabled(true);
            if (record->recordlist->rowCount()<10 || (ui->gameField->rowCount() < record->recordlist->item(9,0)->text().toInt())){
                bool Ok;
                QString name = QInputDialog::getText(0, "Список лидеров", "Введите имя", QLineEdit::Normal, "", &Ok);
                if (Ok){
                    if(name.isEmpty())
                        name = "аноним";
                    emit playerInfo(name, ui->gameField->rowCount());
                }
                else
                    QMessageBox::information(this, 0, "Ваш результат не будет сохранён");
            }

            ui->statusLabel->setText("Сыграем ещё?");
        }
        ui->inputLine->setText("");

    }
    else {
        QMessageBox::warning(this, "Ошибка", "Введите четырёхзначное число без повторяющихся цифр");
        ui->inputLine->setText("");
    }
}

void Bullsncows::on_showRecords_clicked()
{
    record->show();
}
