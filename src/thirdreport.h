#ifndef THIRDREPORT_H
#define THIRDREPORT_H

#include <QObject>
#include <QFile>
#include <QImage>
#include <QTextStream>

class ThirdReport : public QObject
{
    Q_OBJECT
public:
    explicit ThirdReport(int n, int m, double error, double alpha, int pValue, double errorStep, const QString &img,const QString &outFileName);
    virtual ~ThirdReport();
    
    void run();

private:
    void execute(int n, int m, double error, double alpha, int pValue, const QImage &img, QTextStream &out);


    int mPValue;
    double mError;
    double mErrorStep;
    int mN;
    int mM;
    double mAlpha;
    QString mOutFileName;
    QFile mFile;
    QString mImgName;
    
};

#endif // THIRDREPORT_H
