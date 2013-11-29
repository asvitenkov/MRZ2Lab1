#ifndef NEURALNETWORK_H
#define NEURALNETWORK_H

#include "image.h"

class CNeuralNetwork
{
public:
    CNeuralNetwork(int segmantLength, int secondLayerCount, double alpha);
    virtual ~CNeuralNetwork();

    double learn(const QVector<Segment*> &vector);
    QVector<Segment*>* process(const QVector<Segment*> &vector) const ;
    double getError(const QVector<Segment*> &vector) const ;
    int getStep() const { return mStep; }

    const Matrix2DF& firstLayerMatrix(){ return mFirstLayerMatrix; }
    const Matrix2DF& secondLayerMatrix(){ return mSecondLayerMatrix; }

private:
    void initialize();
    void normalizeMatrix(Matrix2DF &matrix);


    int mSegmentLength;
    int mSecondLayerCount;
    double mAlpha;
    int mStep;

    Matrix2DF mFirstLayerMatrix;
    Matrix2DF mSecondLayerMatrix;

};




#endif // NEURALNETWORK_H
