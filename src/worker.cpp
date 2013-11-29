#include "worker.h"

CWorker::CWorker(CNeuralNetwork *network, QVector<Segment *> *vector, QObject *parent) :
    QObject(parent), mNetwork(network), mSegmantArray(vector), mIsStopped(true), mIsExit(false), mDisableUpdate(false), mUpdateStep(1)
{
    Q_ASSERT(mNetwork);
}


void CWorker::process()
{
    while(true)
    {
        if (mIsExit)
            break;
        mSync.lock();
        if (mIsStopped)
            mPauseCond.wait(&mSync);
        mSync.unlock();
        mNetwork->learn(*mSegmantArray);
        if (!mDisableUpdate && mNetwork->getStep() % mUpdateStep == 0)
            emit stepOver();

    }
}


void CWorker::stop()
{
    mIsStopped = true;
    //mEventLoop.exec();
}



void CWorker::start()
{
    mIsStopped = false;
    //mEventLoop.exit();
    mPauseCond.wakeAll();
}

void CWorker::exit()
{
    mIsExit = true;
}
