#include "defines.h"

#include "neuralnetwork.h"


#define DEBUG_UPDATE_STEP 100

QString ProcessLearnItem(const LearnItem& item)
{
    QString out;

    QImage img(item.imageName);

    if (img.isNull())
    {
        qDebug() << QString("Can not open image %1\n").arg(item.imageName);
        return QString("Can not open image %1\n").arg(item.imageName);
    }


    CImage image = CImage::fromImage(img);
    QVector<Segment*>* vec = image.split(item.n,item.m);

    CNeuralNetwork network(item.n * item.m * 3, item.pValue, item.alpha);

    double e = network.getError(*vec);

    int step = DEBUG_UPDATE_STEP;

    while(e > item.error)
    {
        step--;
        network.learn(*vec);
        e = network.getError(*vec);
        if (!step)
        {
            qDebug() << item.pValue << " " << e;
            step = DEBUG_UPDATE_STEP;
        }
    }

    double z = ( (double) (item.m*item.n + vec->size()) * item.pValue + 2 ) / (item.m * item.n * vec->size());


    qDeleteAll(vec->begin(),vec->end());
    //vec->clear();

    delete vec;



    out = QString("%1, %2, %3, %4, %5, %6, %7\n")
                           .arg(QString::number(item.n))
                           .arg(QString::number(item.m))
                           .arg(QString::number(item.pValue))
                           .arg(QString::number(item.alpha,'f',7))
                           .arg(QString::number(e))
                           .arg(QString::number(z))
                           .arg(QString::number(network.getStep()));
    qDebug() << QString("%1, %2, %3, %4, %5, %6, %7\n%8")
                           .arg(QString::number(item.n))
                           .arg(QString::number(item.m))
                           .arg(QString::number(item.pValue))
                           .arg(QString::number(item.alpha,'f',7))
                           .arg(QString::number(e))
                           .arg(QString::number(z))
                           .arg(QString::number(network.getStep()))
                           .arg(item.imageName);


    return out;
}
