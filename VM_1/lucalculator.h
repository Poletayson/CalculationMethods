#ifndef LUCALCULATOR_H
#define LUCALCULATOR_H

#include <QVector>
#include <QObject>
#include <QFile>
#include <QString>
#include <QStringList>

class LUCalculator
{
public:
    LUCalculator();

    void calculate (QVector<float*> a_a, float *b);
    void luCalculation (QVector<float*> a_a);
    bool calculateFromFile (QString filename);

private:
    int n;
    QVector<float*> a;
    float *b;
    QVector<float*> lu;
    float *x;
};

#endif // LUCALCULATOR_H
