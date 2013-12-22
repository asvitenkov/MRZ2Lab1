#ifndef CIMAGE_H
#define CIMAGE_H

#include <armadillo>

#include <QVector>


typedef arma::mat Matrix2DF;
//typedef arma::fmat Matrix2DF;

class CNeuroPixel;
class QImage;


struct Segment
{
    Segment(int _rs, int _re, int _cs, int _ce, Matrix2DF* mat)
    {
        rs = _rs;
        re = _re;
        cs = _cs;
        ce = _ce;
        mMatrix = mat;
    }

    Segment(const Segment &copy)
    {
        rs = copy.rs;
        re = copy.re;
        cs = copy.cs;
        ce = copy.ce;
        mMatrix = copy.mMatrix;
    }

    Segment(const Segment &copy, Matrix2DF* mat)
    {
        rs = copy.rs;
        re = copy.re;
        cs = copy.cs;
        ce = copy.ce;
        mMatrix = mat;
    }

    int rs,re,cs,ce;
    Matrix2DF* mMatrix;
};


class CImage
{
public:
    CImage(const Matrix2DF &matrix);
    CImage(const CImage &copy);
    CImage& operator=(const CImage &other);

    static CImage fromImage(const QImage &from);
    static QImage toImage(const Matrix2DF &matrix);

    QVector<Segment*> *split(int r, int c) ;
    static CImage unite(int imgHeight, int imgWidth, const QVector<Segment *> *vec);

    QImage toImage() const;

    int rows() const { return mMatrix.n_rows; }
    int cols()  const{ return mMatrix.n_cols; }
    //CNeuroPixel color(int x, int y) const;


    //QImage toImage();

private:
    CImage();
    static double encodeColor(int color);
    static double decodeColor(double color);

    Matrix2DF mMatrix;
};

#endif // CIMAGE_H
