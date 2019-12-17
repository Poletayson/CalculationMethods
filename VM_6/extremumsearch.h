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
    bool calculate ();
    QString getSolution ();
    QVector<double> getVariable(int num);
    QVector<double> getValues(int num);
    QVector<double> getExtremum();
    double getZExtremum() const;

private:
    int n;
    //int INTERIUM_COUNT = 5;   //количество значений между соседними иксами
    double intervals[2][2]; //интервалы для каждой переменной
    double extremum[2];   //точка экстремума, которую ищем
    double zExtremum;
    QVector<double> Variables;    //координаты т. экстремума
    QVector<double> Values;

    double EPSILLON = 0.00000002;
    double EPSILLON_X = 0.001;
    double step = 0.1;

    double goldenSection (int coordNumber);    //спуск по координате
    double functionValue (double x, double y);     //значение в заданной точке
};

#endif // EXTREMUMSEARCH_H
