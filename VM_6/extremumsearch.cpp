#include "extremumsearch.h"

ExtremumSearch::ExtremumSearch(QObject *parent) : QObject(parent)
{
    for (int i = 0; i < 2; i++){
        intervals[i][0] = -10;      //устанавливаем интервалы
        intervals[i][1] = 10;
        extremum[i] = intervals[i][0];  //иизначально экстремумы ищем из границы интервала
    }
}

bool ExtremumSearch::calculate()
{
    double zNew = std::numeric_limits <double>::max();     //изначально берем z как максимально возможное

    do {
        zExtremum = zNew;   //берем z с предыдущей итерации
        for (int i = 0; i < 2; i++){
            zNew = goldenSection(i);
        }
    } while(abs(zExtremum - zNew) > EPSILLON);  //пока разница не станет несущественной
    return true;
}

QString ExtremumSearch::getSolution()
{
    QString Out = "Точка экстремума: " + QString::number(extremum[0]) + ", " + QString::number(extremum[1]) +
            "\nЗначение: " + QString::number(zExtremum);

    return Out;
}

QVector<double> ExtremumSearch::getVariable(int num)
{
    Variables.clear();
    double a = intervals[num][0];
    while (a < intervals[num][1]) {
        Variables.append(a);
        a += step;
    }
    return Variables;
}

QVector<double> ExtremumSearch::getValues(int num)
{
    Values.clear();
    double ptrVar[2];
    for (int i = 0; i < 2; i++){    //по умолчанию берем значения переменных в точке экстремума
        ptrVar[i] = extremum[i];
    }
    foreach (double var, Variables) {
        ptrVar[num] = var;    //меняем только заданную переменную, по которой и делаем "срез"
        Values.append(functionValue(ptrVar[0], ptrVar[1]));
    }
    return Values;
}

QVector<double> ExtremumSearch::getExtremum()
{
    QVector <double> ptr;
    for (int i = 0; i < 2; i++){
        ptr.append(extremum[0]);
    }
    return ptr;
}

double ExtremumSearch::getZExtremum() const
{
    return zExtremum;
}

double ExtremumSearch::goldenSection(int coordNumber)
{
    double currExtremum[2] = {extremum[0], extremum[1]};    //экстремум, полученный на этой итерации
    currExtremum[coordNumber] = intervals[coordNumber][0];  //одну из координат начинаем искать из границы

//изначальные параметры золотого сечения
    double x1 = intervals[coordNumber][0],  x2 = intervals[coordNumber][1];
    double a = x1 + (x2 - x1)/3, b = x1 + 2*(x2 - x1)/3;
    double newZ;

    currExtremum[coordNumber] = x1;
    double z1 = functionValue(currExtremum[0], currExtremum[1]);
    currExtremum[coordNumber] = a;
    double z2 = functionValue(currExtremum[0], currExtremum[1]);
    currExtremum[coordNumber] = b;
    double z3 = functionValue(currExtremum[0], currExtremum[1]);
    currExtremum[coordNumber] = x2;
    double z4 = functionValue(currExtremum[0], currExtremum[1]);


    //пока интервал не сожмется
    while (abs(x2 - x1) > EPSILLON_X){

        //В левой точке значение побольше
        if(z2 > z3){
            x1 = a; //выкидываем левую точку
            z1 = z2;
            a = a + (b - a) * 0.618;    //передвигаем a
            currExtremum[coordNumber] = a;
            z2 = functionValue(currExtremum[0], currExtremum[1]);
        }
        else{
            x2 = b; //выкидываем левую точку
            z4 = z3;
            b = b - (b - a) * 0.618;    //передвигаем b
            currExtremum[coordNumber] = b;
            z3 = functionValue(currExtremum[0], currExtremum[1]);
        }
    }
    //currExtremum[coordNumber] = (x1 + x2) / 2;
    extremum[coordNumber] = (x1 + x2) / 2;
    return functionValue(extremum[0], extremum[1]);
}

//эллиптический параболоид
double ExtremumSearch::functionValue(double x, double y)
{
    double p = 3.5, q = 2.8;
    double xOffset = 3.5, yOffset = 2.8;    //смещения
    return (x * x + xOffset) / (2 * p) + (y * y + yOffset) / (2 * q);
}
