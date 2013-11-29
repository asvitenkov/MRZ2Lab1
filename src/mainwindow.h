#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QThread>
#include "worker.h"

QString Matrix2String(const Matrix2DF &matrix);

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void openFile();

private slots:

    void setOriginalImage(const QImage &img) const;
    void setCompressedImage(const QImage &img) const;
    void onBtnInitNetwork();

    void start();
    void stop();
    void resetNetwork();
    void resetUI();
    void onBtnReset();
    void showCompressedImage();
    void updateNetworkStateGUI();
    void showFirstLayerMatrix();
    void showSecondLayerMatrix();


    void setUpdateStep();
private:
    void initNetwork();


    Ui::MainWindow *ui;
    CNeuralNetwork *mNetwork;
    QVector<Segment*>* mSegmentsArray;
    CWorker* mWorker;
    CImage* mNeuralImage;
    QThread* mThread;

    QString mFilePath;
    QImage mOriginalImage;
    QVector<QWidget*> mOpenBrowserWindow;
};

#endif // MAINWINDOW_H
