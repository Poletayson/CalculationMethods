#ifndef RELAXCALCULATOR_H
#define RELAXCALCULATOR_H

#include <QVector>
#include <QObject>
#include <QFile>
#include <QQmlFile>
#include <QString>
#include <QStringList>

class RelaxCalculator : public QObject
{
    Q_OBJECT
public:
    RelaxCalculator(QObject *parent = nullptr);
public slots:

    bool calculateFromFile (QString filename);
    bool calculate ();
    bool setFromFile (QString filename);
    void setBC ();

    double getW() const;
    void setW(double value);

    int getIteratinCounter() const;

    double getEPSILON() const;

//    double *getX() const;
    QString getInput ();
    QString getX ();
    QString getIterCount ();

private:
    double EPSILON = 0.0001;
    double W = 1;
    int n;
    int iteratinCounter;
    QVector<double*> a;
//    QVector<double*> b;
//    QVector<double*> c;
    double *b;
//    QVector<float*> lu;
    double *x;
    double *oldx;

    double differenceDecision ();
    void relaxIteration ();
};

#endif // RELAXCALCULATOR_H
