#ifndef FURIEINTERPOLATOR_H
#define FURIEINTERPOLATOR_H

#include <QVector>
#include <QObject>
#include <QFile>
#include <QQmlFile>
#include <QString>
#include <QStringList>
#include <QtMath>

class FurieInterpolator : public QObject
{
    Q_OBJECT
public:
    explicit FurieInterpolator(QObject *parent = nullptr);
    bool calculate ();
    bool setFromFile (QString filename);

    QVector<double> getXout() const;
    QVector<double> getYout() const;

signals:

public slots:
    QString getSolution ();
private:
    QVector <double> Xin;
    QVector <double> Yin;
    QVector <double> Xout;
    QVector <double> Yout;
    int n;
    int INTERIUM_COUNT = 10;   //количество значений между соседними иксами
    double t;   //период
    double f;   //смещение

    QVector <double> directTransformation ();   //вычисление коэффициентов A
    double exponent (double fi);
};

#endif // FURIEINTERPOLATOR_H
