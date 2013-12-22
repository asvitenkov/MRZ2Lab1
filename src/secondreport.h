#ifndef SECONDREPORT_H
#define SECONDREPORT_H

#include <QFile>
#include <QTextStream>
#include <QFutureWatcher>

#include <QObject>

class SecondReport: public QObject
{

    Q_OBJECT

public:
    SecondReport(int n, int m, double error, double alpha, int pValue, const QVector<QString> &images, const QString &outFileName, bool multithreadingEnabled = true);
    virtual ~SecondReport();

    void run();

private:

    void executeSingleThread(int n, int m, double error, double alpha, int pValue, const QImage &img, QTextStream &out);

    void runSingleThread();
    void runMultiThread();


    int mPValue;
    QVector<QString> mImagesNames;
    double mError;
    int mN;
    int mM;
    double mAlpha;
    bool mMultithreadingEnable;
    QString mOutFileName;
    QFile mFile;
    QFutureWatcher<QString> mWatcher;
};

#endif // SECONDREPORT_H
