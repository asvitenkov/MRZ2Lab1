#include "defines.h"

#include "secondreport.h"

#include "neuralnetwork.h"

#include <QtCore/qtconcurrentmap.h>




SecondReport::SecondReport(int n, int m, double error, double alpha, int pValue, const QVector<QString> &images, const QString &outFileName, bool multithreadingEnabled)
    : QObject(0)
{
    mM = m;
    mN = n;
    mError = error;
    mAlpha = alpha;
    mPValue = pValue;
    mOutFileName = outFileName;
    mImagesNames = images;
    mMultithreadingEnable = multithreadingEnabled;
}


SecondReport::~SecondReport()
{

}

void SecondReport::run()
{
    if (mMultithreadingEnable)
        runMultiThread();
    else runSingleThread();
}

void SecondReport::executeSingleThread(int n, int m, double error, double alpha, int pValue, const QImage &img, QTextStream &out)
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


void SecondReport::runSingleThread()
{

    mFile.setFileName(mOutFileName);

    mFile.open(QIODevice::WriteOnly);

    QTextStream out(&mFile);

    out << "N, M, P, Alpha, Error, Z, It\n";

    for(int i=0; i<mImagesNames.size(); i++)
    {
        QImage img(mImagesNames.at(i));

        if (img.isNull())
        {
            qDebug() << QString("Can not open image %1").arg(mImagesNames[i]);
        }
        else
        {
            qDebug() << "IMAGE: " << mImagesNames.at(i);
            executeSingleThread(mN, mM, mError, mAlpha, mPValue, img, out);
        }
    }

    mFile.close();
}



void SecondReport::runMultiThread()
{
    mFile.setFileName(mOutFileName);

    mFile.open(QIODevice::WriteOnly);

    QTextStream out(&mFile);

    out << "N, M, P, Alpha, Error, Z, It\n";

    QVector<LearnItem> list;

    for(int i=0; i < mImagesNames.size(); i++)
        list  << LearnItem(mN, mM, mError, mAlpha, mPValue, mImagesNames[i]);

    mWatcher.setFuture(QtConcurrent::mapped(list,ProcessLearnItem));


    mWatcher.waitForFinished();


    for(int i=0; i< mImagesNames.size(); i++)
    {
        out << mWatcher.resultAt(i);
    }

    mFile.close();
}
