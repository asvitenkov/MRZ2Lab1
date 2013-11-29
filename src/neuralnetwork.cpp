#include "neuralnetwork.h"

CNeuralNetwork::CNeuralNetwork(int segmantLength, int secondLayerCount, double alpha)
    : mSegmentLength(segmantLength)
    , mSecondLayerCount(secondLayerCount)
    , mAlpha(alpha)
    , mStep(0)
{
    Q_ASSERT(mAlpha >0 && mAlpha <= 0.01);
    initialize();
}


CNeuralNetwork::~CNeuralNetwork()
{

}

void CNeuralNetwork::initialize()
{
    mFirstLayerMatrix = arma::randu<Matrix2DF>(mSegmentLength, mSecondLayerCount) * 2 - 1;
    mSecondLayerMatrix = arma::randu<Matrix2DF>(mSecondLayerCount, mSegmentLength) * 2 - 1;

//    for(uint i=0; i<mFirstLayerMatrix.n_rows; i++)
//        for(uint j=0; j<mFirstLayerMatrix.n_cols; j++)
//            mFirstLayerMatrix(i,j) = 0.02;

//    mSecondLayerMatrix = mFirstLayerMatrix.t();

}



double CNeuralNetwork::learn(const QVector<Segment *> &vector)
{

    int size = vector.size();
    Matrix2DF Y;
    Matrix2DF Xs;
    Matrix2DF deltaX;

    for(int i=0; i<size; i++)
    {
        Matrix2DF &X = *(vector.at(i)->mMatrix);
        Y = X * mFirstLayerMatrix;
        Xs = Y * mSecondLayerMatrix;
        deltaX = Xs - X;

        mFirstLayerMatrix = mFirstLayerMatrix - mAlpha * ( X.t() * deltaX * ( mSecondLayerMatrix.t() ) );

        mSecondLayerMatrix = mSecondLayerMatrix - mAlpha * ( Y.t() * deltaX );

        normalizeMatrix(mFirstLayerMatrix);
        normalizeMatrix(mSecondLayerMatrix);

    }

    mStep++;


    return 0;
}


QVector<Segment*>* CNeuralNetwork::process(const QVector<Segment *> &vector) const
{
    QVector<Segment*> *retVector = new QVector<Segment*>();

    for(int i=0; i<vector.size(); i++)
    {
        Segment &pSeg = *vector.at(i);
        Matrix2DF result = *pSeg.mMatrix * mFirstLayerMatrix * mSecondLayerMatrix;
        retVector->push_back(new Segment(pSeg, new Matrix2DF(result)));
    }

    return retVector;
}


double CNeuralNetwork::getError(const QVector<Segment *> &vector) const
{
    double error = 0;
    int size = vector.size();
        for(int i=0; i<size; i++)
        {
            Matrix2DF &X = *(vector.at(i)->mMatrix);
            //deltaX = (X * mFirstLayerMatrix) * mSecondLayerMatrix - X;
            error += arma::accu(arma::pow((X * mFirstLayerMatrix) * mSecondLayerMatrix - X,2));
        }

   return error;
}


void CNeuralNetwork::normalizeMatrix(Matrix2DF &matrix)
{

    double sum;
    for(uint i=0; i<matrix.n_cols; i++)
    {

        sum = arma::norm(matrix.col(i),2);

         matrix.col(i)/=sum;

    }
}
