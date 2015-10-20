#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>


//teste
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load("SeqEtq_Default");
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
