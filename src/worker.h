#ifndef WORKER_H
#define WORKER_H

#include <QObject>
#include <QEventLoop>
#include <QWaitCondition>
#include <QMutex>

#include "neuralnetwork.h"


class CWorker : public QObject
{
    Q_OBJECT
public:
    explicit CWorker(CNeuralNetwork *network, QVector<Segment*>* vector,QObject *parent = 0);
    
signals:
    void errorValue(double error);
    void stepOver();
    
public slots:
    void process();
    void stop();
    void start();
    void exit();
    void setDisableUpdate(bool enable) { mDisableUpdate = enable; }
    void setUpdateStep(int step ) { mUpdateStep = step; }

private:

    CNeuralNetwork *mNetwork;

    QVector<Segment*>* mSegmantArray;

    bool mIsStopped;
    bool mIsExit;
    bool mDisableUpdate;

    int mUpdateStep;
    QMutex mSync;
    QWaitCondition mPauseCond;
    QEventLoop mEventLoop;

};

#endif // WORKER_H
