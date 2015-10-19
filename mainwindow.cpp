#include <QDebug>
#include <QStringList>
#include <QtPrintSupport/QPrinterInfo>
#include <QFile>
#include <QTextStream>
#include <QHostInfo>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"


//vars config
static QChar _STX = '\x02';
static QString _AUTO_GAP = "C0000"; //Gap Automático
static QString _MANUAL_GAP = "KI503"; //Gap Manual
static QString _AUTO_BACKFEED = "f340"; //BackFeed Automático
static QString _PARAMETER_1 = "00220";
static QString _PARAMETER_2 = "KI7";
static QString _PARAMETER_3 = "V0";
static QString _PARAMETER_4 = "L";
static QString _TEMPERATURE = "H12"; //Parametro de ajuste de temperatura (H10 --> H20)
static QString _PARAMETER_5 = "PA";
static QString _PARAMETER_6 = "A2";
static QString _PARAMETER_7 = "D11";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    listPrinters();
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::on_pushButton_clicked()
{
    this->close();
}

void MainWindow::on_pushButton_2_clicked()
{
    qint32 initial = ui->lineEdit->text().toInt();
    qint32 final = ui->lineEdit_2->text().toInt();

    if ((ui->lineEdit->text() != "") && (ui->lineEdit_2->text() != "")) {
        for (int var = initial; var <= final; ++var) {
            QStringList listValues;

            listValues.append(_STX + _AUTO_GAP);
            //listValues.append(_STX + _MANUAL_GAP);
            listValues.append(_STX + _AUTO_BACKFEED);
            listValues.append(_STX + _PARAMETER_1);
            listValues.append(_STX + _PARAMETER_2);
            listValues.append(_STX + _PARAMETER_3);
            listValues.append(_STX + _PARAMETER_4);
            listValues.append(_TEMPERATURE);
            listValues.append(_PARAMETER_5);
            listValues.append(_PARAMETER_6);
            listValues.append(_PARAMETER_7);
            listValues.append("1E0002000010020" + QString::number(var));
            listValues.append("Q1");
            listValues.append("E");


            QFile file(ui->comboBoxPrinters->currentText());

            if (!file.open(QIODevice::WriteOnly| QIODevice::Text))
                return;

            QTextStream out(&file);

            for (int i = 0; i < listValues.size(); i++) {
                out << listValues.at(i) << endl;
            }

            file.close();
            listValues.clear();
        }
    } else {
        QMessageBox::critical(this, tr("Erro"), tr("Os campos Inicial e Final não devem ser nulos"));
    }
}

void MainWindow::listPrinters()
{
    QList<QPrinterInfo> printerInfo = QPrinterInfo::availablePrinters();

    for (int i = 0; i < printerInfo.size(); ++i) {
        ui->comboBoxPrinters->addItem(printerInfo[i].printerName());
    }

    QString hostname = QHostInfo::localHostName();
    ui->comboBoxPrinters->addItem("\\\\" + hostname + "\\Argox");
}
