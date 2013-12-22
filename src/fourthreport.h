#ifndef FOURTHREPORT_H
#define FOURTHREPORT_H


#include <QFile>
#include <QTextStream>
#include <QFutureWatcher>

#include <QObject>

class FourthReport: public QObject
{

    Q_OBJECT

public:
    FourthReport(int n, int m, double error, const QVector<double> &alphaValues, int pValue, const QString &img,const QString &outFileName, bool multithreadingEnabled = true);
    virtual ~FourthReport();

    void run();

private:

    void executeSingleThread(int n, int m, double error, double alpha, int pValue, const QImage &img, QTextStream &out);

    void runSingleThread();
    void runMultiThread();


    int mPValue;
    double mError;
    int mN;
    int mM;
    QVector<double> mAlphaValues;
    bool mMultithreadingEnable;
    QString mOutFileName;
    QFile mFile;
    QString mImgName;
    QFutureWatcher<QString> mWatcher;
};

#endif // FOURTHREPORT_H
