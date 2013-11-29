#include "image.h"
#include <QImage>

CImage::CImage()
{

}

CImage::CImage(const Matrix2DF &matrix)
{
    mMatrix = matrix;
}

CImage::CImage(const CImage &copy)
{
    mMatrix = copy.mMatrix;
}

CImage& CImage::operator =(const CImage &other)
{
    mMatrix = other.mMatrix;
    return *this;
}

CImage CImage::fromImage(QImage &from)
{
    Q_ASSERT(!from.isNull());

    if (from.isNull())
        return CImage();

    Matrix2DF matrix(from.height(),from.width()*3);
    for(int i=0; i<from.height();i++)
        for(int j=0; j<from.width(); j++)
        {
            QRgb color = from.pixel(j,i);
            matrix(i,j*3) = encodeColor(qRed(color));
            matrix(i,j*3+1) = encodeColor(qGreen(color));
            matrix(i,j*3+2) = encodeColor(qBlue(color));
        }

    CImage img(matrix);

    return img;
}


double CImage::encodeColor(int color)
{
    Q_ASSERT(2*color/255 - 1 <=1 &&  2*color/255 - 1 >=-1);
    return 2 * color / 255.0 - 1.0;
}

double CImage::decodeColor(double color)
{
    double val = 255 * (color + 1) / 2;

    if(val < 0 ) return 0;
    if(val >255) return 255;

    return val;
}

QImage CImage::toImage(const Matrix2DF &matrix)
{
    QImage img(matrix.n_cols/3, matrix.n_rows, QImage::Format_RGB32);

    for(int i=0; i<img.height(); i++)
        for(int j=0; j<img.width(); j++)
        {
            img.setPixel(j, i, qRgb(decodeColor(matrix(i,j*3)),decodeColor(matrix(i,j*3+1)), decodeColor(matrix(i,j*3+2))));
        }

    return img;
}

QImage CImage::toImage() const
{
    return CImage::toImage(mMatrix);
}

QVector<Segment *> *CImage::split(int r, int c)
{
    Q_ASSERT(r>0);
    Q_ASSERT(c>0);

    int matRows = mMatrix.n_rows;
    int matCols = mMatrix.n_cols;

    int segRowCount = ceil( (double) matRows / r);
    int segColCount = ceil( (double) matCols / (3 * c));

    QVector<Segment *> *vec = new QVector<Segment *>();
    Matrix2DF subMat;

    int rs, cs, re, ce;

    for(int i=0; i< segRowCount; i++)
        for(int j=0; j<segColCount; j++)
        {
            rs = i * r;
            cs = 3 * j * c;
            if (i == segRowCount - 1)
                rs = matRows - r;
            if (j == segColCount - 1)
                cs = matCols - c * 3;
            re = rs + r - 1;
            ce = cs + 3 * c - 1;

            subMat = mMatrix.submat(rs, cs, re, ce).t();
            subMat.reshape(1,r*c*3);
            vec->push_back(new Segment(rs,re,cs,ce,new Matrix2DF(subMat)));
        }

    return vec;
}


CImage CImage::unite(int imgHeight, int imgWidth, const QVector<Segment *> *vec)
{
    Q_ASSERT(!vec->isEmpty());

    if(vec->isEmpty())
        return CImage();

    int rs, cs, re, ce;
    Matrix2DF matrix(imgHeight, imgWidth * 3);


    for(int i=0; i< vec->size(); i++)
    {
        Segment *pSeg = vec->at(i);
        Matrix2DF &pMatrix = *pSeg->mMatrix;

        rs = pSeg->rs;
        re = pSeg->re;
        cs = pSeg->cs;
        ce = pSeg->ce;

        int item=0;

        for(int ii = rs; ii <= re; ii++)
            for(int jj = cs; jj <= ce; jj++)
                matrix(ii,jj) = pMatrix(item++);
    }

    return CImage(matrix);
}
