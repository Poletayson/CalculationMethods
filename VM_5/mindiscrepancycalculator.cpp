#include "mindiscrepancycalculator.h"

MinDiscrepancyCalculator::MinDiscrepancyCalculator(QObject *parent) : QObject(parent)
{

}

bool MinDiscrepancyCalculator::calculate()
{
    iteratinCounter = 0;
    for (int i = 0; i < n; i ++) {
        x[i] = i;
    }
    r = new double[n];
    do {
        iteratinCounter++;
        minDiscrIteration();
    }  while (maxDiscrepancy() > EPSILON);

    return true;
}

bool MinDiscrepancyCalculator::setFromFile(QString filename)
{
    QFile file (QQmlFile::urlToLocalFileOrQrc(filename));
     file.open(QFile::ReadOnly);
     QString inputText = file.readLine();         //получаем массив b
     QStringList  strList = inputText.split(' ');     //разбиваем
     n = strList.length();
     b = new double [n];
     x = new double [n];
     oldx = new double [n];
     for (int i = 0; i < n; i ++) {
         b[i] = strList[i].toDouble();         //получаем массив b
     }

     a.clear();
     for (int i = 0; i < n; i ++) {
         inputText = file.readLine();         //получаем очередную строку
         strList = inputText.split(' ');     //разбиваем
         a.append(new double[n]);         //добавляем строку в матрицу
         for (int j = 0; j < n; j ++) {
             a[i][j] = strList[j].toDouble();         //заполняем строку
         }
     }
}

QString MinDiscrepancyCalculator::getInput()
{
    QString Out = "Система уравнений:\n";
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j++){
            Out += QString::number(a[i][j]).leftJustified(5, ' ') + " ";
        }
        Out += "| " + QString::number(b[i]).leftJustified(5, ' ') + "\n";
    }
    return Out;
}

QString MinDiscrepancyCalculator::getX()
{
    QString Out = "X:\n";
    for (int i = 0; i < n; i ++) {
        Out += QString::number(x[i]) + " \n";
    }
    return Out;
}

QString MinDiscrepancyCalculator::getIterCount()
{
    return "Число итераций: " + QString::number(iteratinCounter);
}

void MinDiscrepancyCalculator::mulMatrixVector(QVector<double *> m, double *v, double *res)
{
    double tmp;
    for (int i = 0; i < n; i++){
        tmp = 0;
        for (int j = 0; j < n; j++){
            tmp += m[i][j] * v[j];
        }
        res[i] = tmp;
    }
}

void MinDiscrepancyCalculator::subVectors(double *v1, double *v2, double *res)
{
    for (int i = 0; i < n; i++){
        res[i] = v1[i] - v2[i];
    }
}

double MinDiscrepancyCalculator::scalarMul(double *v1, double *v2)
{
    double scalMul = 0;
    for (int i = 0; i < n; i++){
        scalMul += v1[i] * v2[i];
    }
    return scalMul;
}

void MinDiscrepancyCalculator::setDiscrepancy()
{
    mulMatrixVector(a, x, r);
    subVectors(r, b, r);
}

void MinDiscrepancyCalculator::minDiscrIteration()
{
    setDiscrepancy();   //считаем невязки
    double *tmp = new double [n];
    mulMatrixVector(a, r, tmp);
    t = scalarMul(tmp, r) / scalarMul(tmp, tmp);

    for (int i = 0; i < n; i++){
        x[i] = x[i] - t * r[i];
    }
}

double MinDiscrepancyCalculator::maxDiscrepancy()
{
    double maxDiscr = 0;
    double tmp;
    for (int i = 0; i < n; i++)
    {
        tmp = abs(r[i]);
        if (tmp > maxDiscr)
            maxDiscr = tmp;
    }
    return maxDiscr;
}
