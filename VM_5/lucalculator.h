#ifndef LUCALCULATOR_H
#define LUCALCULATOR_H

#include <QVector>
#include <QObject>
#include <QFile>
#include <QQmlFile>
#include <QString>
#include <QStringList>

class LUCalculator : public QObject
{
    Q_OBJECT
public:
    LUCalculator(QObject *parent = nullptr);

    void calculate (float *b);
    void luCalculation (QVector<float*> a_a);
public slots:
    bool calculateFromFile (QString filename);
    bool calculate ();
    bool setFromFile (QString filename);
    QString getInput ();
    QString getLU ();
    QString getX ();


private:
    int n;
    QVector<float*> a;
    float *b;
    QVector<float*> lu;
    float *x;
};

#endif // LUCALCULATOR_H
