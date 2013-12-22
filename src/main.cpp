#include <QApplication>
#include "mainwindow.h"

#include <iostream>
#include <QTime>

#include "firstreport.h"
#include "secondreport.h"
#include "thirdreport.h"
#include "fourthreport.h"

using namespace std;
using namespace arma;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QVector<int> pVal;
//    pVal << 12 << 14 << 16  << 20 << 24 << 28 << 32 << 40 << 50 << 60;
//    FirstReport firstReport(8, 8, 2000, 0.00005, pVal,":/images/1.jpg","firstReport.cvs");
//    firstReport.run();


//    QVector<QString> images;
//    images << ":/images/1.jpg"
//           << ":/images/2.jpg"
//           << ":/images/3.jpg"
//           << ":/images/4.jpg"
//           << ":/images/5.jpg" ;
//    SecondReport secondReport(8, 8, 1700.0, 0.00005, 16, images,"secondReport.cvs");
//    secondReport.run();

//    ThirdReport thirdReport(8,8,1200,0.00005,16,100,":/images/1.jpg","thirdReport.cvs");
//    thirdReport.run();

//    QVector<double> alphaValues;
//    alphaValues << 0.00005 << 0.00007 << 0.00009 << 0.0001 << 0.0003 << 0.0005 << 0.0007 << 0.0009 << 0.001;
//    FourthReport fourthReport(8,8,1500,alphaValues,16,":/images/1.jpg","fourthReport.cvs");
//    fourthReport.run();

//    return 0;

    MainWindow w;
    w.show();
    
    return a.exec();


}
