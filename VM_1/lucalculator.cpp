#include "lucalculator.h"

LUCalculator::LUCalculator(QObject *parent): QObject (parent)
{

}

void LUCalculator::calculate(QVector<float*> a_a, float *b)
{
    x = new float [n];
    float *ptrY = new float [n];

    //сначала находим вспомогательные y
    for (int i = 0; i < n; i++) {
        ptrY[i] = b[i];
        for (int j = 0; j < i; j++) {
            ptrY[i] -= ptrY[j] * lu[i][j];
        }
    }

    //теперь находим все иксы
    for (int i = n - 1; i >= 0; i--) {
        x[i] = ptrY[i];
        for (int j = n - 1; j > i; j--) {
            x[i] -= x[j] * lu[i][j];
        }
        x[i] /= lu[i][i];
    }
}

void LUCalculator::luCalculation(QVector<float*> a_a)
{
    lu.clear();
    for (int i = 0; i < n; i ++) {
        lu.append(new float[n]);         //добавляем строку в матрицу
        for (int j = 0; j < n; j ++) {
            lu[i][j] = a_a[i][j];         //заполняем строку
        }
    }

    float ptrSum;
    for(int i = 0; i < n; i++)
    {
        //находим строку U
        for(int j = i; j < n; j++){
            ptrSum = 0;
            for(int k = 0; k < i; k++)
                ptrSum += lu[i][k] * lu[k][j];

            lu[i][j] -= ptrSum;
        }

        //находим столбец L
        for(int j = i + 1; j < n; j++){
            ptrSum = 0;
            for(int k = 0; k < i; k++)
                ptrSum += lu[j][k] * lu[k][i];

            lu[j][i] = (lu[j][i] - ptrSum) / lu[i][i];
        }

    }
}

bool LUCalculator::calculateFromFile(QString filename)
{
    QFile file (QQmlFile::urlToLocalFileOrQrc(filename));
    file.open(QFile::ReadOnly);
    QString inputText = file.readLine();         //получаем массив b
    QStringList  strList = inputText.split(' ');     //разбиваем
    n = strList.length();
    b = new float [n];
    for (int i = 0; i < n; i ++) {
        b[i] = strList[i].toFloat();         //получаем массив b
    }

    a.clear();
    for (int i = 0; i < n; i ++) {
        inputText = file.readLine();         //получаем очередную строку
        strList = inputText.split(' ');     //разбиваем
        a.append(new float[n]);         //добавляем строку в матрицу
        for (int j = 0; j < n; j ++) {
            a[i][j] = strList[j].toFloat();         //заполняем строку
        }
    }

    luCalculation(a);
    calculate(a, b);
}

QString LUCalculator::getInput()
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

QString LUCalculator::getLU()
{
    QString Out = "Матрицы L и U:\n";
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < n; j++){
            Out += QString::number(lu[i][j]).leftJustified(8, ' ') + " ";
        }
        Out += "\n";
    }
    return Out;
}

QString LUCalculator::getX()
{
    QString Out = "X:\n";
    for (int i = 0; i < n; i ++) {
        Out += QString::number(x[i]) + " \n";
    }
    return Out;
}
