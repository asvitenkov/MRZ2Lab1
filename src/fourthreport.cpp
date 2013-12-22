#include "defines.h"

#include "fourthreport.h"

#include "neuralnetwork.h"

#include <QtCore/qtconcurrentmap.h>


FourthReport::FourthReport(int n, int m, double error, const QVector<double> &alphaValues, int pValue, const QString &img, const QString &outFileName, bool multithreadingEnabled)
    : QObject(0)
{
    mM = m;
    mN = n;
    mError = error;
    mAlphaValues = alphaValues;
    mPValue = pValue;
    mOutFileName = outFileName;
    mImgName = img;
    mMultithreadingEnable = multithreadingEnabled;

}


FourthReport::~FourthReport()
{

}

void FourthReport::run()
{
    if (mMultithreadingEnable)
        runMultiThread();
    else runSingleThread();
}

void FourthReport::executeSingleThread(int n, int m, double error, double alpha, int pValue, const QImage &img, QTextStream &out)
{
        CImage image = CImage::fromImage(img);
        QVector<Segment*>* vec = image.split(n,m);

        CNeuralNetwork network(n*m*3, pValue, alpha);

        double e = network.getError(*vec);

        while(e > error)
        {
            network.learn(*vec);
            e = network.getError(*vec);
        }

        double z = ( (double) (m*n + vec->size()) * pValue + 2 ) / (m * n * vec->size());

        qDeleteAll(vec->begin(),vec->end());

        delete vec;



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

}


void FourthReport::runSingleThread()
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

    for(int i=0; i<mAlphaValues.size(); i++)
    {
        executeSingleThread(mN, mM, mError, mAlphaValues[i], mPValue, img, out);
    }

    mFile.close();
}



void FourthReport::runMultiThread()
{
    mFile.setFileName(mOutFileName);

    mFile.open(QIODevice::WriteOnly);

    QTextStream out(&mFile);

    out << "N, M, P, Alpha, Error, Z, It\n";

    QVector<LearnItem> list;

    for(int i=0; i < mAlphaValues.size(); i++)
        list  << LearnItem(mN, mM, mError, mAlphaValues[i], mPValue, mImgName);

    mWatcher.setFuture(QtConcurrent::mapped(list,ProcessLearnItem));


    mWatcher.waitForFinished();


    for(int i=0; i< mAlphaValues.size(); i++)
    {
        out << mWatcher.resultAt(i);
    }

    mFile.close();
}
