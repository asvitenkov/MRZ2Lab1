#include <QApplication>
#include "mainwindow.h"

#include <iostream>
#include <QTime>

using namespace arma;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    
    return a.exec();
}
