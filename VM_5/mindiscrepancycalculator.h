#ifndef MINDISCREPANCYCALCULATOR_H
#define MINDISCREPANCYCALCULATOR_H

#include <QObject>
#include <QVector>
#include <QFile>
#include <QQmlFile>
#include <QString>
#include <QStringList>

class MinDiscrepancyCalculator : public QObject
{
    Q_OBJECT
public:
    explicit MinDiscrepancyCalculator(QObject *parent = nullptr);

public slots:
    bool calculate ();
    bool setFromFile (QString filename);

//    double getEPSILON() const;

////    double *getX() const;
    QString getInput ();
    QString getX ();
    QString getIterCount ();

private:
    double EPSILON = 0.0001;
    double W = 1;
    int n;
    int iteratinCounter;
    QVector<double*> a;

    double *b;
    double *r;
    double t;
    double *x;
    double *oldx;

    void mulMatrixVector (QVector<double*> m, double *v, double *res);    //умножение матрицы на вектор
    void subVectors (double *v1, double *v2, double *res);
    double scalarMul (double *v1, double *v2);
    void setDiscrepancy ();
//    double differenceDecision ();
    void minDiscrIteration ();
    double maxDiscrepancy ();

};

#endif // MINDISCREPANCYCALCULATOR_H
