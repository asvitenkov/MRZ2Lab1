#ifndef FIRSTREPORT_H
#define FIRSTREPORT_H


#include <QFile>
#include <QTextStream>
#include <QFutureWatcher>

#include <QObject>

class FirstReport: public QObject
{

    Q_OBJECT

public:
    FirstReport(int n, int m, double error, double alpha, const QVector<int> &pValues, const QString &img,const QString &outFileName, bool multithreadingEnabled = true);
    virtual ~FirstReport();

    void run();

private:

    void executeSingleThread(int n, int m, double error, double alpha, int pValue, const QImage &img, QTextStream &out);

    void runSingleThread();
    void runMultiThread();


    QVector<int> mPValues;
    double mError;
    int mN;
    int mM;
    double mAlpha;
    bool mMultithreadingEnable;
    QString mOutFileName;
    QFile mFile;
    QString mImgName;
    QFutureWatcher<QString> mWatcher;
};

#endif // FIRSTREPORT_H
