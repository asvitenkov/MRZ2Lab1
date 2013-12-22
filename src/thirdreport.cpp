#include "thirdreport.h"

#include <QDebug>


#include <neuralnetwork.h>

ThirdReport::ThirdReport(int n, int m, double error, double alpha, int pValue, double errorStep, const QString &img, const QString &outFileName)
    : QObject(0)
{
    mM = m;
    mN = n;
    mError = error;
    mAlpha = alpha;
    mPValue = pValue;
    mOutFileName = outFileName;
    mImgName = img;
    mErrorStep = errorStep;
}



ThirdReport::~ThirdReport()
{

}


void ThirdReport::run()
{
    QImage img(mImgName);

    if (img.isNull())
    {
       qDebug() << QString("Can not open image %1").arg(mImgName);
        return;
    }

    mFile.setFileName(mOutFileName);

    mFile.open(QIODevice::WriteOnly);

    QTextStream out(&mFile);

    out << "N, M, P, Alpha, Error, Z, It\n";

    execute(mN, mM, mError, mAlpha, mPValue, img, out);

    mFile.close();
}


void ThirdReport::execute(int n, int m, double error, double alpha, int pValue, const QImage &img, QTextStream &out)
{
    CImage image = CImage::fromImage(img);
    QVector<Segment*>* vec = image.split(n,m);

    CNeuralNetwork network(n*m*3, pValue, alpha);

    double e = network.getError(*vec);

//    double step;
    double oldError = e;
    double z = ( (double) (m*n + vec->size()) * pValue + 2 ) / (m * n * vec->size());

    while(e > error)
    {
        if( oldError - e >= mErrorStep)
        {
            out << QString("%1, %2, %3, %4, %5, %6, %7\n")
                                   .arg(QString::number(n))
                                   .arg(QString::number(m))
                                   .arg(QString::number(pValue))
                                   .arg(QString::number(alpha,'f',7))
                                   .arg(QString::number(e))
                                   .arg(QString::number(z))
                                   .arg(QString::number(network.getStep()));
            qDebug() << QString("%1, %2, %3, %4, %5, %6, %7\n")
                                   .arg(QString::number(n))
                                   .arg(QString::number(m))
                                   .arg(QString::number(pValue))
                                   .arg(QString::number(alpha,'f',7))
                                   .arg(QString::number(e))
                                   .arg(QString::number(z))
                                   .arg(QString::number(network.getStep()));
            oldError = e;
        }
        network.learn(*vec);
        e = network.getError(*vec);
    }


    out << QString("%1, %2, %3, %4, %5, %6, %7\n")
                           .arg(QString::number(n))
                           .arg(QString::number(m))
                           .arg(QString::number(pValue))
                           .arg(QString::number(alpha,'f',7))
                           .arg(QString::number(e))
                           .arg(QString::number(z))
                           .arg(QString::number(network.getStep()));
    qDebug() << QString("%1, %2, %3, %4, %5, %6, %7\n")
                           .arg(QString::number(n))
                           .arg(QString::number(m))
                           .arg(QString::number(pValue))
                           .arg(QString::number(alpha,'f',7))
                           .arg(QString::number(e))
                           .arg(QString::number(z))
                           .arg(QString::number(network.getStep()));


    qDeleteAll(vec->begin(),vec->end());

    delete vec;




}
