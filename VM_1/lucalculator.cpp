#include "lucalculator.h"

LUCalculator::LUCalculator()
{

}

void LUCalculator::calculate(QVector<float*> a_a, float *b)
{
    x = new float [n];
    float *ptrX = new float [n * n];
    float currentX;
//находим все иксы
    for (int i = n - 1; i >= 0; i--) {
        //находим x как в треугольной матрице
        currentX = b[i];
        for (int j = i + 1; j < n; j ++){
            currentX -= ptrX[i * n + j];
        }
        x[i] = currentX / lu[i][i];

        //находим столбец
        for (int j = i - 1; j >= 0; j--){
//            ptrX[j * n + i] = 1;
            float ptrSum = 0;
            //находим сумму
            for (int k = i + 1; k < n; k ++){
                ptrSum += lu[i][k] * ptrX[k * n + i];
            }
            ptrX[j * n + i] = (1 - ptrSum) / lu[i][j];
        }

        //находим строку
        for (int j = i - 1; j >= 0; j--){
            float ptrSum = 0;
            //находим сумму
            for (int k = j + 1; k < n; k ++){
                ptrSum += lu[k][j] * ptrX[i * n + k];
            }
            ptrX[i * n + j] = - ptrSum;
        }
    }

}

void LUCalculator::luCalculation(QVector<float*> a_a)
{
    lu = a_a;

    for(int i = 0; i < n; i++)
        for(int j = i; j < n; j++)
            lu[j][i]=lu[j][i]/lu[i][i];

    for(int k = 1; k < n; k++)
    {
        for(int i = k-1; i < n; i++)
            for(int j = i; j < n; j++)
                lu[j][i]=lu[j][i]/lu[i][i];

        for(int i = k; i < n; i++)
            for(int j = k-1; j < n; j++)
                lu[i][j]=lu[i][j]-lu[i][k-1]*lu[k-1][j];
    }
}

bool LUCalculator::calculateFromFile(QString filename)
{
    QFile file (filename);
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

    //return Translator->Translate(Text);       //переводим текст и возвращаем
}
