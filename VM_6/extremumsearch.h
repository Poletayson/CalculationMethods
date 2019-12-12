#ifndef EXTREMUMSEARCH_H
#define EXTREMUMSEARCH_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QQmlFile>
#include <QString>
#include <QStringList>
#include <QtMath>
#include <QtCore>

class ExtremumSearch : public QObject
{
    Q_OBJECT
public:

    explicit ExtremumSearch(QObject *parent = nullptr);

signals:

public slots:
//    bool setFromFile (QString filename);
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
    double extremum[2];   //точка экстремума, которую ищем
    double Xext;    //координаты т. экстремума
    double Yext;

    double functionValue (double x, double y);     //значение в заданной точке
};

#endif // EXTREMUMSEARCH_H
