#ifndef DEFINES_H
#define DEFINES_H

#include <QString>
#include <QVector>
#include <QImage>
#include <QDebug>

//#include "neuralnetwork.h"


struct LearnItem
{
    LearnItem()
    {

    }

    LearnItem(int _n, int _m, double _error, double _alpha, int _pValue, const QString& _imageName)
    {
        n = _n;
        m = _m;
        error = _error;
        alpha = _alpha;
        pValue = _pValue;
        imageName = _imageName;
    }

    LearnItem(const LearnItem &copy)
    {
        n = copy.n;
        m = copy.m;
        error = copy.error;
        alpha = copy.alpha;
        pValue = copy.pValue;
        imageName = copy.imageName;
    }

    int m;
    int n;
    double error;
    double alpha;
    int pValue;
    QString imageName;
};


QString ProcessLearnItem(const LearnItem& item);

#endif // DEFINES_H
