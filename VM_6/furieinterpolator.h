#ifndef FURIEINTERPOLATOR_H
#define FURIEINTERPOLATOR_H

#include <QVector>
#include <QObject>
#include <QFile>
#include <QQmlFile>
#include <QString>
#include <QStringList>
#include <QtMath>
#include <QtCore>

#include <complex>

typedef std::complex<double> Complex;

class FurieInterpolator : public QObject
{
    Q_OBJECT
public:
    explicit FurieInterpolator(QObject *parent = nullptr);

signals:

public slots:
    bool setFromFile (QString filename);
    bool calculate ();
    QString getSolution ();
    QVector<double> getXout() const;
    QVector<double> getYout() const;

private:
    QVector <double> Xin;
    QVector <double> Yin;
    QVector <double> Xout;
    QVector <double> Yout;
    int n;
    int INTERIUM_COUNT = 5;   //количество значений между соседними иксами
    double t;   //период
    double st;
    double f;   //смещение
    Complex IC = Complex (0, 1);


    QVector <Complex> directTransformation ();   //вычисление коэффициентов A
    double exponent (double fi);
};

#endif // FURIEINTERPOLATOR_H
