#include "relaxcalculator.h"


RelaxCalculator::RelaxCalculator(QObject *parent): QObject (parent)
{

}

bool RelaxCalculator::calculateFromFile(QString filename)
{
    setFromFile(filename);
    return calculate();
}

bool RelaxCalculator::calculate()
{
    iteratinCounter = 0;
    for (int i = 0; i < n; i ++) {
        x[i] = i;
    }
     do {
        iteratinCounter++;
        for (int i = 0; i < n; i++) {      //копируем новые значения в старые
           oldx[i] = x[i];
        }
        relaxIteration();
    }  while (differenceDecision() > EPSILON);

//     luCalculation(a);
//     calculate(b);
    return true;
}

bool RelaxCalculator::setFromFile(QString filename)
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

void RelaxCalculator::setBC()
{

}

double RelaxCalculator::getW() const
{
    return W;
}

void RelaxCalculator::setW(double value)
{
    W = value;
}

int RelaxCalculator::getIteratinCounter() const
{
    return iteratinCounter;
}

double RelaxCalculator::getEPSILON() const
{
    return EPSILON;
}

QString RelaxCalculator::getInput()
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

QString RelaxCalculator::getX()
{
    QString Out = "X:\n";
    for (int i = 0; i < n; i ++) {
        Out += QString::number(x[i]) + " \n";
    }
    return Out;
}

QString RelaxCalculator::getIterCount()
{
//    QString Out = ;
//    for (int i = 0; i < n; i ++) {
//        Out += QString::number(x[i]) + " \n";
//    }
    return "Число итераций: " + QString::number(iteratinCounter);
}


//разница между решениями
double RelaxCalculator::differenceDecision()
{
    double maxDiff = 0;
    double tmp;
    for (int i = 0; i < n; i++)
    {
        tmp = abs(x[i] - oldx[i]);
        if (tmp > maxDiff)
            maxDiff = tmp;
    }
    return maxDiff;
}

void RelaxCalculator::relaxIteration()
{
    double ptrSum;
    //double ajk;
    for (int i = 0; i < n; i++){
        ptrSum = 0;
        for (int j = 0; j < n; j++){
            if (i != j){
                ptrSum += a[i][j]/a[i][i] * x[j];
            }
        }
        x[i] = (1 - W) * x[i] + W * (b[i] / a[i][i] - ptrSum);
    }
}
